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
		return new TBS::Robo::RoboCan::ModuleCommandAnyAckTask(enable ? "Enable" : "Disable", this->getInternalModule(),
				this->getInternalModule().composeCommand((int) Enable, data));
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

	BioRadarTouchTask::BioRadarTouchTask(std::string name, const TBS::Robo::RoboCan::InternalCanModule & module) :
			TBS::Robo::RoboCan::ConsumingDataModuleTask(name, module) {
		this->DataMessageReady += Poco::delegate(this, &BioRadarTouchTask::onDataReady);
	}
	BioRadarTouchTask::~BioRadarTouchTask() {
		this->DataMessageReady -= Poco::delegate(this, &BioRadarTouchTask::onDataReady);
	}

	void BioRadarTouchTask::onDataReady(TBS::Robo::RoboCan::DataMessage & msg) {
		try {
			Positions p;

			TBS::Robo::RoboCan::RoboCanMessageData::UChar4 val = msg.getData(0).getUCHAR4();

			p.p1.touch = val.uchar1 ? true : false;
			p.p2.touch = val.uchar2 ? true : false;
			p.p3.touch = val.uchar3 ? true : false;
			p.p4.touch = val.uchar4 ? true : false;

			p.p1.distance = msg.getData(1).getSHORT2().short1;
			p.p2.distance = msg.getData(1).getSHORT2().short2;

			p.p3.distance = msg.getData(2).getSHORT2().short1;
			p.p4.distance = msg.getData(2).getSHORT2().short2;

			PositionChanged(this, p);

		} catch (Poco::Exception & e){
			std::cout << "err: " << e.displayText() << std::endl;
		} catch (std::exception & e){
			std::cout << "err: " << e.what() << std::endl;
		} catch (...){
			std::cout << "err: ??" << std::endl;
		}
	}

	BioRadarTouchModule::BioRadarTouchModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule) :
			TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule), n(name) {
	}
	BioRadarTouchModule::~BioRadarTouchModule() {
	}

	BioRadarTouchTask::Ptr BioRadarTouchModule::taskConsumeTouchData() const {
		return new BioRadarTouchTask(n, this->getInternalModule());
	}

}

