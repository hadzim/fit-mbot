/*
 * JsonServices.h
 *
 *  Created on: Oct 7, 2013
 *      Author: root
 */

#ifndef JSONSERVICES_H_
#define JSONSERVICES_H_

#include <string>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/SharedPtr.h>
#include <vector>
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"

namespace TBS {
	namespace Services {

		std::string computeMD5hash(std::string plainPassword);

		class JsonClientParams {
			public:
				enum JsonProtocol{
					JsonHttp,
					JsonWs,
					JsonRaw
				};

				JsonClientParams(std::string hostName, int port, JsonProtocol protocol);
				std::string hostName() const;
				int port() const;

				void setHttps(bool https = true);
				void setProtected(const std::string & userName, const std::string & password);

				bool isHttps() const;

				bool isProtected() const;
				std::string getUserName() const;
				std::string getPassword() const;

				JsonProtocol protocol() const;
			private:
				std::string hostName_;
				int port_;
				JsonProtocol protocol_;

				bool isHttps_;

				bool isProtected_;
				std::string userName_;
				std::string password_;
		};

		class RequestHandler {
			public:
				typedef Poco::SharedPtr <RequestHandler> Ptr;
				typedef std::vector <Ptr> PtrList;

				virtual ~RequestHandler();

				virtual bool canHandle(std::string query) = 0;
				virtual void handle(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response) = 0;
		};

		class FileStreamRequestHandler : public RequestHandler {
			public:
				FileStreamRequestHandler(std::string url, std::string filePath, std::string contentType = "text/html");
				virtual ~FileStreamRequestHandler();

				virtual bool canHandle(std::string query);
				virtual void handle(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response);
			private:
				std::string url;
				std::string fname;
				std::string contentType;

		};

		class JsonServerParams {
			public:
				JsonServerParams(int port);
				int port() const;

				void allowCrossDomain(bool cd);
				bool isCrossDomainAllowed() const;

				void setHttps(const std::string & privateKey, const std::string & certificate);
				void setProtected(const std::string & userName, const std::string & passwordHash);

				bool isHttps() const;
				std::string getHttpsPrivateKey() const;
				std::string getHttpsCertificate() const;

				bool isProtected() const;
				std::string getUserName() const;
				std::string getPasswordHash() const;

				void addSpecialRequestHandler(RequestHandler::Ptr rh);
				RequestHandler::PtrList & getRequestHandlers();
			private:
				int port_;

				bool allowCrossDomain_;

				bool isHttps_;
				std::string httpsPrivateKey_;
				std::string httpsCertificate_;

				bool isProtected_;
				std::string userName_;
				std::string passwordMD5Hash_;

				RequestHandler::PtrList specialHandlers;
		};

	}
}
#endif /* JSONSERVICES_H_ */
