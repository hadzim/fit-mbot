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
					speed(20), maxRelDurationTimeInMs(50), t("ManipulatorWorker"), finished(false), enabled(false),
					joint1Feedback(this, &Manipulator::feedbackLoopJoint1),
					joint2Feedback(this, &Manipulator::feedbackLoopJoint2),
					rotationFeedback(this, &Manipulator::feedbackLoopRot)
					{

		LDEBUG("HAL")<< "Manipulator constructed" << LE;

			HAL::API::Manipulator::MotorInfo mi;
			mi.current = -1;
			mi.position = -1;
			this->currentStatus.holder = this->currentStatus.joint1 = this->currentStatus.joint2 = this->currentStatus.rotation = mi;

			t.start(*this);
			joint1Feedback.start();
			joint2Feedback.start();
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

		joint1Feedback.stop();
		joint1Feedback.wait();

		joint2Feedback.stop();
		joint2Feedback.wait();

		rotationFeedback.stop();
		rotationFeedback.wait();
	}

	void Manipulator::Enable() {
		enabled = true;

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




	void Manipulator::StartJoint1(const double & speed) {
		double sp = speed;
		updateCmd(sp, TBS::Nullable<double>(), currentStatus.joint1, joint1cmd, false);
		joint1.go(sp);
	}

	void Manipulator::StartJoint1To(const double & speed, const double & destination){
		double sp = speed;
		updateCmd(sp, destination, currentStatus.joint1, joint1cmd, false);
		joint1.go(sp);
	}

	void Manipulator::StopJoint1() {
		joint1.stop();
		resetCmd(joint1cmd);
	}

	void Manipulator::StartJoint2(const double & speed) {
		double sp = speed;
		updateCmd(sp, TBS::Nullable<double>(), currentStatus.joint2, joint2cmd, false);
		joint2.go(sp);
	}



	void Manipulator::StartJoint2To(const double & speed, const double & destination){
		double sp = speed;
		updateCmd(sp, destination, currentStatus.joint2, joint2cmd, false);
		joint2.go(sp);
	}

	void Manipulator::StopJoint2() {
		joint2.stop();
		resetCmd(joint2cmd);
	}

	void Manipulator::rotateInternally(double sp, TBS::Nullable<double> pos){

		if (sp > 100) sp = 100;
		if (sp < -100) sp = -100;

		updateCmd(sp, pos, currentStatus.rotation, rotationcmd, true);

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



	void Manipulator::StartRotationTo(const double & speed, const double & destination){
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

	void Manipulator::onRotationChanged(ManipulatorRotationPositionTask::Position & pos){
		Poco::Mutex::ScopedLock l(m);
		this->currentStatus.rotation.position = pos.encoder;
		this->currentStatus.rotation.current = 0;
		std::cout << "rot changed" << std::endl;
		dump();
	}

	void Manipulator::GetStatus(double & rotation, double & joint1, double & joint2, double & holder){
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

	void Manipulator::dump(){
		std::cout << "position: r: " << this->currentStatus.rotation.position << " j1: " << this->currentStatus.joint1.position << " j2: " << this->currentStatus.joint2.position << std::endl;
	}

	static double shorterPosition(double final, double curr){
		int direction1 = (final + modulo) - curr;

		direction1 = direction1 % modulo;
		int direction2 = direction1;
		if (direction1 < 0){
			direction2 = direction1 + modulo;
		}
		if (direction1 > 0){
			direction2 = direction1 - modulo;
		}

		return (std::abs(direction1) < std::abs(direction2)) ? direction1 : direction2;
	}

	void Manipulator::checkActivity(JointID jid, HAL::API::Manipulator::MotorInfo & motorInfo, CurrentCommand & cmd){
		double currPos = 0;
		double finalPos = 0;
		double startPos = 0;
		double speed = 0;
		{
			Poco::Mutex::ScopedLock l(m);
			currPos = motorInfo.position;
		}
		{
			Poco::Mutex::ScopedLock l(cmd.commandLock);
			if (cmd.finalPosition.isEmpty()){
				return;
			}
			if (cmd.startPosition.isEmpty()){
				return;
			}
			if (cmd.speed.isEmpty()){
				return;
			}
			finalPos = cmd.finalPosition.val();
			startPos = cmd.startPosition.val();
			speed = cmd.speed.val();
		}
		double direction = shorterPosition(finalPos, currPos);

		bool stop = false;

		if (direction > 0 && speed < 0){
			stop = true;
		}
		if (direction < 0 && speed > 0){
			stop = true;
		}

		//std::cout << "CHECK POS current: " << currPos << " final: " << finalPos << " start: " << startPos << " direction: " << direction << " shouldStop " << (stop ? 1 : 0) << " speed: " << speed << std::endl;

		if (stop){
			std::cout << "FORCED STOP !!!" << std::endl;
			if (jid == J1){
				StopJoint1();
			}
			if (jid == J2){
				StopJoint2();
			}
			if (jid == Rot){
				StopRotation();
			}
		}
	}

	void Manipulator::feedbackLoopJoint1(){
		while (!joint1Feedback.isStopped()){
			Poco::Thread::sleep(10);
			this->checkActivity(J1, currentStatus.joint1, joint1cmd);
		}
	}
	void Manipulator::feedbackLoopJoint2(){

		while (!joint1Feedback.isStopped()){
			Poco::Thread::sleep(5);
			this->checkActivity(J2, currentStatus.joint2, joint2cmd);
		}
	}

	void Manipulator::feedbackLoopRot(){

			while (!rotationFeedback.isStopped()){
				Poco::Thread::sleep(5);
				this->checkActivity(Rot, currentStatus.rotation, rotationcmd);
			}
		}

	void Manipulator::updateCmd(double & speed, TBS::Nullable<double> final, HAL::API::Manipulator::MotorInfo & motorInfo, CurrentCommand & cmd, bool isRot){
		{
			Poco::Mutex::ScopedLock l(cmd.commandLock);
			{
				Poco::Mutex::ScopedLock ll(m);
				cmd.startPosition = motorInfo.position;
			}

			if (final.isSet()){


				double direction = shorterPosition(final.val(), cmd.startPosition.val());

				std::cout << "DIRECTION: " << direction << "speed: " << speed << std::endl;

				if (direction > 0 && speed < 0){
					speed = 0;
				}
				if (direction < 0 && speed > 0){
					speed = 0;
				}
				if (direction == 0){
					speed = 0;
				}


				int absdir = std::abs(direction);
				if (absdir < 150){
					//max speed for short distances
					int mlt = absdir / 10;
					if (mlt <= 0) mlt = 1;

					std::cout << "LOWER SPEED before " << speed << "absdir: " << absdir << " mlt: " << mlt << std::endl;

					int mltConst = isRot ? 5 : 1000;
					mltConst = mltConst * mlt;

					if (isRot && mltConst < 15){
						mltConst = 15;
					}

					int newspeed = (speed > 0) ? (mltConst) : (-mltConst);

					if (std::abs(newspeed) < std::abs(speed)){
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

	void Manipulator::resetCmd(CurrentCommand & cmd){
		Poco::Mutex::ScopedLock l(cmd.commandLock);
		cmd.finalPosition.reset();
		cmd.speed.reset();
		cmd.startPosition.reset();
	}

/*
	void Manipulator::feedbackLoop(){

	}*/

} /* namespace MBot */
