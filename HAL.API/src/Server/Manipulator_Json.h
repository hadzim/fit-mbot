/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
#ifndef _MANIPULATOR_JSONSERVER_H_
#define _MANIPULATOR_JSONSERVER_H_

#include <Poco/SharedPtr.h>
#include <Poco/BasicEvent.h>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <jsonrpc/rpc.h>
///includes
#include "HAL/API/Manipulator.h"


namespace HAL { 
	namespace API { 
		namespace Manipulator { 
			namespace Stub { 
	class Manipulator_JsonServer : public jsonrpc::AbstractServerInterface<Manipulator_JsonServer>
		{
			public:
				Manipulator_JsonServer(jsonrpc::ServiceHandlers & handlers, HAL::API::Manipulator::IManipulator::Ptr interfaceImpl) :
					jsonrpc::AbstractServerInterface<Manipulator_JsonServer>("HAL.API.Manipulator.Manipulator", handlers), interfaceImpl(interfaceImpl) 
					{
						            this->bindAndAddMethod(new jsonrpc::Procedure("Enable", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &Manipulator_JsonServer::EnableI);
            this->bindAndAddMethod(new jsonrpc::Procedure("Disable", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &Manipulator_JsonServer::DisableI);
            this->bindAndAddMethod(new jsonrpc::Procedure("StartRotation", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL, "speed",jsonrpc::JSON_REAL, NULL), &Manipulator_JsonServer::StartRotationI);
            this->bindAndAddMethod(new jsonrpc::Procedure("StopRotation", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &Manipulator_JsonServer::StopRotationI);
            this->bindAndAddMethod(new jsonrpc::Procedure("StartJoint1", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL, "speed",jsonrpc::JSON_REAL, NULL), &Manipulator_JsonServer::StartJoint1I);
            this->bindAndAddMethod(new jsonrpc::Procedure("StopJoint1", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &Manipulator_JsonServer::StopJoint1I);
            this->bindAndAddMethod(new jsonrpc::Procedure("StartJoint2", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL, "speed",jsonrpc::JSON_REAL, NULL), &Manipulator_JsonServer::StartJoint2I);
            this->bindAndAddMethod(new jsonrpc::Procedure("StopJoint2", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &Manipulator_JsonServer::StopJoint2I);
            this->bindAndAddMethod(new jsonrpc::Procedure("StartHolder", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL, "speed",jsonrpc::JSON_REAL, NULL), &Manipulator_JsonServer::StartHolderI);
            this->bindAndAddMethod(new jsonrpc::Procedure("StopHolder", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &Manipulator_JsonServer::StopHolderI);
            this->bindAndAddMethod(new jsonrpc::Procedure("SetHolderThreshold", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL, "threshold",jsonrpc::JSON_REAL, NULL), &Manipulator_JsonServer::SetHolderThresholdI);
            this->bindAndAddMethod(new jsonrpc::Procedure("GetStatus", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &Manipulator_JsonServer::GetStatusI);

					}
					
					        inline virtual void EnableI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->Enable();
        }

        inline virtual void DisableI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->Disable();
        }

        inline virtual void StartRotationI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->StartRotation(jsonrpc::Convertor::json2Cpp< double >(request["speed"]));
        }

        inline virtual void StopRotationI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->StopRotation();
        }

        inline virtual void StartJoint1I(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->StartJoint1(jsonrpc::Convertor::json2Cpp< double >(request["speed"]));
        }

        inline virtual void StopJoint1I(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->StopJoint1();
        }

        inline virtual void StartJoint2I(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->StartJoint2(jsonrpc::Convertor::json2Cpp< double >(request["speed"]));
        }

        inline virtual void StopJoint2I(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->StopJoint2();
        }

        inline virtual void StartHolderI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->StartHolder(jsonrpc::Convertor::json2Cpp< double >(request["speed"]));
        }

        inline virtual void StopHolderI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->StopHolder();
        }

        inline virtual void SetHolderThresholdI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->SetHolderThreshold(jsonrpc::Convertor::json2Cpp< double >(request["threshold"]));
        }

        inline virtual void GetStatusI(const ::Json::Value& request, ::Json::Value& response) 
        {
        	MotorInfo tmpvar_rotation;
MotorInfo tmpvar_joint1;
MotorInfo tmpvar_joint2;
MotorInfo tmpvar_holder;

        	this->GetStatus(tmpvar_rotation, tmpvar_joint1, tmpvar_joint2, tmpvar_holder);
        	response["rotation"] = jsonrpc::Convertor::cpp2Json<MotorInfo >(tmpvar_rotation);
response["joint1"] = jsonrpc::Convertor::cpp2Json<MotorInfo >(tmpvar_joint1);
response["joint2"] = jsonrpc::Convertor::cpp2Json<MotorInfo >(tmpvar_joint2);
response["holder"] = jsonrpc::Convertor::cpp2Json<MotorInfo >(tmpvar_holder);

        }


					        void Enable(){
        	 interfaceImpl->Enable();
        }

        void Disable(){
        	 interfaceImpl->Disable();
        }

        void StartRotation(const double & speed){
        	 interfaceImpl->StartRotation(speed);
        }

        void StopRotation(){
        	 interfaceImpl->StopRotation();
        }

        void StartJoint1(const double & speed){
        	 interfaceImpl->StartJoint1(speed);
        }

        void StopJoint1(){
        	 interfaceImpl->StopJoint1();
        }

        void StartJoint2(const double & speed){
        	 interfaceImpl->StartJoint2(speed);
        }

        void StopJoint2(){
        	 interfaceImpl->StopJoint2();
        }

        void StartHolder(const double & speed){
        	 interfaceImpl->StartHolder(speed);
        }

        void StopHolder(){
        	 interfaceImpl->StopHolder();
        }

        void SetHolderThreshold(const double & threshold){
        	 interfaceImpl->SetHolderThreshold(threshold);
        }

        void GetStatus(MotorInfo & rotation, MotorInfo & joint1, MotorInfo & joint2, MotorInfo & holder){
        	 interfaceImpl->GetStatus(rotation, joint1, joint2, holder);
        }


			private:
				HAL::API::Manipulator::IManipulator::Ptr interfaceImpl;
};
 } 
 } 
 } 
 } 



#endif //_MANIPULATOR_JSONSERVER_H_

