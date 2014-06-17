/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
#ifndef _BIORADAR_H_
#define _BIORADAR_H_

#include <Poco/SharedPtr.h>
#include <Poco/BasicEvent.h>
#include "TBS/Services/Types.h"
#include <string>
#include <vector>
#include <map>

namespace TBS{ namespace Services{ namespace Introspection{ class Class; struct Struct; } } } 


namespace HAL { 
	namespace API { 
		namespace BioRadar { 
       struct MotorInfo {
				
				static std::string name(){
					static std::string n = "MotorInfo";
					return n;
				}
				static const ::TBS::Services::Introspection::Struct & introspection();
				
 //members 
						bool touchMin;
		bool touchMax;
		double position;
		bool positionError;

				
			};
 } 
 } 
 } 


namespace HAL { 
	namespace API { 
		namespace BioRadar { 
       struct TouchInfo {
				
				static std::string name(){
					static std::string n = "TouchInfo";
					return n;
				}
				static const ::TBS::Services::Introspection::Struct & introspection();
				
 //members 
						bool isTouch;
		double distance;

				
			};
 } 
 } 
 } 




namespace HAL { 
	namespace API { 
		namespace BioRadar { 
	   /** [interface] IBioRadar:  */
       class GEN_SERVICE_API IBioRadar {
			public:
				typedef Poco::SharedPtr <IBioRadar> Ptr;
				
				virtual ~IBioRadar(){}
				
				static std::string name(){
					static std::string n = "HAL.API.BioRadar.BioRadar";
					return n;
				}
				static const ::TBS::Services::Introspection::Class & introspection();
				
 //methods 
				
		/** 
		  * [method] Enable: 
		  */ 
		        virtual void Enable() = 0;

		/** 
		  * [method] Disable: 
		  */ 
		        virtual void Disable() = 0;

		/** 
		  * [method] GoMinBase: 
		  */ 
		        virtual void GoMinBase() = 0;

		/** 
		  * [method] GoMaxBase: 
		  */ 
		        virtual void GoMaxBase() = 0;

		/** 
		  * [method] GoRelBase: 
		  * [in] double speed: 
		  */ 
		        virtual void GoRelBase(const double & speed) = 0;

		/** 
		  * [method] GoMinAntenna: 
		  */ 
		        virtual void GoMinAntenna() = 0;

		/** 
		  * [method] GoMaxAntenna: 
		  */ 
		        virtual void GoMaxAntenna() = 0;

		/** 
		  * [method] GoRelAntenna: 
		  * [in] double speed: 
		  */ 
		        virtual void GoRelAntenna(const double & speed) = 0;

		/** 
		  * [method] GetMotorStatus: 
		  * [in] bool isBase: 
		  * [out] MotorInfo info: 
		  */ 
		        virtual MotorInfo GetMotorStatus(const bool & isBase) = 0;

		/** 
		  * [method] GetAntenaStatus: 
		  * [out] std::vector< TouchInfo > antenaSensors: array of structs(isTouch,distance)
		  */ 
		        virtual std::vector< TouchInfo > GetAntenaStatus() = 0;

				
 //signals 
				
				
			};
 } 
 } 
 } 



#endif //_BIORADAR_H_
