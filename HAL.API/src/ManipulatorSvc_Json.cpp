/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
///includes
#include "HAL/API/ManipulatorSvc_Json.h"
#include "Client/Manipulator_Json.h"
#include "Server/Manipulator_Json.h"

#include <TBS/Services/Json/JsonServicesImpl.h>

//convertors
namespace jsonrpc {template<>
class InternalConvertor<HAL::API::Manipulator::MotorInfo> { 
	public:
		static HAL::API::Manipulator::MotorInfo json2Cpp(const Json::Value & val) {
		   using namespace HAL::API::Manipulator;
		   HAL::API::Manipulator::MotorInfo var;
		   		var.position =  Convertor::json2Cpp< double > (val["position"]);
		   		var.current =  Convertor::json2Cpp< double > (val["current"]);
			return var;
		}
		static Json::Value cpp2Json(const HAL::API::Manipulator::MotorInfo & val) {
		    using namespace HAL::API::Manipulator;
		    ::Json::Value retval(::Json::objectValue);
		    retval["position"] = Convertor::cpp2Json< double >(val.position);
		    retval["current"] = Convertor::cpp2Json< double >(val.current);
			return retval;
		}
};
}

namespace HAL { 
	namespace API { 
		namespace Manipulator { 
			namespace Json { 
	   Client::Client(const TBS::Services::JsonClientParams & ch) : 
	       ch(ch){
	   }
	   Client::~Client(){}
	   
	   HAL::API::Manipulator::IManipulator & Client::Manipulator(){
   if (!manipulator_) {      manipulator_ =  new HAL::API::Manipulator::Stub::Manipulator_JsonClient(TBS::Services::createClientConnector(HAL::API::Manipulator::IManipulator::name(), ch));
   }   return *manipulator_;
}

	   
	   
	   Server::Ptr Server::createJsonServer(const TBS::Services::JsonServerParams & p){
		   return new Server(new TBS::Services::JsonCommChannelHolder(p));
	   }
	   Server::Ptr Server::createJsonpServer(const TBS::Services::JsonServerParams & p){
		   return new Server(new TBS::Services::JsonpCommChannelHolder(p));
	   }
	   Server::Ptr Server::createWsServer(const TBS::Services::JsonServerParams & p){
		   return new Server(new TBS::Services::WsCommChannelHolder(p));
	   }
	   Server::Ptr Server::createRawServer(const TBS::Services::JsonServerParams & p){
		   return new Server(new TBS::Services::RawCommChannelHolder(p));
	   }
	   
	   
	   Server::Server(TBS::Services::ICommChannelHolder::Ptr ch) : 
	   	   channel(ch){
		   
	    } 
	    Server::~Server(){}
	    void Server::start(){ 
	   	   channel.cast<TBS::Services::AJsonCommChannelHolder>()->getInterface().StartListening();
	    } 
	    void Server::stop(){ 
	   	   channel.cast<TBS::Services::AJsonCommChannelHolder>()->getInterface().StopListening();
	    } 
	    
	   TBS::Services::IServer::Ptr Server::createManipulator(HAL::API::Manipulator::IManipulator::Ptr impl){
   return new TBS::Services::JsonServerImpl<HAL::API::Manipulator::IManipulator, HAL::API::Manipulator::Stub::Manipulator_JsonServer>(this->channel.cast<TBS::Services::AJsonCommChannelHolder>()->getInterface(), impl);
}

 } 
 } 
 } 
 } 



