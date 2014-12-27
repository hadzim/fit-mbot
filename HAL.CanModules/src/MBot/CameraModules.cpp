//------------------------------------------------------------------------------
//
//  Project:   VG20102014024
//             Robot for search of human beings in crushes and avalanches
//
//             Brno University of Technology
//             Faculty of Information Technology
//
//------------------------------------------------------------------------------
//
//             This project was financially supported by project
//                  VG20102014024 funds provided by MV CR.
//
//------------------------------------------------------------------------------
/*!

@file
@brief     Implementation of methods
@details   Details
@authors   Jan Vana (<ivanajan@fit.vutbr.cz>)
@date      2010-2014
@note      This project was supported by project funds of the MV CR grant VG20102014024.

*/
#include "MBot/HW/CameraModules.h"

namespace MBot {

CameraMotorModule::CameraMotorModule(const std::string & name,
		TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule) :
		TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule) {
}
CameraMotorModule::~CameraMotorModule() {
}

TBS::Robo::RoboCan::ModuleCommandTask::Ptr CameraMotorModule::taskGoMin() const {
	TBS::Robo::RoboCan::RoboCanMessageData data;
	return new TBS::Robo::RoboCan::ModuleCommandTask("GoMin",
			this->getInternalModule(),
			this->getInternalModule().composeCommand((int) GoMin, data));
}
TBS::Robo::RoboCan::ModuleCommandTask::Ptr CameraMotorModule::taskGoMax() const {
	TBS::Robo::RoboCan::RoboCanMessageData data;
	return new TBS::Robo::RoboCan::ModuleCommandTask("GoMax",
			this->getInternalModule(),
			this->getInternalModule().composeCommand((int) GoMax, data));
}

TBS::Robo::RoboCan::ModuleCommandTask::Ptr CameraMotorModule::taskGoRel(
		Poco::Int16 speed, Poco::Int16 timeInMs) const {
	TBS::Robo::RoboCan::RoboCanMessageData data;
	TBS::Robo::RoboCan::RoboCanMessageData::Short2 val;
	val.short1 = speed;
	val.short2 = timeInMs;
	data.setSHORT2(val);
	return new TBS::Robo::RoboCan::ModuleCommandTask("GoRel",
			this->getInternalModule(),
			this->getInternalModule().composeCommand((int) GoRel, data));
}
TBS::Robo::RoboCan::ModuleCommandTask::Ptr CameraMotorModule::taskEnable(
		bool enable) const {
	TBS::Robo::RoboCan::RoboCanMessageData data;
	data.setUSHORT(enable ? 1 : 0);
	return new TBS::Robo::RoboCan::ModuleCommandTask(
			enable ? "Enable" : "Disable", this->getInternalModule(),
			this->getInternalModule().composeCommand((int) Enable, data));
}

LightModule::LightModule(const std::string & name,
		TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule):
				TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule) {
}
LightModule::~LightModule() {
}

TBS::Robo::RoboCan::ModuleCommandTask::Ptr LightModule::taskEnable(
		bool enable) const {
	TBS::Robo::RoboCan::RoboCanMessageData data;
		data.setUSHORT(enable ? 1 : 0);
		return new TBS::Robo::RoboCan::ModuleCommandTask(
				enable ? "Enable" : "Disable", this->getInternalModule(),
				this->getInternalModule().composeCommand((int) Enable, data));
}

}

