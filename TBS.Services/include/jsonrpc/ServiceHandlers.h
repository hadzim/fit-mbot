/*
 * ServiceServer.h
 *
 *  Created on: Oct 3, 2013
 *      Author: root
 */

#ifndef SERVICESERVER_H_
#define SERVICESERVER_H_

#include <map>
#include "jsonrpc/rpcprotocolserver.h"

namespace jsonrpc {

	class ServiceHandlers {
		public:

			typedef std::map <std::string, RpcProtocolServer::Ptr> Handlers;

			ServiceHandlers();
			virtual ~ServiceHandlers();

			void registerHandler(std::string name, RpcProtocolServer::Ptr service);
			void unregisterHandler(std::string name);
			RpcProtocolServer::Ptr getHandler(std::string name);
		private:
			Handlers handlers;
	};

} /* namespace jsonrpc */
#endif /* SERVICESERVER_H_ */
