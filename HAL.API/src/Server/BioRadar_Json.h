/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
#ifndef _BIORADAR_JSONSERVER_H_
#define _BIORADAR_JSONSERVER_H_

#include <Poco/SharedPtr.h>
#include <Poco/BasicEvent.h>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <jsonrpc/rpc.h>
///includes
#include "HAL/API/BioRadar.h"


namespace HAL { 
	namespace API { 
		namespace BioRadar { 
			namespace Stub { 
	class BioRadar_JsonServer : public jsonrpc::AbstractServerInterface<BioRadar_JsonServer>
		{
			public:
				BioRadar_JsonServer(jsonrpc::ServiceHandlers & handlers, HAL::API::BioRadar::IBioRadar::Ptr interfaceImpl) :
					jsonrpc::AbstractServerInterface<BioRadar_JsonServer>("HAL.API.BioRadar.BioRadar", handlers), interfaceImpl(interfaceImpl) 
					{
						            this->bindAndAddMethod(new jsonrpc::Procedure("Enable", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &BioRadar_JsonServer::EnableI);
            this->bindAndAddMethod(new jsonrpc::Procedure("Disable", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &BioRadar_JsonServer::DisableI);
            this->bindAndAddMethod(new jsonrpc::Procedure("GoMinBase", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &BioRadar_JsonServer::GoMinBaseI);
            this->bindAndAddMethod(new jsonrpc::Procedure("GoMaxBase", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &BioRadar_JsonServer::GoMaxBaseI);
            this->bindAndAddMethod(new jsonrpc::Procedure("GoRelBase", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL, "speed",jsonrpc::JSON_REAL, NULL), &BioRadar_JsonServer::GoRelBaseI);
            this->bindAndAddMethod(new jsonrpc::Procedure("GoMinAntenna", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &BioRadar_JsonServer::GoMinAntennaI);
            this->bindAndAddMethod(new jsonrpc::Procedure("GoMaxAntenna", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &BioRadar_JsonServer::GoMaxAntennaI);
            this->bindAndAddMethod(new jsonrpc::Procedure("GoRelAntenna", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL, "speed",jsonrpc::JSON_REAL, NULL), &BioRadar_JsonServer::GoRelAntennaI);
            this->bindAndAddMethod(new jsonrpc::Procedure("GetMotorStatus", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_OBJECT, "isBase",jsonrpc::JSON_BOOLEAN, NULL), &BioRadar_JsonServer::GetMotorStatusI);
            this->bindAndAddMethod(new jsonrpc::Procedure("GetAntenaStatus", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_ARRAY,  NULL), &BioRadar_JsonServer::GetAntenaStatusI);

					}
					
					        inline virtual void EnableI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->Enable();
        }

        inline virtual void DisableI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->Disable();
        }

        inline virtual void GoMinBaseI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->GoMinBase();
        }

        inline virtual void GoMaxBaseI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->GoMaxBase();
        }

        inline virtual void GoRelBaseI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->GoRelBase(jsonrpc::Convertor::json2Cpp< double >(request["speed"]));
        }

        inline virtual void GoMinAntennaI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->GoMinAntenna();
        }

        inline virtual void GoMaxAntennaI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->GoMaxAntenna();
        }

        inline virtual void GoRelAntennaI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->GoRelAntenna(jsonrpc::Convertor::json2Cpp< double >(request["speed"]));
        }

        inline virtual void GetMotorStatusI(const ::Json::Value& request, ::Json::Value& response) 
        {
            response = jsonrpc::Convertor::cpp2Json< MotorInfo >(this->GetMotorStatus(jsonrpc::Convertor::json2Cpp< bool >(request["isBase"])));
        }

        inline virtual void GetAntenaStatusI(const ::Json::Value& request, ::Json::Value& response) 
        {
            response = jsonrpc::Convertor::cpp2Json< std::vector< TouchInfo > >(this->GetAntenaStatus());
        }


					        void Enable(){
        	 interfaceImpl->Enable();
        }

        void Disable(){
        	 interfaceImpl->Disable();
        }

        void GoMinBase(){
        	 interfaceImpl->GoMinBase();
        }

        void GoMaxBase(){
        	 interfaceImpl->GoMaxBase();
        }

        void GoRelBase(const double & speed){
        	 interfaceImpl->GoRelBase(speed);
        }

        void GoMinAntenna(){
        	 interfaceImpl->GoMinAntenna();
        }

        void GoMaxAntenna(){
        	 interfaceImpl->GoMaxAntenna();
        }

        void GoRelAntenna(const double & speed){
        	 interfaceImpl->GoRelAntenna(speed);
        }

        MotorInfo GetMotorStatus(const bool & isBase){
        	return interfaceImpl->GetMotorStatus(isBase);
        }

        std::vector< TouchInfo > GetAntenaStatus(){
        	return interfaceImpl->GetAntenaStatus();
        }


			private:
				HAL::API::BioRadar::IBioRadar::Ptr interfaceImpl;
};
 } 
 } 
 } 
 } 



#endif //_BIORADAR_JSONSERVER_H_

