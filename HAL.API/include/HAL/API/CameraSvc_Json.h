/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
#ifndef _CAMERA_SERVICE_JSON_H_
#define _CAMERA_SERVICE_JSON_H_

#include <Poco/SharedPtr.h>
#include <Poco/BasicEvent.h>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <TBS/Services/Services.h>
#include <TBS/Services/Json/JsonServices.h>
///includes
#include "HAL/API/Camera.h"


namespace HAL { 
	namespace API { 
		namespace Camera { 
			namespace Json { 
       class GEN_SERVICE_API Client {
			public:
				typedef Poco::SharedPtr <Client> Ptr;
				
				Client(const TBS::Services::JsonClientChannel & ch);
				~Client();
				
				
 //methods 
				HAL::API::Camera::ICamera & Camera();

				
		private: 
				TBS::Services::JsonClientChannel ch;
				HAL::API::Camera::ICamera::Ptr camera_;

			};
			
			
		class GEN_SERVICE_API Server {
			public:
				typedef Poco::SharedPtr<Server> Ptr;
				Server(const TBS::Services::JsonServerChannel & ch);
				~Server();
				
				void start();
				void stop();
			public:
				TBS::Services::IServer::Ptr createCamera(HAL::API::Camera::ICamera::Ptr impl);

				
			private:
				TBS::Services::ICommChannelHolder::Ptr channel;
		};
 } 
 } 
 } 
 } 

#endif //_CAMERA_SERVICE_H_

