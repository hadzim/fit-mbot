/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
 #ifndef _NO_DBUS 
#ifndef _MOVEMENT_SERVICE_DBUS_H_
#define _MOVEMENT_SERVICE_DBUS_H_

#include <Poco/SharedPtr.h>
#include <Poco/BasicEvent.h>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <TBS/Services/Services.h>
#include <TBS/Services/DBus/DBusServices.h>
///includes
#include "HAL/API/Movement.h"

namespace TBS {
	namespace Services {
		class CommunicationChannelHolder;
	}
}

namespace HAL { 
	namespace API { 
		namespace Movement { 
			namespace DBus { 
       class GEN_SERVICE_API Client {
			public:
				typedef Poco::SharedPtr <Client> Ptr;
				
				//with given dbus dispatcher via DBusCommChannelProvider
				Client(TBS::Services::ICommChannelHolder::Ptr ch);
				//with default dbus dispatcher
				Client();
				~Client();
				
				HAL::API::Movement::IMovement & Movement();

				
		private: 
				TBS::Services::ICommChannelHolder::Ptr ch;
				std::auto_ptr<TBS::Services::CommunicationChannelHolder> comChannelHolder;
				HAL::API::Movement::IMovement::Ptr movement_;

			};
			
			
		class GEN_SERVICE_API Server {
			public:
				typedef Poco::SharedPtr<Server> Ptr;
				//with given dbus dispatcher via DBusCommChannelProvider
				Server(TBS::Services::ICommChannelHolder::Ptr ch);
				//uses default dbus dispatcher
				Server();
				~Server();
				
			public:
				TBS::Services::IServer::Ptr createMovement(HAL::API::Movement::IMovement::Ptr impl);

				
			private:
				TBS::Services::ICommChannelHolder::Ptr ch;
		};
 } 
 } 
 } 
 } 

#endif //_MOVEMENT_SERVICE_H_
#endif

