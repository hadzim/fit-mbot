/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
#ifndef _MANIPULATOR_H_
#define _MANIPULATOR_H_

#include <Poco/SharedPtr.h>
#include <Poco/BasicEvent.h>
#include "TBS/Services/Types.h"
#include <string>
#include <vector>
#include <map>

namespace TBS{ namespace Services{ namespace Introspection{ class Class; struct Struct; } } } 


namespace HAL { 
	namespace API { 
		namespace Manipulator { 
       struct MotorInfo {
				
				static std::string name(){
					static std::string n = "MotorInfo";
					return n;
				}
				static const ::TBS::Services::Introspection::Struct & introspection();
				
 //members 
						double position;
		double current;

				
			};
 } 
 } 
 } 




namespace HAL { 
	namespace API { 
		namespace Manipulator { 
	   /** [interface] IManipulator:  */
       class GEN_SERVICE_API IManipulator {
			public:
				typedef Poco::SharedPtr <IManipulator> Ptr;
				
				virtual ~IManipulator(){}
				
				static std::string name(){
					static std::string n = "HAL.API.Manipulator.Manipulator";
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
		  * [method] StartRotation: 
		  * [in] double speed: 
		  */ 
		        virtual void StartRotation(const double & speed) = 0;

		/** 
		  * [method] StopRotation: 
		  */ 
		        virtual void StopRotation() = 0;

		/** 
		  * [method] StartJoint1: 
		  * [in] double speed: 
		  */ 
		        virtual void StartJoint1(const double & speed) = 0;

		/** 
		  * [method] StopJoint1: 
		  */ 
		        virtual void StopJoint1() = 0;

		/** 
		  * [method] StartJoint2: 
		  * [in] double speed: 
		  */ 
		        virtual void StartJoint2(const double & speed) = 0;

		/** 
		  * [method] StopJoint2: 
		  */ 
		        virtual void StopJoint2() = 0;

		/** 
		  * [method] StartHolder: 
		  * [in] double speed: 
		  */ 
		        virtual void StartHolder(const double & speed) = 0;

		/** 
		  * [method] StopHolder: 
		  */ 
		        virtual void StopHolder() = 0;

		/** 
		  * [method] SetHolderThreshold: 
		  * [in] double threshold: 
		  */ 
		        virtual void SetHolderThreshold(const double & threshold) = 0;

		/** 
		  * [method] LightOn: 
		  */ 
		        virtual void LightOn() = 0;

		/** 
		  * [method] LightOff: 
		  */ 
		        virtual void LightOff() = 0;

		/** 
		  * [method] GetStatus: 
		  * [out] MotorInfo rotation: 
		  * [out] MotorInfo joint1: 
		  * [out] MotorInfo joint2: 
		  * [out] MotorInfo holder: 
		  */ 
		        virtual void GetStatus(MotorInfo & rotation, MotorInfo & joint1, MotorInfo & joint2, MotorInfo & holder) = 0;

				
 //signals 
				
				
			};
 } 
 } 
 } 



#endif //_MANIPULATOR_H_

