/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
///includes
#include "HAL/API/CameraSvc_Json.h"
#include "Client/Camera_Json.h"
#include "Server/Camera_Json.h"

#include <TBS/Services/Json/JsonServicesImpl.h>

//convertors
namespace jsonrpc {}

namespace HAL { 
	namespace API { 
		namespace Camera { 
			namespace Json { 
	   Client::Client(const TBS::Services::JsonClientParams & ch) : 
	       ch(ch){
	   }
	   Client::~Client(){}
	   
	   HAL::API::Camera::ICamera & Client::Camera(){
   if (!camera_) {      camera_ =  new HAL::API::Camera::Stub::Camera_JsonClient(TBS::Services::createClientConnector(HAL::API::Camera::ICamera::name(), ch));
   }   return *camera_;
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
	    
	   TBS::Services::IServer::Ptr Server::createCamera(HAL::API::Camera::ICamera::Ptr impl){
   return new TBS::Services::JsonServerImpl<HAL::API::Camera::ICamera, HAL::API::Camera::Stub::Camera_JsonServer>(this->channel.cast<TBS::Services::AJsonCommChannelHolder>()->getInterface(), impl);
}

 } 
 } 
 } 
 } 



