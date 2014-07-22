/*
 * ManipulatorModules.h
 *
 *  Created on: Jul 22, 2014
 *      Author: dron
 */

#ifndef MANIPULATORMODULES_H_
#define MANIPULATORMODULES_H_
#include "TBS/Robo/RoboCan/HW/CanModule.h"

namespace MBot {

class ManipulatorRotationModule: public TBS::Robo::RoboCan::CanModule {

	enum TwoStateCommands {
		GoRel = 30, Enable = 32
	};

public:
	ManipulatorRotationModule(const std::string & name,
			TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule) :
			TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule) {
	}
	virtual ~ManipulatorRotationModule() {
	}

	TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskGoRel(Poco::Int16 speed,
			Poco::Int16 timeInMs) const {
		TBS::Robo::RoboCan::RoboCanMessageData data;
		TBS::Robo::RoboCan::RoboCanMessageData::Short2 val;
		val.short1 = speed;
		val.short2 = timeInMs;
		data.setSHORT2(val);
		return new TBS::Robo::RoboCan::ModuleCommandTask("gorel",
				this->getInternalModule(),
				this->getInternalModule().composeCommand((int) GoRel, data));
	}

	TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskEnable(bool enable) const {
		TBS::Robo::RoboCan::RoboCanMessageData data;
		data.setUSHORT(enable ? 1 : 0);
		return new TBS::Robo::RoboCan::ModuleCommandAnyAckTask("enable",
				this->getInternalModule(),
				this->getInternalModule().composeCommand((int) Enable, data));
	}

};

class ManipulatorHolderModule: public TBS::Robo::RoboCan::CanModule {

	enum TwoStateCommands {
		GoRel = 30, SetThreshold = 31, Enable = 32
	};

public:
	ManipulatorHolderModule(const std::string & name,
			TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule) :
			TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule) {
	}
	virtual ~ManipulatorHolderModule() {
	}

	TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskGoRel(Poco::Int16 speed,
			Poco::Int16 timeInMs) const {
		TBS::Robo::RoboCan::RoboCanMessageData data;
		TBS::Robo::RoboCan::RoboCanMessageData::Short2 val;
		val.short1 = speed;
		val.short2 = timeInMs;
		data.setSHORT2(val);
		return new TBS::Robo::RoboCan::ModuleCommandTask("gorel",
				this->getInternalModule(),
				this->getInternalModule().composeCommand((int) GoRel, data));
	}

	TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskSetThreshold(
			Poco::UInt16 thresh) const {
		TBS::Robo::RoboCan::RoboCanMessageData data;
		data.setUSHORT(thresh);
		return new TBS::Robo::RoboCan::ModuleCommandTask("setthresh",
				this->getInternalModule(),
				this->getInternalModule().composeCommand((int) SetThreshold,
						data));
	}

	TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskEnable(bool enable) const {
		TBS::Robo::RoboCan::RoboCanMessageData data;
		data.setUSHORT(enable ? 1 : 0);
		return new TBS::Robo::RoboCan::ModuleCommandAnyAckTask("enable",
				this->getInternalModule(),
				this->getInternalModule().composeCommand((int) Enable, data));
	}

};

} /* namespace MBot */

#endif /* MANIPULATORMODULES_H_ */
