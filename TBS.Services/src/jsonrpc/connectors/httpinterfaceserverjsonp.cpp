/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    httpserver.cpp
 * @date    31.12.2012
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#include "jsonrpc/connectors/httpinterfaceserverjsonp.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/Context.h"
#include "Poco/Net/SecureServerSocket.h"
#include "Poco/Net/HTTPBasicCredentials.h"

#include "Poco/Net/HTMLForm.h"

#include "Poco/Net/HTTPServer.h"
#include "Poco/URI.h"
#include <Poco/StreamCopier.h>
#include "jsonrpc/ServiceHandlers.h"

#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"
#include "Poco/DigestEngine.h"

#include "Poco/File.h"
#include <fstream>

#include "TBS/Log.h"

#include "HttpServerHelpers.h"

namespace jsonrpc {



	class JsonpMultiRootHandler: public Poco::Net::HTTPRequestHandler {
		public:

			JsonpMultiRootHandler(ServiceHandlers & serviceHandlers, TBS::Services::JsonServerParams p) :
					handlerProvider(serviceHandlers), p(p) {
			}

			static std::string parseResponse(std::string respOriginalStr){

				Json::Value respFinalOk;
				std::string errorMessage;

		        try {
			        Json::Value respOriginalJson;
		        	Json::Reader reader;
					if (reader.parse(respOriginalStr, respOriginalJson, false))
					{
						if (respOriginalJson["error"].isNull()){
							//valid data
							respFinalOk = respOriginalJson["result"];
						} else {
							errorMessage = respOriginalJson["error"]["message"].asString();
						}
					} else {
						errorMessage = "Output not in json format";
					}
		    	} catch (Poco::Exception & e){
					errorMessage = e.message();
					std::cout << "Exception: " << e.displayText() << std::endl;
				} catch (std::exception & e){
					std::cout << "Exception: " << e.what() << std::endl;
					errorMessage = e.what();
				} catch (...){
					std::cout << "Exception: ??" << std::endl;
					errorMessage = "Unknown error";
				}

				Json::Value val;
				val["ReturnCode"] = errorMessage.empty() ? 200 : 500;
				val["ReturnMessage"] = errorMessage.empty() ? "OK" : errorMessage;
				val["ReturnObject"] = respFinalOk;

				 Json::FastWriter writer;
				return writer.write(val);
			}




