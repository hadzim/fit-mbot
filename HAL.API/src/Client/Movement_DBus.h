/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
#ifndef _NO_DBUS 
#ifndef _MOVEMENT_DBUSCLIENT_H_
#define _MOVEMENT_DBUSCLIENT_H_

#include <Poco/SharedPtr.h>
#include <Poco/BasicEvent.h>
#include <Poco/Exception.h>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <memory>
#include <dbus-c++/dbus.h>
#include <dbus/dbus-protocol.h>
///includes
#include "HAL/API/Movement.h"


namespace HAL { 
	namespace API { 
		namespace Movement { 
			namespace Stub { 
       class Movement_DBusClient : public ::DBus::InterfaceProxy, public HAL::API::Movement::IMovement {
			public:
				typedef Poco::SharedPtr <Movement_DBusClient> Ptr;
				
				Movement_DBusClient() : ::DBus::InterfaceProxy("com.HAL.API.Movement.Movement"){
							connect_signal(Movement_DBusClient, StatusChanged, _StatusChanged_sigstub);

				}
				virtual ~Movement_DBusClient() {
				}

				
				static const std::string & dbuspath(){ static std::string val = "/com/HAL/API/Movement"; return val; }
				static const std::string & dbusname(){ static std::string val = "com.HAL.API.Movement.Movement"; return val; }
				
				
 //methods 
				virtual void Move(const double & speedLeft, const double & speedRight){		try {
		::DBus::CallMessage call;
		::DBus::MessageIter wi = call.writer();

		wi << speedLeft;
		wi << speedRight;
		call.member("Move");
		::DBus::Message ret = invoke_method (call);
		} catch (::DBus::Error & err){
			if (strcmp(err.name(), DBUS_ERROR_FAILED) == 0){
				throw ::TBS::Services::RuntimeServiceException(err.message());
			} else {
				throw ::TBS::Services::ChannelServiceException(err.what());
			}
		}
	}

virtual void Stop(){		try {
		::DBus::CallMessage call;
		call.member("Stop");
		::DBus::Message ret = invoke_method (call);
		} catch (::DBus::Error & err){
			if (strcmp(err.name(), DBUS_ERROR_FAILED) == 0){
				throw ::TBS::Services::RuntimeServiceException(err.message());
			} else {
				throw ::TBS::Services::ChannelServiceException(err.what());
			}
		}
	}

virtual void SetPosition(const int64_t & posLeft, const int64_t & posRight){		try {
		::DBus::CallMessage call;
		::DBus::MessageIter wi = call.writer();

		wi << posLeft;
		wi << posRight;
		call.member("SetPosition");
		::DBus::Message ret = invoke_method (call);
		} catch (::DBus::Error & err){
			if (strcmp(err.name(), DBUS_ERROR_FAILED) == 0){
				throw ::TBS::Services::RuntimeServiceException(err.message());
			} else {
				throw ::TBS::Services::ChannelServiceException(err.what());
			}
		}
	}

virtual void GetStatus(double & speedLeft, double & speedRight, int64_t & posLeft, int64_t & posRight){		try {
		::DBus::CallMessage call;
		call.member("GetStatus");
		::DBus::Message ret = invoke_method (call);
		::DBus::MessageIter ri = ret.reader();

		ri >> speedLeft;
		ri >> speedRight;
		ri >> posLeft;
		ri >> posRight;
		} catch (::DBus::Error & err){
			if (strcmp(err.name(), DBUS_ERROR_FAILED) == 0){
				throw ::TBS::Services::RuntimeServiceException(err.message());
			} else {
				throw ::TBS::Services::ChannelServiceException(err.what());
			}
		}
	}


		private: 
					void _StatusChanged_sigstub(const ::DBus::SignalMessage &sig){
		::DBus::MessageIter ri = sig.reader();

		double _speedLeft;
		ri >> _speedLeft;
		double _speedRight;
		ri >> _speedRight;
		int64_t _posLeft;
		ri >> _posLeft;
		int64_t _posRight;
		ri >> _posRight;
		StatusChangedArg sig_arg;
		sig_arg.speedLeft = _speedLeft;
		sig_arg.speedRight = _speedRight;
		sig_arg.posLeft = _posLeft;
		sig_arg.posRight = _posRight;

		//raise poco event
		StatusChanged(this, sig_arg);
	}

			};
 } 
 } 
 } 
 } 



#endif //_MOVEMENT_DBUSCLIENT_H_
#endif

