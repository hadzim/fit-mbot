/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
#include "TBS/Services/Introspection.h"
#include "HAL/API/Camera.h"



namespace HAL { 
	namespace API { 
		namespace Camera { 
		::TBS::Services::Introspection::Class __introspectionICamera(){
			::TBS::Services::Introspection::Namespace cnmspc;
cnmspc.push_back("HAL");
cnmspc.push_back("API");
cnmspc.push_back("Camera");
::TBS::Services::Introspection::Class c("HAL.API.Camera.Camera", "Camera", cnmspc,"");
{
	::TBS::Services::Introspection::Method m("Enable", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("Disable", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("GoMinEngine", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("GoMaxEngine", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("GoRelEngine", "");
  m.inArguments.push_back(::TBS::Services::Introspection::Argument("speed", "d", ""));
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("GoMinServo1", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("GoMaxServo1", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("GoRelServo1", "");
  m.inArguments.push_back(::TBS::Services::Introspection::Argument("speed", "d", ""));
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("GoMinServo2", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("GoMaxServo2", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("GoRelServo2", "");
  m.inArguments.push_back(::TBS::Services::Introspection::Argument("speed", "d", ""));
	c.methods.push_back(m);
}
return c;

		}
	   const ::TBS::Services::Introspection::Class & ICamera::introspection(){
			static ::TBS::Services::Introspection::Class c(__introspectionICamera());
			return c;
	   }
 } 
 } 
 } 




