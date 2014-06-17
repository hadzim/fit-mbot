/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    httpserver.cpp
 * @date    31.12.2012
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#include "jsonrpc/connectors/httpinterfaceserver.h"
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

#include "Poco/Net/HTTPServer.h"
#include <Poco/StreamCopier.h>
#include "jsonrpc/ServiceHandlers.h"

#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"
#include "Poco/DigestEngine.h"

#include "Poco/File.h"
#include <fstream>

#include "HttpServerHelpers.h"

namespace jsonrpc {



	class MultiRootHandler: public Poco::Net::HTTPRequestHandler {
		public:

			MultiRootHandler(ServiceHandlers & serviceHandlers, TBS::Services::JsonServerParams & p) :
					handlerProvider(serviceHandlers), p(p) {
			}

			void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
				std::string errorMessage = "";
				try {

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
						serviceName = serviceName.substr(0, question - 1);
					}

					for (auto i = p.getRequestHandlers().begin(); i != p.getRequestHandlers().end(); i++){
						if ((*i)->canHandle(serviceName)){
							std::cout << "SPECIAL HANDLING of " << serviceName << std::endl;
							(*i)->handle(request, response);
							return;
						}
					}

					//std::cout << "service name: " << serviceName << std::endl;

					std::istream& rs = request.stream();
					std::stringstream outstr;
					Poco::StreamCopier::copyStream(rs, outstr);
					std::string rsp;
					std::string req = outstr.str();

					//std::cout << "requset: " << req << std::endl;

					//this->handlerProvider.GetHandler()

					this->handlerProvider.getHandler(serviceName)->HandleRequest(req, rsp);

					//std::cout << "response: " << rsp << std::endl;

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

	class MultiRequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory {
		public:
			MultiRequestHandlerFactory(ServiceHandlers & handlerProvider, const TBS::Services::JsonServerParams & p) :
					handlerProvider(handlerProvider), p(p) {
				//std::cout < "hfactory " << &handlerProvider << std::endl;
			}
			virtual ~MultiRequestHandlerFactory() {
			}
			Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
				return new MultiRootHandler(handlerProvider, p);
			}
		private:
			ServiceHandlers & handlerProvider;
			TBS::Services::JsonServerParams p;
	};

	HttpInterfaceServer::HttpInterfaceServer(const TBS::Services::JsonServerParams & p) :
			p(p) {

		Poco::Net::HTTPServerParams* pParams = new Poco::Net::HTTPServerParams;
		pParams->setMaxQueued(100);
		pParams->setMaxThreads(2);
		if (p.isHttps()) {
			std::cout << "service via https: PK: " << p.getHttpsPrivateKey() << " CT:" << p.getHttpsCertificate() << std::endl;
			Poco::Net::Context::Ptr context = new Poco::Net::Context(Poco::Net::Context::SERVER_USE, p.getHttpsPrivateKey(), p.getHttpsCertificate(), "");
			// disable session cache because of Firefox (less memory consuming than session cache enabling)
#ifndef OLDPOCO13
			context->disableStatelessSessionResumption();
#endif
			Poco::Net::SecureServerSocket svs(p.port(), 64, context);
			srv = std::unique_ptr<Poco::Net::HTTPServer>(new Poco::Net::HTTPServer(new MultiRequestHandlerFactory(handlers_, p), svs, pParams));
			std::cout << "multi https server listens on " << srv->port() << std::endl;
		} else {
			Poco::Net::ServerSocket svs(p.port()); // set-up a server socket
			srv = std::unique_ptr<Poco::Net::HTTPServer>(new Poco::Net::HTTPServer(new MultiRequestHandlerFactory(handlers_, p), svs, pParams));
			std::cout << "multi server listens on " << srv->port() << std::endl;
		}
	}

	HttpInterfaceServer::~HttpInterfaceServer() {
		srv->stop();
	}

	bool HttpInterfaceServer::StartListening() {
		std::cout << "multi server start listening " << std::endl;
		srv->start();
		return true;
	}

	bool HttpInterfaceServer::StopListening() {
		std::cout << "multi server stop listening " << std::endl;
		srv->stop();
		return true;

	}
	ServiceHandlers & HttpInterfaceServer::handlers() {
		return this->handlers_;
	}

} /* namespace jsonrpc */
