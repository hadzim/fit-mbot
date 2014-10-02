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

			lightModule("Manipulator.Light", &node, 3),

			magneticModule("Manipulatior.Magnetic", &node, 4),
#if ALLWORKING
					joint1(portMan1),
					joint2(portMan2),
#endif
					speed(20), maxRelDurationTimeInMs(50), t("ManipulatorWorker"), finished(false), enabled(false) {

		LDEBUG("HAL")<< "Manipulator constructed" << LE;

			HAL::API::Manipulator::MotorInfo mi;
			mi.current = -1;
			mi.position = -1;
			this->currentStatus.holder = this->currentStatus.joint1 = this->currentStatus.joint2 = this->currentStatus.rotation = mi;

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
		joint2.enable();
		joint1.enable();


		Poco::Thread::sleep(800);

		joint2.unbreakMotor();
		joint1.unbreakMotor();


		Poco::Thread::sleep(100);
#endif
	}
	void Manipulator::Disable() {
		enabled = false;
		rotationExecution.addTask(rotationModule.taskEnable(false));
		holderExecution.addTask(holderModule.taskEnable(false));

#if ALLWORKING

		joint2.stop();
		joint1.stop();

		Poco::Thread::sleep(100);


		joint2.breakMotor();
		joint1.breakMotor();

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

		this->currentStatus.joint1.position = pos.encoder1;
		this->currentStatus.joint1.current = 0;

		this->currentStatus.joint2.position = pos.encoder2;
		this->currentStatus.joint2.current = 0;
		dump();
	}

	void Manipulator::onRotationChanged(ManipulatorRotationPositionTask::Position & pos){
		Poco::Mutex::ScopedLock l(m);
		this->currentStatus.rotation.position = pos.encoder;
		this->currentStatus.rotation.current = 0;
		dump();
	}

	void Manipulator::GetStatus(double & rotation, double & joint1, double & joint2, double & holder){
		Poco::Mutex::ScopedLock l(m);

		rotation = this->currentStatus.rotation.position;
		joint1 = this->currentStatus.joint1.position;
		joint2 = this->currentStatus.joint2.position;

		holder = this->currentStatus.holder.current;
	}

	void Manipulator::LightOn() {
		lightExecution.addTask(lightModule.taskEnable(true));
	}
	void Manipulator::LightOff() {
		lightExecution.addTask(lightModule.taskEnable(false));
	}

	void Manipulator::run() {

		std::cout << "manipulator BG" << std::endl;

		ManipulatorPositionTask::Ptr tBase = magneticModule.taskConsumePosition();
		tBase->PositionChanged += Poco::delegate(this, &Manipulator::onPositionChanged);

		ManipulatorRotationPositionTask::Ptr tRot = rotationModule.taskConsumePosition();
		tRot->PositionChanged += Poco::delegate(this, &Manipulator::onRotationChanged);

		std::cout << "start manipulator bg" << std::endl;
		tBase->start();
		tRot->start();

		while (!finished) {
			if (enabled) {
				rotationModule.askData();
			}
			Poco::Thread::sleep(50);
		}

		std::cout << "done manipulator bg" << std::endl;

		tBase->PositionChanged -= Poco::delegate(this, &Manipulator::onPositionChanged);
		tRot->PositionChanged -= Poco::delegate(this, &Manipulator::onRotationChanged);

		tBase->cancel();
		tRot->cancel();
	}

	void Manipulator::dump(){
		std::cout << "position: r: " << this->currentStatus.rotation.position << " j1: " << this->currentStatus.joint1.position << " j2: " << this->currentStatus.joint2.position << std::endl;
	}

	void Manipulator::feedbackLoop(){

	}

} /* namespace MBot */
