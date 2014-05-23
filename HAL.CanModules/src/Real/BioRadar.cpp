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
	}
	void BioRadar::Disable() {
		enabled = false;
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

	void BioRadar::GetStatus(bool & baseTouchMin, bool & baseTouchMax, double & basePosition, bool & basePositionError,

	bool & antennaTouchMin, bool & antennaTouchMax, double & antennaPosition, bool & antennaPositionError,

	bool & antennaTouch1, bool & antennaTouch2, bool & antennaTouch3, bool & antennaTouch4,

	int32_t & antennaDistance1, int32_t & antennaDistance2, int32_t & antennaDistance3, int32_t & antennaDistance4) {

	}

	void BioRadar::onBasePositionChanged(BioRadarPositionTask::Position & pos) {
		Poco::Mutex::ScopedLock l(m);
		this->currentStatus.basePosition = pos.position;
		this->currentStatus.basePositionError = pos.isError;
	}

	void BioRadar::onAntennaPositionChanged(BioRadarPositionTask::Position & pos) {
		Poco::Mutex::ScopedLock l(m);
		this->currentStatus.antennaPosition = pos.position;
		this->currentStatus.antennaPositionError = pos.isError;
	}

	void BioRadar::run() {

		BioRadarPositionTask::Ptr tBase = baseMagneticModule.taskConsumePosition();
		tBase->PositionChanged += Poco::delegate(this, &BioRadar::onBasePositionChanged);
		BioRadarPositionTask::Ptr tAntenna = antennaMagneticModule.taskConsumePosition();
		tAntenna->PositionChanged += Poco::delegate(this, &BioRadar::onAntennaPositionChanged);

		tBase->start();
		tAntenna->start();

		while (!finished) {
			if (enabled) {
				//TODO
			}
			Poco::Thread::sleep(250);
		}

		tBase->PositionChanged -= Poco::delegate(this, &BioRadar::onBasePositionChanged);
		tAntenna->PositionChanged -= Poco::delegate(this, &BioRadar::onAntennaPositionChanged);


		tAntenna->cancel();
		tBase->cancel();
	}

} /* namespace MBot */
