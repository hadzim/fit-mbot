/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
#ifndef _MOVEMENT_JSONSERVER_H_
#define _MOVEMENT_JSONSERVER_H_

#include <Poco/SharedPtr.h>
#include <Poco/BasicEvent.h>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <jsonrpc/rpc.h>
///includes
#include "HAL/API/Movement.h"


namespace HAL { 
	namespace API { 
		namespace Movement { 
			namespace Stub { 
	class Movement_JsonServer : public jsonrpc::AbstractServerInterface<Movement_JsonServer>
		{
			public:
				Movement_JsonServer(jsonrpc::ServiceHandlers & handlers, HAL::API::Movement::IMovement::Ptr interfaceImpl) :
					jsonrpc::AbstractServerInterface<Movement_JsonServer>("HAL.API.Movement.Movement", handlers), interfaceImpl(interfaceImpl) 
					{
						            this->bindAndAddMethod(new jsonrpc::Procedure("Move", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL, "speedLeft",jsonrpc::JSON_REAL,"speedRight",jsonrpc::JSON_REAL, NULL), &Movement_JsonServer::MoveI);
            this->bindAndAddMethod(new jsonrpc::Procedure("Stop", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &Movement_JsonServer::StopI);
            this->bindAndAddMethod(new jsonrpc::Procedure("SetPosition", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL, "posLeft",jsonrpc::JSON_INTEGER,"posRight",jsonrpc::JSON_INTEGER, NULL), &Movement_JsonServer::SetPositionI);
            this->bindAndAddMethod(new jsonrpc::Procedure("GetStatus", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_NULL,  NULL), &Movement_JsonServer::GetStatusI);

					}
					
					        inline virtual void MoveI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->Move(jsonrpc::Convertor::json2Cpp< double >(request["speedLeft"]), jsonrpc::Convertor::json2Cpp< double >(request["speedRight"]));
        }

        inline virtual void StopI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->Stop();
        }

        inline virtual void SetPositionI(const ::Json::Value& request, ::Json::Value& response) 
        {
            this->SetPosition(jsonrpc::Convertor::json2Cpp< int64_t >(request["posLeft"]), jsonrpc::Convertor::json2Cpp< int64_t >(request["posRight"]));
        }

        inline virtual void GetStatusI(const ::Json::Value& request, ::Json::Value& response) 
        {
        	double tmpvar_speedLeft;
double tmpvar_speedRight;
int64_t tmpvar_posLeft;
int64_t tmpvar_posRight;

        	this->GetStatus(tmpvar_speedLeft, tmpvar_speedRight, tmpvar_posLeft, tmpvar_posRight);
        	response["speedLeft"] = jsonrpc::Convertor::cpp2Json<double >(tmpvar_speedLeft);
response["speedRight"] = jsonrpc::Convertor::cpp2Json<double >(tmpvar_speedRight);
response["posLeft"] = jsonrpc::Convertor::cpp2Json<int64_t >(tmpvar_posLeft);
response["posRight"] = jsonrpc::Convertor::cpp2Json<int64_t >(tmpvar_posRight);

        }


					        void Move(const double & speedLeft, const double & speedRight){
        	 interfaceImpl->Move(speedLeft, speedRight);
        }

        void Stop(){
        	 interfaceImpl->Stop();
        }

        void SetPosition(const int64_t & posLeft, const int64_t & posRight){
        	 interfaceImpl->SetPosition(posLeft, posRight);
        }

        void GetStatus(double & speedLeft, double & speedRight, int64_t & posLeft, int64_t & posRight){
        	 interfaceImpl->GetStatus(speedLeft, speedRight, posLeft, posRight);
        }


			private:
				HAL::API::Movement::IMovement::Ptr interfaceImpl;
};
 } 
 } 
 } 
 } 



#endif //_MOVEMENT_JSONSERVER_H_

