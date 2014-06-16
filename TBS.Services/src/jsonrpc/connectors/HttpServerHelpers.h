/*
 * HttpServerHelpers.h
 *
 *  Created on: May 29, 2014
 *      Author: dron
 */

#ifndef HTTPSERVERHELPERS_H_
#define HTTPSERVERHELPERS_H_
#include "Poco/MD5Engine.h"

#include "Poco/DigestStream.h"

#include "jsonrpc/connectors/httpinterfaceserver.h"

#include "Poco/Net/HTTPServerRequest.h"

#include "Poco/Net/HTTPServerResponse.h"

#include "Poco/Net/HTTPBasicCredentials.h"
#include "TBS/Services/Json/JsonServices.h"

namespace jsonrpc {

	class HttpServerHelpers {
		public:
			HttpServerHelpers();
			virtual ~HttpServerHelpers();

			enum ReturnType {
				RequestOk, RequestFinished
			};



			static ReturnType preprocess(TBS::Services::JsonServerParams params, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
	};

} /* namespace jsonrpc */

#endif /* HTTPSERVERHELPERS_H_ */
