/*
 * Manipulator.cpp
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#include "Manipulator.h"
#include <iostream>
#include <Poco/Delegate.h>
#include <algorithm>

namespace MBot {

	int modulo = 4096;

	static double shorterPosition(double final, double curr) {
		int direction1 = (final + modulo) - curr;

		direction1 = direction1 % modulo;
		int direction2 = direction1;
		if (direction1 < 0) {
			direction2 = direction1 + modulo;
		}
		if (direction1 > 0) {
			direction2 = direction1 - modulo;
		}

		return (std::abs(direction1) < std::abs(direction2)) ? direction1 : direction2;
	}

	static bool shouldStop(Poco::Mutex & posLock, HAL::API::Manipulator::MotorInfo & motorInfo, CurrentCommand & cmd) {
		double currPos = 0;
		double finalPos = 0;
		double startPos = 0;
		double speed = 0;
		{
			Poco::Mutex::ScopedLock l(posLock);
			currPos = motorInfo.position;
		}
		{
			Poco::Mutex::ScopedLock l(cmd.commandLock);
			if (cmd.finalPosition.isEmpty()) {
				return false;
			}
			if (cmd.startPosition.isEmpty()) {
				return false;
			}
			if (cmd.speed.isEmpty()) {
				return false;
			}
			finalPos = cmd.finalPosition.val();
			startPos = cmd.startPosition.val();
			speed = cmd.speed.val();
		}
		double direction = shorterPosition(finalPos, currPos);

		bool stop = false;

		if (direction > 0 && speed < 0) {
			stop = true;
		}
		if (direction < 0 && speed > 0) {
			stop = true;
		}

		//std::cout << "CHECK POS current: " << currPos << " final: " << finalPos << " start: " << startPos << " direction: " << direction << " shouldStop " << (stop ? 1 : 0) << " speed: " << speed << std::endl;

		return stop;
	}

	static void updateCmd(Poco::Mutex & posLock, double & speed, TBS::Nullable<double> final, HAL::API::Manipulator::MotorInfo & motorInfo, CurrentCommand & cmd, bool isRot) {
		{
			Poco::Mutex::ScopedLock l(cmd.commandLock);
			{
				Poco::Mutex::ScopedLock ll();
				cmd.startPosition = motorInfo.position;
			}

			if (final.isSet()) {

				double direction = shorterPosition(final.val(), cmd.startPosition.val());

				std::cout << "DIRECTION: " << direction << "speed: " << speed << std::endl;

				if (direction > 0 && speed < 0) {
					speed = 0;
				}
				if (direction < 0 && speed > 0) {
					speed = 0;
				}
				if (direction == 0) {
					speed = 0;
				}

				int absdir = std::abs(direction);
				if (absdir < 150) {
					//max speed for short distances
					int mlt = absdir / 10;
					if (mlt <= 0)
					mlt = 1;

					std::cout << "LOWER SPEED before " << speed << "absdir: " << absdir << " mlt: " << mlt << std::endl;

					int mltConst = isRot ? 5 : 1000;
					mltConst = mltConst * mlt;

					if (isRot && mltConst < 15) {
						mltConst = 15;
					}

					int newspeed = (speed > 0) ? (mltConst) : (-mltConst);

					if (std::abs(newspeed) < std::abs(speed)) {
						speed = newspeed;
					}

					std::cout << "LOWER SPEED after " << speed << std::endl;
				}

				std::cout << "FINAL SPEED: " << speed << std::endl;
			}

			cmd.finalPosition = final;
			cmd.speed.set(speed);
		}
	}

	static void resetCmd(CurrentCommand & cmd) {
		Poco::Mutex::ScopedLock l(cmd.commandLock);
		cmd.finalPosition.reset();
		cmd.speed.reset();
		cmd.startPosition.reset();
	}

	JointControl::JointControl(int port, HAL::API::Manipulator::MotorInfo & info, Poco::Mutex & infoLock) :
			joint(port), info(info), infoLock(infoLock), jointFeedback(this, &JointControl::feedbackLoopJoint), jointExec(this, &JointControl::execLoopJoint) {
		jointFeedback.start();
		jointExec.start();

		std::cout << "create joint: " << port << std::endl;

	}

	JointControl::~JointControl() {
		jointFeedback.stop();
		jointFeedback.wait();

		jointExec.stop();
		jointExec.wait();
	}

	void JointControl::StartJoint(const double & speed) {
		double sp = speed;
		updateCmd(infoLock, sp, TBS::Nullable<double>(), info, feedbackJointCmd, false);
		{
			Poco::Mutex::ScopedLock l(execLock);
			CurrentExec e;
			e.speed.set(sp);
			this->execJointCmd = e;
		}
	}
	void JointControl::StartJointTo(const double & speed, const double & destination) {
		double sp = speed;
		updateCmd(infoLock, sp, destination, info, feedbackJointCmd, false);
		{
			Poco::Mutex::ScopedLock l(execLock);
			CurrentExec e;
			e.speed.set(sp);
			this->execJointCmd = e;
		}
	}
	void JointControl::StopJoint() {
		{
			Poco::Mutex::ScopedLock l(execLock);
			CurrentExec e;
			e.stop.set(true);
			this->execJointCmd = e;
		}
		resetCmd (feedbackJointCmd);
	}

	void JointControl::execLoopJoint(){
		while (!jointExec.isStopped()) {
			try {
				CurrentExec e;
				{
					Poco::Mutex::ScopedLock l(execLock);
					e = this->execJointCmd;
					this->execJointCmd = CurrentExec();
				}
				if (e.stop.isSet()){
					joint.stop();
				} else if (e.speed.isSet()){
					double speed = e.speed.val();
					joint.go(speed);
				}
			} catch (Poco::Exception & e){
				std::cout << "Error in manipulator execution: " << e.displayText() << std::endl;
			}
			Poco::Thread::sleep(3);
		}
	}

	ManipulatorModule & JointControl::lowLevelModule(){
		return this->joint;
	}

	void JointControl::feedbackLoopJoint() {
		while (!jointFeedback.isStopped()) {
			Poco::Thread::sleep(10);

			if (shouldStop(infoLock, info, feedbackJointCmd)) {
				this->StopJoint();
			}
		}
	}


	Manipulator::Manipulator(TBS::NotificationWorker::Ptr nw, TBS::Robo::RoboCan::IChannel::Ptr canChannel, int portMan1, int portMan2) :
			node("Manipulator", 4, nw, canChannel),

			rotationModule("Manipulator.Rotation", &node, 2),

			holderModule("Manipulator.Holder", &node, 1),

			lightModule("Manipulator.Light", &node, 3),

			magneticModule("Manipulatior.Magnetic", &node, 4),

					speed(20), maxRelDurationTimeInMs(50), t("ManipulatorWorker"), finished(false), enabled(false), rotationFeedback(this,
							&Manipulator::feedbackLoopRot)
#if ALLWORKING
					, j1(portMan1, currentStatus.joint1, m), j2(portMan2, currentStatus.joint2, m)
#endif
	{

		LDEBUG("HAL")<< "Manipulator constructed" << LE;

			HAL::API::Manipulator::MotorInfo mi;
			mi.current = -1;
			mi.position = -1;
			this->currentStatus.holder = this->currentStatus.joint1 = this->currentStatus.joint2 = this->currentStatus.rotation = mi;

			t.start(*this);
			rotationFeedback.start();

			rotationExecution.addTask(rotationModule.taskEnable(true));
			holderExecution.addTask(holderModule.taskEnable(true));
		}

	Manipulator::~Manipulator() {

		rotationExecution.addTask(rotationModule.taskEnable(false));
		holderExecution.addTask(holderModule.taskEnable(false));

		Poco::Thread::sleep(200);

		finished = true;
		t.join();

		rotationFeedback.stop();
		rotationFeedback.wait();
	}

	void Manipulator::Enable() {
		enabled = true;

#if ALLWORKING
		j2.lowLevelModule().enable();
		j1.lowLevelModule().enable();

		Poco::Thread::sleep(800);

		j2.lowLevelModule().unbreakMotor();
		j1.lowLevelModule().unbreakMotor();

		Poco::Thread::sleep(100);
#endif
	}
	void Manipulator::Disable() {
		enabled = false;

#if ALLWORKING

		j2.lowLevelModule().stop();
		j1.lowLevelModule().stop();

		Poco::Thread::sleep(100);

		j2.lowLevelModule().breakMotor();
		j1.lowLevelModule().breakMotor();

		Poco::Thread::sleep(100);

		j1.lowLevelModule().disable();
		j2.lowLevelModule().disable();
#endif
	}

	void Manipulator::StartJoint1(const double & speed) {
		j1.StartJoint(speed);
	}

	void Manipulator::StartJoint1To(const double & speed, const double & destination) {
		j1.StartJointTo(speed, destination);
	}

	void Manipulator::StopJoint1() {
		j1.StopJoint();
	}

	void Manipulator::StartJoint2(const double & speed) {
		j2.StartJoint(speed);
	}

	void Manipulator::StartJoint2To(const double & speed, const double & destination) {
		j2.StartJointTo(speed, destination);
	}

	void Manipulator::StopJoint2() {
		j2.StopJoint();
	}

	void Manipulator::rotateInternally(double sp, TBS::Nullable<double> pos) {

		if (sp > 100)
			sp = 100;
		if (sp < -100)
			sp = -100;

		updateCmd(m, sp, pos, currentStatus.rotation, rotationcmd, true);

		if (sp == 0) {
			LDEBUG("HAL")<< "Manipulator motor stop" << LE;
				rotationExecution.addTask(rotationModule.taskStop());
			} else {
				int aproxVal = std::abs(sp)*1.5;
				int maxDuration = std::min(maxRelDurationTimeInMs, aproxVal);
				LDEBUG("HAL")<< "Manipulator motor goRel: " << sp << " by " << maxDuration << LE;
				std::cout << "ROTATE:" << sp << " max: " << maxDuration << std::endl;
				rotationExecution.addTask(rotationModule.taskGoRel(sp, maxDuration));
			}
		}

	void Manipulator::StartRotation(const double & speed) {
		rotateInternally(speed, TBS::Nullable<double>());
	}

	void Manipulator::StartRotationTo(const double & speed, const double & destination) {
		rotateInternally(speed, destination);
	}

	void Manipulator::StopRotation() {
		std::cout << "ROTATE stop" << std::endl;
		rotationExecution.addTask(rotationModule.taskStop());
		resetCmd(rotationcmd);
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
		std::cout << "pos changed" << std::endl;
		dump();
	}

	void Manipulator::onRotationChanged(ManipulatorRotationPositionTask::Position & pos) {
		Poco::Mutex::ScopedLock l(m);
		this->currentStatus.rotation.position = pos.encoder;
		this->currentStatus.rotation.current = 0;
		std::cout << "rot changed" << std::endl;
		dump();
	}

	void Manipulator::GetStatus(double & rotation, double & joint1, double & joint2, double & holder) {
		Poco::Mutex::ScopedLock l(m);

		std::cout << "get status" << std::endl;
		dump();

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
			rotationModule.askData();
			Poco::Thread::sleep(25);
		}

		std::cout << "done manipulator bg" << std::endl;

		tBase->PositionChanged -= Poco::delegate(this, &Manipulator::onPositionChanged);
		tRot->PositionChanged -= Poco::delegate(this, &Manipulator::onRotationChanged);

		tBase->cancel();
		tRot->cancel();
	}

	void Manipulator::dump() {
		std::cout << "position: r: " << this->currentStatus.rotation.position << " j1: " << this->currentStatus.joint1.position << " j2: "
				<< this->currentStatus.joint2.position << std::endl;
	}

	void Manipulator::feedbackLoopRot() {

		while (!rotationFeedback.isStopped()) {
			Poco::Thread::sleep(5);
			if (shouldStop(m, currentStatus.rotation, rotationcmd)) {
				this->StopRotation();
			}
		}

	}



/*
 void Manipulator::feedbackLoop(){

 }*/

} /* namespace MBot */
