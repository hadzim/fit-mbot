/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
///includes
#include "HAL/API/BioRadarSvc_Json.h"
#include "Client/BioRadar_Json.h"
#include "Server/BioRadar_Json.h"

#include <TBS/Services/Json/JsonServicesImpl.h>

//convertors
namespace jsonrpc {template<>
class InternalConvertor<HAL::API::BioRadar::MotorInfo> { 
	public:
		static HAL::API::BioRadar::MotorInfo json2Cpp(const Json::Value & val) {
		   using namespace HAL::API::BioRadar;
		   HAL::API::BioRadar::MotorInfo var;
		   		var.touchMin =  Convertor::json2Cpp< bool > (val["touchMin"]);
		   		var.touchMax =  Convertor::json2Cpp< bool > (val["touchMax"]);
		   		var.position =  Convertor::json2Cpp< double > (val["position"]);
		   		var.positionError =  Convertor::json2Cpp< bool > (val["positionError"]);
			return var;
		}
		static Json::Value cpp2Json(const HAL::API::BioRadar::MotorInfo & val) {
		    using namespace HAL::API::BioRadar;
		    ::Json::Value retval(::Json::objectValue);
		    retval["touchMin"] = Convertor::cpp2Json< bool >(val.touchMin);
		    retval["touchMax"] = Convertor::cpp2Json< bool >(val.touchMax);
		    retval["position"] = Convertor::cpp2Json< double >(val.position);
		    retval["positionError"] = Convertor::cpp2Json< bool >(val.positionError);
			return retval;
		}
};
template<>
class InternalConvertor<HAL::API::BioRadar::TouchInfo> { 
	public:
		static HAL::API::BioRadar::TouchInfo json2Cpp(const Json::Value & val) {
		   using namespace HAL::API::BioRadar;
		   HAL::API::BioRadar::TouchInfo var;
		   		var.isTouch =  Convertor::json2Cpp< bool > (val["isTouch"]);
		   		var.distance =  Convertor::json2Cpp< double > (val["distance"]);
			return var;
		}
		static Json::Value cpp2Json(const HAL::API::BioRadar::TouchInfo & val) {
		    using namespace HAL::API::BioRadar;
		    ::Json::Value retval(::Json::objectValue);
		    retval["isTouch"] = Convertor::cpp2Json< bool >(val.isTouch);
		    retval["distance"] = Convertor::cpp2Json< double >(val.distance);
			return retval;
		}
};
}

namespace HAL { 
	namespace API { 
		namespace BioRadar { 
			namespace Json { 
	   Client::Client(const TBS::Services::JsonClientParams & ch) : 
	       ch(ch){
	   }
	   Client::~Client(){}
	   
	   HAL::API::BioRadar::IBioRadar & Client::BioRadar(){
   if (!bioradar_) {      bioradar_ =  new HAL::API::BioRadar::Stub::BioRadar_JsonClient(TBS::Services::createClientConnector(HAL::API::BioRadar::IBioRadar::name(), ch));
   }   return *bioradar_;
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
	    
	   TBS::Services::IServer::Ptr Server::createBioRadar(HAL::API::BioRadar::IBioRadar::Ptr impl){
   return new TBS::Services::JsonServerImpl<HAL::API::BioRadar::IBioRadar, HAL::API::BioRadar::Stub::BioRadar_JsonServer>(this->channel.cast<TBS::Services::AJsonCommChannelHolder>()->getInterface(), impl);
}

 } 
 } 
 } 
 } 



