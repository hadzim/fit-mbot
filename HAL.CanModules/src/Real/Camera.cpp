/*
 * Camera.cpp
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#include "Camera.h"
#include <iostream>
#include <Poco/Delegate.h>

namespace MBot {

Camera::Camera(TBS::NotificationWorker::Ptr nw,
		TBS::Robo::RoboCan::IChannel::Ptr canChannel) :
		node("Camera", 1, nw, canChannel),

		motorModule("Camera.Motor", &node, 1),

		servo1Module("Camera.Servo1", &node, 2),

		servo2Module("Camera.Servo2", &node, 3),

		lightModule("Camera.Light", &node, 4),

		speed(20), maxRelDurationTimeInMs(50), t("CameraWorker"), finished(
				false), enabled(false) {
	LDEBUG("HAL")<< "Camera constructed" << LE;
		t.start(*this);
	}

Camera::~Camera() {
	finished = true;
	t.join();
}

void Camera::Enable() {
	enabled = true;
	motorExecution.addTask(motorModule.taskEnable(true));
	servo1Execution.addTask(servo1Module.taskEnable(true));
	servo2Execution.addTask(servo2Module.taskEnable(true));
}
void Camera::Disable() {
	enabled = false;
	motorExecution.addTask(motorModule.taskEnable(false));
	servo1Execution.addTask(servo1Module.taskEnable(false));
	servo2Execution.addTask(servo2Module.taskEnable(false));
}

static void internalGoMin(TBS::Task::OneActiveTaskExectution & execution,
		MBot::CameraMotorModule & module) {
	execution.addTask(module.taskGoMin());
}
static void internalGoMax(TBS::Task::OneActiveTaskExectution & execution,
		MBot::CameraMotorModule & module) {
	execution.addTask(module.taskGoMax());
}
static void internalGoRel(TBS::Task::OneActiveTaskExectution & execution,
		MBot::CameraMotorModule & module, double speed, int maxDuration) {
	if (speed == 0) {
		LDEBUG("HAL")<< "Camera motor stop" << LE;
			execution.addTask(module.taskStop());
		} else {
			LDEBUG("HAL")<< "Camera motor goRel: " << speed << " by " << maxDuration << LE;
			execution.addTask(module.taskGoRel(speed, maxDuration));
		}
	}

void Camera::GoMinEngine() {
	internalGoMin(motorExecution, motorModule);
}
void Camera::GoMaxEngine() {
	internalGoMax(motorExecution, motorModule);
}

void Camera::GoRelEngine(const double & speed) {
	internalGoRel(motorExecution, motorModule, speed,
			maxRelDurationTimeInMs * 5);
}

void Camera::GoMinServo1() {
	internalGoMin(servo1Execution, servo1Module);
}
void Camera::GoMaxServo1() {
	internalGoMax(servo1Execution, servo1Module);
}
void Camera::GoRelServo1(const double & speed) {
	internalGoRel(servo1Execution, servo1Module, speed, maxRelDurationTimeInMs);
}

void Camera::GoMinServo2() {
	internalGoMin(servo2Execution, servo2Module);
}
void Camera::GoMaxServo2() {
	internalGoMax(servo2Execution, servo2Module);
}
void Camera::GoRelServo2(const double & speed) {
	internalGoRel(servo2Execution, servo2Module, speed, maxRelDurationTimeInMs);
}

void Camera::LightOn() {
	lightExecution.addTask(lightModule.taskEnable(true));
}
void Camera::LightOff() {
	lightExecution.addTask(lightModule.taskEnable(false));
}

void Camera::run() {

	while (!finished) {
		if (enabled) {
			//TODO
			//std::cout << "running" << std::endl;
		}

		Poco::Thread::sleep(250);
	}
}

} /* namespace MBot */
