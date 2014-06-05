/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
#include "TBS/Services/Introspection.h"
#include "HAL/API/BioRadar.h"



namespace HAL { 
	namespace API { 
		namespace BioRadar { 
		::TBS::Services::Introspection::Class __introspectionIBioRadar(){
			::TBS::Services::Introspection::Namespace cnmspc;
cnmspc.push_back("HAL");
cnmspc.push_back("API");
cnmspc.push_back("BioRadar");
::TBS::Services::Introspection::Class c("HAL.API.BioRadar.BioRadar", "BioRadar", cnmspc,"");
{
	::TBS::Services::Introspection::Method m("Enable", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("Disable", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("GoMinBase", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("GoMaxBase", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("GoRelBase", "");
  m.inArguments.push_back(::TBS::Services::Introspection::Argument("speed", "d", ""));
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("GoMinAntenna", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("GoMaxAntenna", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("GoRelAntenna", "");
  m.inArguments.push_back(::TBS::Services::Introspection::Argument("speed", "d", ""));
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("GetMotorStatus", "");
  m.inArguments.push_back(::TBS::Services::Introspection::Argument("isBase", "b", ""));
  m.outArguments.push_back(::TBS::Services::Introspection::Argument("touchMin", "b", ""));
  m.outArguments.push_back(::TBS::Services::Introspection::Argument("touchMax", "b", ""));
  m.outArguments.push_back(::TBS::Services::Introspection::Argument("position", "d", ""));
  m.outArguments.push_back(::TBS::Services::Introspection::Argument("positionError", "b", ""));
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("GetAntenaStatus", "");
  m.outArguments.push_back(::TBS::Services::Introspection::Argument("antenaSensors", "a(bi)", "array of structs(isTouch,distance)"));
	c.methods.push_back(m);
}
return c;

		}
	   const ::TBS::Services::Introspection::Class & IBioRadar::introspection(){
			static ::TBS::Services::Introspection::Class c(__introspectionIBioRadar());
			return c;
	   }
 } 
 } 
 } 




