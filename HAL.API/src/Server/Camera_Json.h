/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
#ifndef _CAMERA_JSONSERVER_H_
#define _CAMERA_JSONSERVER_H_

#include <Poco/SharedPtr.h>
#include <Poco/BasicEvent.h>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <jsonrpc/rpc.h>
///includes
#include "HAL/API/Camera.h"


namespace HAL { 
	namespace API { 
		namespace Camera { 
			namespace Stub { 
	class Camera_JsonServer : public jsonrpc::AbstractServerInterface<Camera_JsonServer>
		{
			public:
				Camera_JsonServer(jsonrpc::ServiceHandlers & handlers, HAL::API::Camera::ICamera::Ptr interfaceImpl) :
					jsonrpc::AbstractServerInterface<Camera_JsonServer>("HAL.API.Camera.Camera", handlers), interfaceImpl(interfaceImpl) 
					{
						            this->bindAndAddMethod(new jsonrpc::Procedure("Enable", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &Camera_JsonServer::EnableI);
            this->bindAndAddMethod(new jsonrpc::Procedure("Disable", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &Camera_JsonServer::DisableI);
            this->bindAndAddMethod(new jsonrpc::Procedure("GoMinEngine", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &Camera_JsonServer::GoMinEngineI);
            this->bindAndAddMethod(new jsonrpc::Procedure("GoMaxEngine", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &Camera_JsonServer::GoMaxEngineI);
            this->bindAndAddMethod(new jsonrpc::Procedure("GoRelEngine", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL, "speed",jsonrpc::JSON_REAL, NULL), &Camera_JsonServer::GoRelEngineI);
            this->bindAndAddMethod(new jsonrpc::Procedure("GoMinServo1", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &Camera_JsonServer::GoMinServo1I);
            this->bindAndAddMethod(new jsonrpc::Procedure("GoMaxServo1", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &Camera_JsonServer::GoMaxServo1I);
            this->bindAndAddMethod(new jsonrpc::Procedure("GoRelServo1", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL, "speed",jsonrpc::JSON_REAL, NULL), &Camera_JsonServer::GoRelServo1I);
            this->bindAndAddMethod(new jsonrpc::Procedure("GoMinServo2", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &Camera_JsonServer::GoMinServo2I);
            this->bindAndAddMethod(new jsonrpc::Procedure("GoMaxServo2", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &Camera_JsonServer::GoMaxServo2I);
            this->bindAndAddMethod(new jsonrpc::Procedure("GoRelServo2", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL, "speed",jsonrpc::JSON_REAL, NULL), &Camera_JsonServer::GoRelServo2I);

					}
					
					        inline virtual void EnableI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->Enable();
        }

        inline virtual void DisableI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->Disable();
        }

        inline virtual void GoMinEngineI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->GoMinEngine();
        }

        inline virtual void GoMaxEngineI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->GoMaxEngine();
        }

        inline virtual void GoRelEngineI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->GoRelEngine(jsonrpc::Convertor::json2Cpp< double >(request["speed"]));
        }

        inline virtual void GoMinServo1I(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->GoMinServo1();
        }

        inline virtual void GoMaxServo1I(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->GoMaxServo1();
        }

        inline virtual void GoRelServo1I(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->GoRelServo1(jsonrpc::Convertor::json2Cpp< double >(request["speed"]));
        }

        inline virtual void GoMinServo2I(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->GoMinServo2();
        }

        inline virtual void GoMaxServo2I(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->GoMaxServo2();
        }

        inline virtual void GoRelServo2I(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->GoRelServo2(jsonrpc::Convertor::json2Cpp< double >(request["speed"]));
        }


					        void Enable(){
        	 interfaceImpl->Enable();
        }

        void Disable(){
        	 interfaceImpl->Disable();
        }

        void GoMinEngine(){
        	 interfaceImpl->GoMinEngine();
        }

        void GoMaxEngine(){
        	 interfaceImpl->GoMaxEngine();
        }

        void GoRelEngine(const double & speed){
        	 interfaceImpl->GoRelEngine(speed);
        }

        void GoMinServo1(){
        	 interfaceImpl->GoMinServo1();
        }

        void GoMaxServo1(){
        	 interfaceImpl->GoMaxServo1();
        }

        void GoRelServo1(const double & speed){
        	 interfaceImpl->GoRelServo1(speed);
        }

        void GoMinServo2(){
        	 interfaceImpl->GoMinServo2();
        }

        void GoMaxServo2(){
        	 interfaceImpl->GoMaxServo2();
        }

        void GoRelServo2(const double & speed){
        	 interfaceImpl->GoRelServo2(speed);
        }


			private:
				HAL::API::Camera::ICamera::Ptr interfaceImpl;
};
 } 
 } 
 } 
 } 



#endif //_CAMERA_JSONSERVER_H_

