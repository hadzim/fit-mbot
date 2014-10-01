/*
 * main.cpp
 *
 *  Created on: 20.3.2014
 *      Author: JV
 */

#include <iostream>
#include <Poco/NumberParser.h>
#include "HAL/API/MovementClient.h"
#include "HAL/API/ManipulatorClient.h"
#include "HAL/API/api.h"

#include "TBS/Log.h"
#include <Poco/Delegate.h>
#include <Poco/Thread.h>
#include <Poco/Random.h>
/*
void onSpeedChanged(HAL::API::Movement::IMovement::StatusChangedArg & arg){
	std::cout << "Speed: (" << arg.speedLeft << " " << arg.speedRight << ") Odometry: (" << arg.posLeft << ", " << arg.posRight << ")" << std::endl;
}



int main(int argc, char **argv) {

	try {
		std::cout << "HAL Client Starts" << std::endl;
		TBS::initLogs("hal.client", 4);
		{
			HAL::API::MovementClient::Ptr client = new HAL::API::MovementClient();
			client->Movement().StatusChanged += Poco::delegate(&onSpeedChanged);

			double act = 0.0;

			while (1){

				try {
					client->Movement().Move(act, act);
					act += 0.01;
					if (act > 1.0) act = 0;
					std::cout << "Ok" << std::endl;
				} catch (Poco::Exception & e){
					std::cout << "Exc: " << e.displayText() << std::endl;
				}

			}



		}

		std::cout << "HAL Client Stops" << std::endl;
		return 0;
	} catch (Poco::Exception & e){
		std::cerr << "Exception: " << e.displayText() << std::endl;
	} catch (std::exception & e){
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	return 1;
}*/


void onManipulatorChanged(HAL::API::Manipulator::IManipulator::StatusChangedArg & arg){
	std::cout << "pos rotation: " << arg.rotationEncoder << " j1: " << arg.joint1Encoder << " j2: " << arg.joint2Encoder << std::endl;
}

int main(int argc, char **argv) {

	Poco::Random r;

	try {
		std::cout << "HAL Client Starts" << std::endl;
		TBS::initLogs("hal.client", 4);
		{
			HAL::API::ManipulatorClient::Ptr client = new HAL::API::ManipulatorClient();
			client->Manipulator().StatusChanged += Poco::delegate(&onManipulatorChanged);

			//while (1){

				//client->Manipulator().Enable();

				Poco::Thread::sleep(200);




				Poco::Thread::sleep(5000);

				//client->Manipulator().Disable();

				Poco::Thread::sleep(500);

			//}
			client->Manipulator().StatusChanged -= Poco::delegate(&onManipulatorChanged);

/*
			while (1){

				try {
					client->Movement().Move(act, act);
					act += 0.01;
					if (act > 1.0) act = 0;
					std::cout << "Ok" << std::endl;
				} catch (Poco::Exception & e){
					std::cout << "Exc: " << e.displayText() << std::endl;
				}

			}*/



		}

		std::cout << "HAL Client Stops" << std::endl;
		return 0;
	} catch (Poco::Exception & e){
		std::cerr << "Exception: " << e.displayText() << std::endl;
	} catch (std::exception & e){
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	return 1;
}
