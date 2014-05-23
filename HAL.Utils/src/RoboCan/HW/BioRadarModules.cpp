/*
 * BioRadarModules.h
 *
 *  Created on: 15.5.2014
 *      Author: JV
 */

#include "TBS/Robo/RoboCan/HW/BioRadarModules.h"

namespace MBot {

	BioRadarMotorModule::BioRadarMotorModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule) :
			TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule) {
	}
	BioRadarMotorModule::~BioRadarMotorModule() {
	}

	TBS::Robo::RoboCan::ModuleCommandTask::Ptr BioRadarMotorModule::taskGoMin(Poco::Int16 speed) const {
		TBS::Robo::RoboCan::RoboCanMessageData data;
		data.setSHORT(speed);
		return new TBS::Robo::RoboCan::ModuleCommandTask(this->getInternalModule(), this->getInternalModule().composeCommand((int) GoMin, data));
	}
	TBS::Robo::RoboCan::ModuleCommandTask::Ptr BioRadarMotorModule::taskGoMax(Poco::Int16 speed) const {
		TBS::Robo::RoboCan::RoboCanMessageData data;
		data.setSHORT(speed);
		return new TBS::Robo::RoboCan::ModuleCommandTask(this->getInternalModule(), this->getInternalModule().composeCommand((int) GoMax, data));
	}


	TBS::Robo::RoboCan::ModuleCommandTask::Ptr BioRadarMotorModule::taskGoRel(Poco::Int16 speed, Poco::Int16 timeInMs) const {
					TBS::Robo::RoboCan::RoboCanMessageData data;
					TBS::Robo::RoboCan::RoboCanMessageData::Short2 val;
					val.short1 = speed;
					val.short2 = timeInMs;
					data.setSHORT2(val);
					return new TBS::Robo::RoboCan::ModuleCommandTask(this->getInternalModule(), this->getInternalModule().composeCommand((int) GoRel, data));
				}


	BioRadarMagneticModule::BioRadarMagneticModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule) :
			TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule) {
	}
	BioRadarMagneticModule::~BioRadarMagneticModule() {
	}

	TBS::Robo::RoboCan::ConsumingDataModuleTask::Ptr BioRadarMagneticModule::taskConsumeData() const {
		return new TBS::Robo::RoboCan::ConsumingDataModuleTask(this->getInternalModule());
	}

}

