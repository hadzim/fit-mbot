/*
 * BioRadar.cpp
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#include "BioRadar.h"
#include <iostream>
#include <Poco/Delegate.h>

namespace MBot {



	BioRadar::BioRadar(TBS::NotificationWorker::Ptr nw, TBS::Robo::RoboCan::IChannel::Ptr canChannel) :
			baseNode("BioRadarBase", 2, nw, canChannel), baseMotorModule("BioRadar.Base.Motor", &baseNode, 1), baseMagneticModule("BioRadar.Base.Magnetic",
					&baseNode, 2),

			antennaNode("BioRadarAntenna", 3, nw, canChannel),

			antennaMotorModule("BioRadar.Antenna.Motor", &antennaNode, 1),

			antennaMagneticModule("BioRadar.Antenna.Magnetic", &antennaNode, 2),

			antennaTouchModule("BioRadar.Antenna.Touch", &antennaNode, 3),

			speed(20), maxRelDurationTimeInMs(250), t("BioRadarWorker"), finished(false), enabled(false) {
		LDEBUG("HAL")<< "BioRadar constructed" << LE;
			t.start(*this);
		}

	BioRadar::~BioRadar() {
		finished = true;
		t.join();
	}

	void BioRadar::Enable() {
		enabled = true;
		antennaExecution.addTask(antennaMotorModule.taskEnable(true));
	}
	void BioRadar::Disable() {
		enabled = false;
		antennaExecution.addTask(antennaMotorModule.taskEnable(false));
	}

	void BioRadar::GoMinAntenna() {
		LDEBUG("HAL")<< "BioRadar antena go min" << LE;
			antennaExecution.addTask(antennaMotorModule.taskGoMin(speed));
		}
	void BioRadar::GoMaxAntenna() {
		LDEBUG("HAL")<< "BioRadar antena go max" << LE;
			antennaExecution.addTask(antennaMotorModule.taskGoMax(speed));
		}
	void BioRadar::GoRelAntenna(const double & speed) {
		if (speed == 0) {
			LDEBUG("HAL")<< "BioRadar antena stop" << LE;
				antennaExecution.addTask(antennaMotorModule.taskStop());
			} else {
				LDEBUG("HAL")<< "BioRadar antena goRel: " << speed << " by " << maxRelDurationTimeInMs << LE;
				antennaExecution.addTask(antennaMotorModule.taskGoRel(speed, maxRelDurationTimeInMs));
			}
		}

	void BioRadar::GoMinBase() {
		LDEBUG("HAL")<< "BioRadar base go min" << LE;
			baseExecution.addTask(baseMotorModule.taskGoMin(speed));
		}
	void BioRadar::GoMaxBase() {
		LDEBUG("HAL")<< "BioRadar base go max" << LE;
			baseExecution.addTask(baseMotorModule.taskGoMax(speed));
		}
	void BioRadar::GoRelBase(const double & speed) {
		if (speed == 0) {
			LDEBUG("HAL")<< "BioRadar antena stop" << LE;
				baseExecution.addTask(baseMotorModule.taskStop());
			} else {
				LDEBUG("HAL")<< "BioRadar antena goRel: " << speed << " by " << maxRelDurationTimeInMs << LE;
				baseExecution.addTask(baseMotorModule.taskGoRel(speed, maxRelDurationTimeInMs));
			}
		}

	HAL::API::BioRadar::MotorInfo BioRadar::GetMotorStatus(const bool & isBase){
		Poco::Mutex::ScopedLock l(m);
		return isBase ? this->currentStatus.base : this->currentStatus.antenna;
	}

	std::vector< HAL::API::BioRadar::TouchInfo > BioRadar::GetAntenaStatus(){
		Poco::Mutex::ScopedLock l(m);
		std::vector< HAL::API::BioRadar::TouchInfo > status;
		status.push_back(this->currentStatus.antenna1);
		status.push_back(this->currentStatus.antenna2);
		status.push_back(this->currentStatus.antenna3);
		status.push_back(this->currentStatus.antenna4);
		return status;
	}

	void BioRadar::onBasePositionChanged(BioRadarPositionTask::Position & pos) {
		Poco::Mutex::ScopedLock l(m);
		this->currentStatus.base.position = pos.position;
		this->currentStatus.base.positionError = pos.isError;
	}

	void BioRadar::onAntennaPositionChanged(BioRadarPositionTask::Position & pos) {
		Poco::Mutex::ScopedLock l(m);

		std::cout << "antenna position changed to: " << pos.position << std::endl;

		this->currentStatus.antenna.position = pos.position;
		this->currentStatus.antenna.positionError = pos.isError;
	}

	void BioRadar::onAntennaTouchChanged(BioRadarTouchTask::Positions & pos){
		Poco::Mutex::ScopedLock l(m);
		//std::cout << "antenna touch changed: "  << std::endl;
		std::cout << "p1: " << pos.p1.distance << " itouch? " << (pos.p1.touch ? 1 : 0) << std::endl;
		//std::cout << "p2: " << pos.p2.distance << " itouch? " << (pos.p2.touch ? 1 : 0) << std::endl;
		//std::cout << "p3: " << pos.p3.distance << " itouch? " << (pos.p3.touch ? 1 : 0) << std::endl;
		//std::cout << "p4: " << pos.p4.distance << " itouch? " << (pos.p4.touch ? 1 : 0) << std::endl;
	}

	void BioRadar::run() {

		BioRadarPositionTask::Ptr tBase = baseMagneticModule.taskConsumePosition();
		tBase->PositionChanged += Poco::delegate(this, &BioRadar::onBasePositionChanged);
		BioRadarPositionTask::Ptr tAntenna = antennaMagneticModule.taskConsumePosition();
		tAntenna->PositionChanged += Poco::delegate(this, &BioRadar::onAntennaPositionChanged);
		BioRadarTouchTask::Ptr tAntennaTouch = antennaTouchModule.taskConsumeTouchData();
		tAntennaTouch->PositionChanged += Poco::delegate(this, &BioRadar::onAntennaTouchChanged);

		std::cout << "start" << std::endl;
		tBase->start();
		tAntenna->start();
		tAntennaTouch->start();

		while (!finished) {
			if (enabled) {
				//TODO
				std::cout << "running" << std::endl;
			}

			Poco::Thread::sleep(250);
		}

		std::cout << "done" << std::endl;

		tBase->PositionChanged -= Poco::delegate(this, &BioRadar::onBasePositionChanged);
		tAntenna->PositionChanged -= Poco::delegate(this, &BioRadar::onAntennaPositionChanged);
		tAntennaTouch->PositionChanged -= Poco::delegate(this, &BioRadar::onAntennaTouchChanged);

		tAntennaTouch->cancel();
		tAntenna->cancel();
		tBase->cancel();
	}

} /* namespace MBot */
