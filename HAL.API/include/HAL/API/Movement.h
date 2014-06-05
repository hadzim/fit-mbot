/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#include <Poco/SharedPtr.h>
#include <Poco/BasicEvent.h>
#include "TBS/Services/Types.h"
#include <string>
#include <vector>
#include <map>

namespace TBS{ namespace Services{ namespace Introspection{ class Class; struct Struct; } } } 




namespace HAL { 
	namespace API { 
		namespace Movement { 
	   /** [interface] IMovement:  */
       class GEN_SERVICE_API IMovement {
			public:
				typedef Poco::SharedPtr <IMovement> Ptr;
				
				virtual ~IMovement(){}
				
				static std::string name(){
					static std::string n = "HAL.API.Movement.Movement";
					return n;
				}
				static const ::TBS::Services::Introspection::Class & introspection();
				
 //methods 
				
		/** 
		  * [method] Move: 
		  * [in] double speedLeft: 
		  * [in] double speedRight: 
		  */ 
		        virtual void Move(const double & speedLeft, const double & speedRight) = 0;

		/** 
		  * [method] Stop: 
		  */ 
		        virtual void Stop() = 0;

		/** 
		  * [method] SetPosition: 
		  * [in] int64_t posLeft: 
		  * [in] int64_t posRight: 
		  */ 
		        virtual void SetPosition(const int64_t & posLeft, const int64_t & posRight) = 0;

		/** 
		  * [method] GetStatus: 
		  * [out] double speedLeft: 
		  * [out] double speedRight: 
		  * [out] int64_t posLeft: 
		  * [out] int64_t posRight: 
		  */ 
		        virtual void GetStatus(double & speedLeft, double & speedRight, int64_t & posLeft, int64_t & posRight) = 0;

				
 //signals 
						struct StatusChangedArg { 
double speedLeft;
double speedRight;
int64_t posLeft;
int64_t posRight;
};
		Poco::BasicEvent <StatusChangedArg> StatusChanged;
		

				
			};
 } 
 } 
 } 



#endif //_MOVEMENT_H_