			void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
				std::string errorMessage = "";
				try {

					LTRACE("Service.Jsonp") << "requset: " << request.getURI() << LE;

					HttpServerHelpers::ReturnType ret = HttpServerHelpers::preprocess(p, request, response);
					if (ret == HttpServerHelpers::RequestFinished){
						return;
					}

					std::string serviceName = request.getURI();

					if (serviceName.find('/') == 0) {
						serviceName = serviceName.substr(1);
					}
					std::string::size_type question = serviceName.find('?');
					if (question != std::string::npos) {
						serviceName = serviceName.substr(0, question);
					}

					for (auto i = p.getRequestHandlers().begin(); i != p.getRequestHandlers().end(); i++){
						std::cout << "try special handling for " << serviceName << std::endl;
						if ((*i)->canHandle(serviceName)){
							std::cout << "SPECIAL HANDLING of " << serviceName << std::endl;
							(*i)->handle(request, response);
							return;
						}
					}

					//std::cout << "service name: " << serviceName << std::endl;

					Poco::Net::HTMLForm form(request, request.stream());

					 Json::Value jsrequest(Json::objectValue);

					 jsrequest["jsonrpc"] = "2.0";
					 jsrequest["params"] = Json::Value(Json::objectValue);
					 jsrequest["id"] = 99;
					 jsrequest["method"] = form["method"];


					 std::string callbackFnc = form["callback"];

					for (Poco::Net::HTMLForm::ConstIterator i = form.begin(); i != form.end(); i++){
						LTRACE("Service.Jsonp") << "param: " << i->first << " value: " << i->second << LE;
						//std::cout << "param: " << i->first << " value: " << i->second << std::endl;
						if (i->first == "callback" || i->first == "_" || i->first == "method"){
							continue;
						}
						jsrequest["params"][i->first] = i->second;
					}

					 Json::FastWriter w;
					 std::string jsonstrrequest = w.write(jsrequest);


					std::cout << "requset: " << jsonstrrequest << std::endl;
					LTRACE("Service.Jsonp") << "requset: " << jsonstrrequest << LE;

					//this->handlerProvider.GetHandler()
					std::string rsp;
					this->handlerProvider.getHandler(serviceName)->HandleRequest(jsonstrrequest, rsp, true);

					//output from Json RPC to Cristis format
					rsp = parseResponse(rsp);


					rsp = callbackFnc + "(" + rsp + ")";

					LTRACE("Service.Jsonp") << "response: " << rsp << LE;

					response.setContentType("application/json");
					response.sendBuffer(rsp.data(), rsp.length());
				} catch (Poco::Exception & e){
					errorMessage = e.message();
					std::cout << "EXception: " << e.displayText() << std::endl;
				} catch (std::exception & e){
					std::cout << "EXception: " << e.what() << std::endl;
					errorMessage = e.what();
				} catch (...){
					std::cout << "EXception: ??" << std::endl;
					errorMessage = "Unknown error";
				}
			}
		private:
			ServiceHandlers & handlerProvider;
			TBS::Services::JsonServerParams p;
	};

	class JsonpMultiRequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory {
		public:
			JsonpMultiRequestHandlerFactory(ServiceHandlers & handlerProvider, const TBS::Services::JsonServerParams & p) :
					handlerProvider(handlerProvider), p(p) {
				//std::cout < "hfactory " << &handlerProvider << std::endl;
			}
			virtual ~JsonpMultiRequestHandlerFactory() {
			}
			Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
				return new JsonpMultiRootHandler(handlerProvider, p);
			}
		private:
			ServiceHandlers & handlerProvider;
			TBS::Services::JsonServerParams p;
	};

	JsonpHttpInterfaceServer::JsonpHttpInterfaceServer(const TBS::Services::JsonServerParams & p) :
			p(p) {

		LTRACE("Service.Jsonp") << "construct " << LE;

		Poco::Net::HTTPServerParams* pParams = new Poco::Net::HTTPServerParams;
		pParams->setMaxQueued(100);
		pParams->setMaxThreads(2);
		if (p.isHttps()) {
			std::cout << "service via https: PK: " << p.getHttpsPrivateKey() << " CT:" << p.getHttpsCertificate() << std::endl;
			Poco::Net::Context::Ptr context = new Poco::Net::Context(Poco::Net::Context::SERVER_USE, p.getHttpsPrivateKey(), p.getHttpsCertificate(), "");
			// disable session cache because of Firefox (less memory consuming than session cache enabling)
			context->disableStatelessSessionResumption();
			Poco::Net::SecureServerSocket svs(p.port(), 64, context);
			srv = std::unique_ptr<Poco::Net::HTTPServer>(new Poco::Net::HTTPServer(new JsonpMultiRequestHandlerFactory(handlers_, p), svs, pParams));
			std::cout << "multi https server listens on " << srv->port() << std::endl;
		} else {
			Poco::Net::ServerSocket svs(p.port()); // set-up a server socket
			srv = std::unique_ptr<Poco::Net::HTTPServer>(new Poco::Net::HTTPServer(new JsonpMultiRequestHandlerFactory(handlers_, p), svs, pParams));
			std::cout << "multi server listens on " << srv->port() << std::endl;
		}
	}

	JsonpHttpInterfaceServer::~JsonpHttpInterfaceServer() {
		LTRACE("Service.Jsonp") << "destruct " << LE;
		srv->stop();
	}

	bool JsonpHttpInterfaceServer::StartListening() {
		LTRACE("Service.Jsonp") << "start listening: " << LE;
		std::cout << "multi server start listening " << std::endl;
		srv->start();
		return true;
	}

	bool JsonpHttpInterfaceServer::StopListening() {
		LTRACE("Service.Jsonp") << "stop listening: " << LE;
		std::cout << "multi server stop listening " << std::endl;
		srv->stop();
		return true;

	}
	ServiceHandlers & JsonpHttpInterfaceServer::handlers() {
		return this->handlers_;
	}

} /* namespace jsonrpc */
