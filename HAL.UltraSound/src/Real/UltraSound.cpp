/*
 * UltraSound.cpp
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#include "UltraSound.h"
#include <iostream>

#include "TBS/Log.h"

namespace MBot {

UltraSound::UltraSound() :
		finish(false), reconnect(true), isDataValid(false),  frontLeft(0), frontRight(0), backLeft(0), backRight(0) {

	t.start(*this);
}

UltraSound::~UltraSound() {
	finish = true;
	t.join();

}

void UltraSound::Reconnect() {
	this->reconnect = true;
}


void UltraSound::GetStatus(HAL::API::UltraSound::TouchSensors & frontSensors,
		HAL::API::UltraSound::TouchSensors & backSensors, bool & isValid) {

	Poco::Mutex::ScopedLock l(dataMutex);
	frontSensors.left.distance = frontLeft;
	frontSensors.right.distance = frontRight;

	backSensors.left.distance = backLeft;
	backSensors.right.distance = backRight;

	isValid = this->isDataValid;

}

void UltraSound::run() {

	LDEBUG("US") << "Bg Run" << LE;

	UltraSoundModule::Ptr module;

	while (!this->finish) {
		try {

			if (reconnect){
				reconnect = false;
				LDEBUG("US") << "Enable" << LE;

				module = NULL;
				module = new UltraSoundModule(10, 19200);

				LDEBUG("US") << "construct" << LE;

				module->connect();
				LDEBUG("US") << "connect" << LE;
				module->activate();

				LDEBUG("US") << "Enable done" << LE;
			}



			std::vector <int> data = module->readData();

			{
				Poco::Mutex::ScopedLock l(dataMutex);
				this->frontLeft = data.at(0);
				this->frontRight = data.at(1);
				this->backLeft = data.at(2);
				this->backRight = data.at(3);
				this->isDataValid = true;
			}
		} catch (Poco::Exception & e) {
			//std::cerr << "EXC: " << e.displayText() << std::endl;
			LERROR("Serial") << "EXC: " << e.displayText() << LE;
			this->isDataValid = false;
		} catch (std::exception & e) {
			//std::cerr << "EXC: " << e.what() << std::endl;
			LERROR("Serial") << "EXC: " << e.what() << LE;
			this->isDataValid = false;
		} catch (...) {
			//std::cerr << "EXC: ?" << std::endl;
			LERROR("Serial") << "EXC: ?"  << LE;
			this->isDataValid = false;
		}

		Poco::Thread::sleep(203);
	}

	LDEBUG("US") << "Bg Done" << LE;
}

} /* namespace MBot */
