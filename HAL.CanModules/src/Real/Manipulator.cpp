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

	Manipulator::Manipulator(TBS::NotificationWorker::Ptr nw, TBS::Robo::RoboCan::IChannel::Ptr canChannel) :
		node("Manipulator", 4, nw, canChannel),

		rotationModule("Manipulator.Rotation", &node, 2),

		holderModule("Manipulator.Holder", &node, 1),

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

	}
	void Manipulator::Disable() {
		enabled = false;
		rotationExecution.addTask(rotationModule.taskEnable(false));
		holderExecution.addTask(holderModule.taskEnable(false));
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

	}

	void Manipulator::StopJoint1() {

	}

	void Manipulator::StartJoint2(const double & speed) {

	}

	void Manipulator::StopJoint2() {

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

	void Manipulator::run() {

		while (!finished) {
			if (enabled) {
				//TODO
				//std::cout << "running" << std::endl;
			}

			Poco::Thread::sleep(250);
		}
	}

} /* namespace MBot */
