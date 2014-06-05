/*
 * BioRadarModules.h
 *
 *  Created on: 15.5.2014
 *      Author: JV
 */

#include "TBS/MBot/HW/BioRadarModules.h"

namespace MBot {

	BioRadarMotorModule::BioRadarMotorModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule) :
			TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule) {
	}
	BioRadarMotorModule::~BioRadarMotorModule() {
	}

	TBS::Robo::RoboCan::ModuleCommandTask::Ptr BioRadarMotorModule::taskGoMin(Poco::Int16 speed) const {
		TBS::Robo::RoboCan::RoboCanMessageData data;
		data.setSHORT(speed);
		return new TBS::Robo::RoboCan::ModuleCommandTask("GoMin", this->getInternalModule(), this->getInternalModule().composeCommand((int) GoMin, data));
	}
	TBS::Robo::RoboCan::ModuleCommandTask::Ptr BioRadarMotorModule::taskGoMax(Poco::Int16 speed) const {
		TBS::Robo::RoboCan::RoboCanMessageData data;
		data.setSHORT(speed);
		return new TBS::Robo::RoboCan::ModuleCommandTask("GoMax", this->getInternalModule(), this->getInternalModule().composeCommand((int) GoMax, data));
	}

	TBS::Robo::RoboCan::ModuleCommandTask::Ptr BioRadarMotorModule::taskGoRel(Poco::Int16 speed, Poco::Int16 timeInMs) const {
		TBS::Robo::RoboCan::RoboCanMessageData data;
		TBS::Robo::RoboCan::RoboCanMessageData::Short2 val;
		val.short1 = speed;
		val.short2 = timeInMs;
		data.setSHORT2(val);
		return new TBS::Robo::RoboCan::ModuleCommandTask("GoRel", this->getInternalModule(), this->getInternalModule().composeCommand((int) GoRel, data));
	}

	TBS::Robo::RoboCan::ModuleCommandTask::Ptr BioRadarMotorModule::taskEnable(bool enable) const {
		TBS::Robo::RoboCan::RoboCanMessageData data;
		data.setUSHORT(enable ? 1 : 0);
		return new TBS::Robo::RoboCan::ModuleCommandAnyAckTask(enable ? "Enable" : "Disable", this->getInternalModule(), this->getInternalModule().composeCommand((int)Enable, data));
	}

	BioRadarPositionTask::BioRadarPositionTask(std::string name, const TBS::Robo::RoboCan::InternalCanModule & module) :
			TBS::Robo::RoboCan::ConsumingDataModuleTask(name, module) {
		this->DataMessageReady += Poco::delegate(this, &BioRadarPositionTask::onDataReady);
	}
	BioRadarPositionTask::~BioRadarPositionTask() {
		this->DataMessageReady -= Poco::delegate(this, &BioRadarPositionTask::onDataReady);
	}

	void BioRadarPositionTask::onDataReady(TBS::Robo::RoboCan::DataMessage & msg) {
		Position p;
		TBS::Robo::RoboCan::RoboCanMessageData::UShort2 val = msg.getData(0).getUSHORT2();
		p.position = val.short1;
		p.isError = val.short2 != 1;
		PositionChanged(this, p);
	}

	BioRadarMagneticModule::BioRadarMagneticModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule) :
			TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule), n(name) {
	}
	BioRadarMagneticModule::~BioRadarMagneticModule() {
	}

	BioRadarPositionTask::Ptr BioRadarMagneticModule::taskConsumePosition() const {
		return new BioRadarPositionTask(n, this->getInternalModule());
	}

}

