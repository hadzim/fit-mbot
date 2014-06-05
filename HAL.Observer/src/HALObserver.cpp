/*
 * BoardSensors.cpp
 *
 *  Created on: Jan 31, 2013
 *      Author: root
 */

#include "HALObserver.h"
#include <iostream>
#include <Poco/Delegate.h>
#include "Poco/Thread.h"

#include "HAL/API/MovementSvc_DBus.h"

namespace HAL {

HALObserver::HALObserver() {

}

HALObserver::~HALObserver() {

}

void onSpeedChanged(HAL::API::Movement::IMovement::StatusChangedArg & arg){
	std::cout << "Speed: (" << arg.speedLeft << " " << arg.speedRight << ") Odometry: (" << arg.posLeft << ", " << arg.posRight << ")" << std::endl;
}

int HALObserver::main(const std::vector<std::string>& args) {

	std::cout << "-------------------" << std::endl;
	std::cout << "HAL Observer Starts" << std::endl;
	std::cout << "-------------------" << std::endl;

	std::cout << std::endl;

	{

		{
			HAL::API::Movement::DBus::Client::Ptr client = new HAL::API::Movement::DBus::Client();
			client->Movement().StatusChanged += Poco::delegate(&onSpeedChanged);
			waitForTerminationRequest();
			client->Movement().StatusChanged -= Poco::delegate(&onSpeedChanged);
		}
	}

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "------------------" << std::endl;
	std::cout << "HAL Observer Stops" << std::endl;
	std::cout << "------------------" << std::endl;

	return EXIT_OK;
}

} /* namespace BB */
