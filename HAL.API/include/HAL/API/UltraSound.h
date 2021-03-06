/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
#ifndef _ULTRASOUND_H_
#define _ULTRASOUND_H_

#include <Poco/SharedPtr.h>
#include <Poco/BasicEvent.h>
#include "TBS/Services/Types.h"
#include <string>
#include <vector>
#include <map>

namespace TBS{ namespace Services{ namespace Introspection{ class Class; struct Struct; } } } 


namespace HAL { 
	namespace API { 
		namespace UltraSound { 
       struct TouchInfo {
				
				static std::string name(){
					static std::string n = "TouchInfo";
					return n;
				}
				static const ::TBS::Services::Introspection::Struct & introspection();
				
 //members 
						int32_t distance;

				
			};
 } 
 } 
 } 


namespace HAL { 
	namespace API { 
		namespace UltraSound { 
       struct TouchSensors {
				
				static std::string name(){
					static std::string n = "TouchSensors";
					return n;
				}
				static const ::TBS::Services::Introspection::Struct & introspection();
				
 //members 
						TouchInfo left;
		TouchInfo right;

				
			};
 } 
 } 
 } 




namespace HAL { 
	namespace API { 
		namespace UltraSound { 
	   /** [interface] IUltraSound:  */
       class GEN_SERVICE_API IUltraSound {
			public:
				typedef Poco::SharedPtr <IUltraSound> Ptr;
				
				virtual ~IUltraSound(){}
				
				static std::string name(){
					static std::string n = "HAL.API.UltraSound.UltraSound";
					return n;
				}
				static const ::TBS::Services::Introspection::Class & introspection();
				
 //methods 
				
		/** 
		  * [method] Reconnect: 
		  */ 
		        virtual void Reconnect() = 0;

		/** 
		  * [method] GetStatus: 
		  * [out] TouchSensors frontSensors: 
		  * [out] TouchSensors backSensors: 
		  * [out] bool isValid: 
		  */ 
		        virtual void GetStatus(TouchSensors & frontSensors, TouchSensors & backSensors, bool & isValid) = 0;

				
 //signals 
				
				
			};
 } 
 } 
 } 



#endif //_ULTRASOUND_H_

