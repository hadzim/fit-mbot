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

	BioRadar::MotorStatus::MotorStatus(){
		touchMin = false;
		touchMax =  false;
		position = 0.0;
		positionError = false;
	}
	BioRadar::AntennaSensor::AntennaSensor(){
		touch = false;
		distance = 0;
	}

	BioRadar::BioRadar(TBS::NotificationWorker::Ptr nw, TBS::Robo::RoboCan::IChannel::Ptr canChannel) :
			baseNode("BioRadarBase", 2, nw, canChannel), baseMotorModule("BioRadar.Base.Motor", &baseNode, 1), baseMagneticModule("BioRadar.Base.Magnetic",
					&baseNode, 2),

			antennaNode("BioRadarAntenna", 3, nw, canChannel), antennaMotorModule("BioRadar.Antenna.Motor", &antennaNode, 1), antennaMagneticModule(
					"BioRadar.Antenna.Magnetic", &antennaNode, 2),

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

	void BioRadar::GetMotorStatus(const bool & isBase, bool & touchMin, bool & touchMax, double & position, bool & positionError) {
		Poco::Mutex::ScopedLock l(m);

		MotorStatus s = isBase ? this->currentStatus.base : this->currentStatus.antenna;

		position = s.position;
		positionError = s.positionError;
		touchMin = s.touchMin;
		touchMax = s.touchMax;
	}

	/**
	 *
	 * [out] std::vector< TBS::Services::Tuple< bool, int32_t > > antenaSensors: array of structs(isTouch,distance)
	 */
	std::vector<TBS::Services::Tuple<bool, int32_t> > BioRadar::GetAntenaStatus() {
		std::vector<TBS::Services::Tuple<bool, int32_t> > status;
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

	void BioRadar::run() {

		BioRadarPositionTask::Ptr tBase = baseMagneticModule.taskConsumePosition();
		tBase->PositionChanged += Poco::delegate(this, &BioRadar::onBasePositionChanged);
		BioRadarPositionTask::Ptr tAntenna = antennaMagneticModule.taskConsumePosition();
		tAntenna->PositionChanged += Poco::delegate(this, &BioRadar::onAntennaPositionChanged);

		std::cout << "start" << std::endl;
		tBase->start();
		tAntenna->start();

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

		tAntenna->cancel();
		tBase->cancel();
	}

} /* namespace MBot */
