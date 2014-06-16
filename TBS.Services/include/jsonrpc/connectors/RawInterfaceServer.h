/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    httpserver.h
 * @date    31.12.2012
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#ifndef RawWSHttpInterfaceServerCONNECTOR_H_
#define RawWSHttpInterfaceServerCONNECTOR_H_

#include <memory>
#include "Poco/Net/HTTPServer.h"
#include "../ServiceHandlers.h"
#include "TBS/Services/Json/JsonServices.h"

#include "Poco/Net/WebSocket.h"
#include <memory>
#include "jsonrpc/AbstractServerConnector.h"

namespace jsonrpc
{


    /**
     * This class provides an embedded HTTP Server, based on Mongoose, to handle incoming Requests and send HTTP 1.1
     * valid responses.
     * Note that this class will always send HTTP-Status 200, even though an JSON-RPC Error might have occurred. Please
     * always check for the JSON-RPC Error Header.
     */
    class RawInterfaceServer: public AbstractServerConnector
    {
        public:


    		RawInterfaceServer(const TBS::Services::JsonServerParams & p);
            virtual ~RawInterfaceServer();

            virtual bool StartListening();
            virtual bool StopListening();

            ServiceHandlers & handlers();

        private:
            TBS::Services::JsonServerParams p;
            ServiceHandlers handlers_;
            std::unique_ptr<Poco::Net::TCPServer> srv;


    };

} /* namespace jsonrpc */
#endif /* HTTPSERVERCONNECTOR_H_ */
