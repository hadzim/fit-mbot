/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
#ifndef _BIORADAR_SERVICE_JSON_H_
#define _BIORADAR_SERVICE_JSON_H_

#include <Poco/SharedPtr.h>
#include <Poco/BasicEvent.h>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <TBS/Services/Services.h>
#include <TBS/Services/Json/JsonServices.h>
///includes
#include "HAL/API/BioRadar.h"


namespace HAL { 
	namespace API { 
		namespace BioRadar { 
			namespace Json { 
       class GEN_SERVICE_API Client {
			public:
				typedef Poco::SharedPtr <Client> Ptr;
				
				Client(const TBS::Services::JsonClientChannel & ch);
				~Client();
				
				
 //methods 
				HAL::API::BioRadar::IBioRadar & BioRadar();

				
		private: 
				TBS::Services::JsonClientChannel ch;
				HAL::API::BioRadar::IBioRadar::Ptr bioradar_;

			};
			
			
		class GEN_SERVICE_API Server {
			public:
				typedef Poco::SharedPtr<Server> Ptr;
				Server(const TBS::Services::JsonServerChannel & ch);
				~Server();
				
				void start();
				void stop();
			public:
				TBS::Services::IServer::Ptr createBioRadar(HAL::API::BioRadar::IBioRadar::Ptr impl);

				
			private:
				TBS::Services::ICommChannelHolder::Ptr channel;
		};
 } 
 } 
 } 
 } 

#endif //_BIORADAR_SERVICE_H_

