/*
 * Manipulator.cpp
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#include "Manipulator.h"
#include <iostream>
#include <Poco/Delegate.h>

namespace MBot {

	Manipulator::Manipulator(TBS::NotificationWorker::Ptr nw, TBS::Robo::RoboCan::IChannel::Ptr canChannel, int portMan1, int portMan2) :
		node("Manipulator", 4, nw, canChannel),

		rotationModule("Manipulator.Rotation", &node, 2),

		holderModule("Manipulator.Holder", &node, 1),

		magneticModule("Manipulatior.Magnetic", &node, 4),
#if ALLWORKING
		joint1(portMan1),
		joint2(portMan2),
#endif
		speed(20), maxRelDurationTimeInMs(50), t("ManipulatorWorker"), finished(false), enabled(false) {

		LDEBUG("HAL")<< "Manipulator constructed" << LE;
		t.start(*this);
	}

	Manipulator::~Manipulator() {
		finished = true;
		t.join();
	}

	void Manipulator::Enable() {
		enabled = true;
		rotationExecution.addTask(rotationModule.taskEnable(true));
		holderExecution.addTask(holderModule.taskEnable(true));
#if ALLWORKING
		joint1.enable();
		joint2.enable();

		Poco::Thread::sleep(800);

		joint1.unbreakMotor();
		joint2.unbreakMotor();

		Poco::Thread::sleep(100);
#endif
	}
	void Manipulator::Disable() {
		enabled = false;
		rotationExecution.addTask(rotationModule.taskEnable(false));
		holderExecution.addTask(holderModule.taskEnable(false));

#if ALLWORKING
		joint1.stop();
		joint2.stop();

		Poco::Thread::sleep(100);

		joint1.breakMotor();
		joint2.breakMotor();

		Poco::Thread::sleep(100);

		joint1.disable();
		joint2.disable();
#endif
	}


	void Manipulator::StartRotation(const double & speed) {
		if (speed == 0) {
			LDEBUG("HAL")<< "Manipulator motor stop" << LE;
			rotationExecution.addTask(rotationModule.taskStop());
		} else {
			LDEBUG("HAL")<< "Manipulator motor goRel: " << speed << " by " << maxRelDurationTimeInMs << LE;
			rotationExecution.addTask(rotationModule.taskGoRel(speed, maxRelDurationTimeInMs));
		}
	}
	void Manipulator::StopRotation() {
		rotationExecution.addTask(rotationModule.taskStop());
	}

	void Manipulator::StartJoint1(const double & speed) {
#if ALLWORKING
		joint1.go(speed);
#endif
	}

	void Manipulator::StopJoint1() {
#if ALLWORKING
		joint1.stop();
#endif
	}

	void Manipulator::StartJoint2(const double & speed) {
#if ALLWORKING
		joint2.go(speed);
#endif
	}

	void Manipulator::StopJoint2() {
#if ALLWORKING
		joint2.stop();
#endif
	}

	void Manipulator::StartHolder(const double & speed) {
		if (speed == 0) {
			LDEBUG("HAL")<< "Manipulator motor stop" << LE;
			holderExecution.addTask(holderModule.taskStop());
		} else {
			LDEBUG("HAL")<< "Manipulator motor goRel: " << speed << " by " << maxRelDurationTimeInMs << LE;
			holderExecution.addTask(holderModule.taskGoRel(speed, maxRelDurationTimeInMs));
		}
	}
	void Manipulator::StopHolder() {
		holderExecution.addTask(holderModule.taskStop());
	}

	void Manipulator::SetHolderThreshold(const double & threshold) {
		holderExecution.addTask(holderModule.taskSetThreshold(threshold));
	}

	void Manipulator::onPositionChanged(ManipulatorPositionTask::Position & pos) {
			Poco::Mutex::ScopedLock l(m);
			std::cout << "pos changed: " << pos.current << " pos: " << pos.position << std::endl;
			//this->currentStatus.base.position = pos.position;
			//this->currentStatus.base.positionError = pos.isError;
	}

	void Manipulator::GetStatus(HAL::API::Manipulator::MotorInfo & rotation, HAL::API::Manipulator::MotorInfo & joint1, HAL::API::Manipulator::MotorInfo & joint2, HAL::API::Manipulator::MotorInfo & holder){
		Poco::Mutex::ScopedLock l(m);
		rotation.current = 12;
		rotation.position = 458;

		joint1.current = 13;
		joint1.position = 460;

		joint2.current = 14;
		joint2.position = 462;

		holder.current = 15;
		holder.position = 0;
	}

	void Manipulator::run() {

		std::cout << "manipulator BG" << std::endl;

		ManipulatorPositionTask::Ptr tBase = magneticModule.taskConsumePosition();
		tBase->PositionChanged += Poco::delegate(this, &Manipulator::onPositionChanged);

		std::cout << "start manipulator bg" << std::endl;
		tBase->start();

		while (!finished) {
			if (enabled) {


			}

			Poco::Thread::sleep(250);
		}

		std::cout << "done manipulator bg" << std::endl;

		tBase->PositionChanged -= Poco::delegate(this, &Manipulator::onPositionChanged);

		tBase->cancel();
	}

} /* namespace MBot */
