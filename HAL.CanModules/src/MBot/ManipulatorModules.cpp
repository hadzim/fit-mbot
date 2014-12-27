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
#include <MBot/HW/ManipulatorModules.h>

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

		TBS::Robo::RoboCan::RoboCanMessage m;
		msg.getData(0).writeToMessage(m);

		std::cout << "pos received: " << (int)val.short1 << " data: " << m.toString() << std::endl;
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
