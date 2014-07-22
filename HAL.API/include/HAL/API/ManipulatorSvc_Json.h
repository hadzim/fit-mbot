/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
#ifndef _MANIPULATOR_SERVICE_JSON_H_
#define _MANIPULATOR_SERVICE_JSON_H_

#include <Poco/SharedPtr.h>
#include <Poco/BasicEvent.h>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <TBS/Services/Services.h>
#include <TBS/Services/Json/JsonServices.h>
///includes
#include "HAL/API/Manipulator.h"


namespace HAL { 
	namespace API { 
		namespace Manipulator { 
			namespace Json { 
       class GEN_SERVICE_API Client {
			public:
				typedef Poco::SharedPtr <Client> Ptr;
				
				Client(const TBS::Services::JsonClientParams & ch);
				~Client();
				
				
 //methods 
				HAL::API::Manipulator::IManipulator & Manipulator();

				
		private: 
				TBS::Services::JsonClientParams ch;
				HAL::API::Manipulator::IManipulator::Ptr manipulator_;

			};
			
			
		class GEN_SERVICE_API Server {
			public:
				typedef Poco::SharedPtr<Server> Ptr;
				
				static Server::Ptr createJsonServer(const TBS::Services::JsonServerParams & p);
				static Server::Ptr createJsonpServer(const TBS::Services::JsonServerParams & p);
				static Server::Ptr createWsServer(const TBS::Services::JsonServerParams & p);
				static Server::Ptr createRawServer(const TBS::Services::JsonServerParams & p);
				
				~Server();
				
				void start();
				void stop();
			public:
				TBS::Services::IServer::Ptr createManipulator(HAL::API::Manipulator::IManipulator::Ptr impl);

				
			private:
				Server(TBS::Services::ICommChannelHolder::Ptr ch);
				TBS::Services::ICommChannelHolder::Ptr channel;
		};
 } 
 } 
 } 
 } 

#endif //_MANIPULATOR_SERVICE_H_
