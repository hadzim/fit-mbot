#ifndef _NO_DBUS 
/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
///includes
#include "HAL/API/BioRadarSvc_DBus.h"
#include "Client/BioRadar_DBus.h"
#include "Server/BioRadar_DBus.h"

#include <TBS/Services/DBus/DBusServicesImpl.h>



namespace HAL { 
	namespace API { 
		namespace BioRadar { 
			namespace DBus { 
	   Client::Client(TBS::Services::ICommChannelHolder::Ptr ch) : 
	       ch(ch), comChannelHolder(new TBS::Services::CommunicationChannelHolder(ch)) {
	   }
	   Client::Client() : 
		   ch(TBS::Services::DBusCommChannelProvider::getDefaultCommChannel()), comChannelHolder(new TBS::Services::CommunicationChannelHolder(ch)) {
	   }
	   HAL::API::BioRadar::IBase & Client::Base(){
   if (!base_) {      base_ =  new TBS::Services::DBusClientImpl<HAL::API::BioRadar::Stub::Base_DBusClient>(comChannelHolder->getConnection());
   }   return *base_;
}

	   
	   
	   Server::Server(TBS::Services::ICommChannelHolder::Ptr ch) : 
	   	   ch(ch){
		   
	    } 
		Server::Server() : 
	   	   ch(TBS::Services::DBusCommChannelProvider::getDefaultCommChannel()){
		   
	    } 
	    
	   TBS::Services::IServer::Ptr Server::createBase(HAL::API::BioRadar::IBase::Ptr impl){
   return new TBS::Services::DBusServerImpl<HAL::API::BioRadar::IBase, HAL::API::BioRadar::Stub::Base_DBusServer>(ch, impl);
}

 } 
 } 
 } 
 } 


#endif 

