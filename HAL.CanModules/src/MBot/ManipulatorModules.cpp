/*
 * ManipulatorModules.cpp
 *
 *  Created on: Jul 22, 2014
 *      Author: dron
 */

#include <TBS/MBot/HW/ManipulatorModules.h>

namespace MBot {

	ManipulatorRotationPositionTask::ManipulatorRotationPositionTask(std::string name, const TBS::Robo::RoboCan::InternalCanModule & module) :
			TBS::Robo::RoboCan::ConsumingDataModuleTask(name, module) {
		this->DataMessageReady += Poco::delegate(this, &ManipulatorRotationPositionTask::onDataReady);
	}
	ManipulatorRotationPositionTask::~ManipulatorRotationPositionTask() {
		this->DataMessageReady -= Poco::delegate(this, &ManipulatorRotationPositionTask::onDataReady);
	}

	void ManipulatorRotationPositionTask::onDataReady(TBS::Robo::RoboCan::DataMessage & msg) {
		Position p;

		TBS::Robo::RoboCan::RoboCanMessageData::UShort2 val = msg.getData(0).getUSHORT2();
		p.encoder = val.short1;
		//p.position = val.short2;
		PositionChanged(this, p);
	}

	ManipulatorPositionTask::ManipulatorPositionTask(std::string name, const TBS::Robo::RoboCan::InternalCanModule & module) :
			TBS::Robo::RoboCan::ConsumingDataModuleTask(name, module) {
		this->DataMessageReady += Poco::delegate(this, &ManipulatorPositionTask::onDataReady);
	}
	ManipulatorPositionTask::~ManipulatorPositionTask() {
		this->DataMessageReady -= Poco::delegate(this, &ManipulatorPositionTask::onDataReady);
	}

	void ManipulatorPositionTask::onDataReady(TBS::Robo::RoboCan::DataMessage & msg) {
		Position p;

		TBS::Robo::RoboCan::RoboCanMessageData::UShort2 val = msg.getData(0).getUSHORT2();
		p.encoder1 = val.short1;
		p.encoder2 = val.short2;

		PositionChanged(this, p);
	}

	ManipulatorMagneticModule::ManipulatorMagneticModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule) :
			TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule), n(name) {
	}
	ManipulatorMagneticModule::~ManipulatorMagneticModule() {
	}

	ManipulatorPositionTask::Ptr ManipulatorMagneticModule::taskConsumePosition() const {
		return new ManipulatorPositionTask(n, this->getInternalModule());
	}

} /* namespace MBot */
