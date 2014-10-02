/**
 * THIS FILE IS GENERATED BY genTool, DO NOT CHANGE IT!!!!!
 */
#include "TBS/Services/Introspection.h"
#include "HAL/API/Manipulator.h"



namespace HAL { 
	namespace API { 
		namespace Manipulator { 
		::TBS::Services::Introspection::Class __introspectionIManipulator(){
			::TBS::Services::Introspection::Namespace cnmspc;
cnmspc.push_back("HAL");
cnmspc.push_back("API");
cnmspc.push_back("Manipulator");
::TBS::Services::Introspection::Class c("HAL.API.Manipulator.Manipulator", "Manipulator", cnmspc,"");
{
	::TBS::Services::Introspection::Method m("Enable", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("Disable", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("StartRotation", "");
  m.inArguments.push_back(::TBS::Services::Introspection::Argument("speed", "d", ""));
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("StartRotationTo", "");
  m.inArguments.push_back(::TBS::Services::Introspection::Argument("speed", "d", ""));
  m.inArguments.push_back(::TBS::Services::Introspection::Argument("destination", "d", ""));
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("StopRotation", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("StartJoint1", "");
  m.inArguments.push_back(::TBS::Services::Introspection::Argument("speed", "d", ""));
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("StartJoint1To", "");
  m.inArguments.push_back(::TBS::Services::Introspection::Argument("speed", "d", ""));
  m.inArguments.push_back(::TBS::Services::Introspection::Argument("destination", "d", ""));
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("StopJoint1", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("StartJoint2", "");
  m.inArguments.push_back(::TBS::Services::Introspection::Argument("speed", "d", ""));
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("StartJoint2To", "");
  m.inArguments.push_back(::TBS::Services::Introspection::Argument("speed", "d", ""));
  m.inArguments.push_back(::TBS::Services::Introspection::Argument("destination", "d", ""));
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("StopJoint2", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("StartHolder", "");
  m.inArguments.push_back(::TBS::Services::Introspection::Argument("speed", "d", ""));
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("StopHolder", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("SetHolderThreshold", "");
  m.inArguments.push_back(::TBS::Services::Introspection::Argument("threshold", "d", ""));
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("LightOn", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("LightOff", "");
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Method m("GetStatus", "");
  m.outArguments.push_back(::TBS::Services::Introspection::Argument("rotationEncoder", "d", ""));
  m.outArguments.push_back(::TBS::Services::Introspection::Argument("joint1Encoder", "d", ""));
  m.outArguments.push_back(::TBS::Services::Introspection::Argument("joint2Encoder", "d", ""));
  m.outArguments.push_back(::TBS::Services::Introspection::Argument("holderCurrent", "d", ""));
	c.methods.push_back(m);
}
{
	::TBS::Services::Introspection::Signal s("StatusChanged", "");
  s.arguments.push_back(::TBS::Services::Introspection::Argument("rotationEncoder", "d", ""));
  s.arguments.push_back(::TBS::Services::Introspection::Argument("joint1Encoder", "d", ""));
  s.arguments.push_back(::TBS::Services::Introspection::Argument("joint2Encoder", "d", ""));
  s.arguments.push_back(::TBS::Services::Introspection::Argument("holderCurrent", "d", ""));
	c.signals.push_back(s);
}
return c;

		}
	   const ::TBS::Services::Introspection::Class & IManipulator::introspection(){
			static ::TBS::Services::Introspection::Class c(__introspectionIManipulator());
			return c;
	   }
 } 
 } 
 } 




