/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    serverconnector.h
 * @date    31.12.2012
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#ifndef SERVERCONNECTOR_H_
#define SERVERCONNECTOR_H_

#include <string>
#include <Poco/SharedPtr.h>
#include "jsonrpc/ServiceHandlers.h"



namespace jsonrpc
{
    
	class AbstractServerConnector {

		public:
			typedef Poco::SharedPtr <AbstractServerConnector> Ptr;

			virtual ~AbstractServerConnector(){}

			virtual bool StartListening() = 0;

			virtual bool StopListening() = 0;

			virtual ServiceHandlers & handlers() = 0;

	};


} /* namespace jsonrpc */
#endif /* SERVERCONNECTOR_H_ */
