/*
 * main.cpp
 *
 *  Created on: 20.3.2014
 *      Author: JV
 */

#include <iostream>
#include <Poco/NumberParser.h>
#include "HAL/API/MovementClient.h"

#include "HAL/API/ManipulatorSvc_Json.h"
#include "HAL/API/Manipulator.h"
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




int main(int argc, char **argv) {

	Poco::Random r;

	try {
		std::cout << "HAL Client Starts" << std::endl;
		TBS::initLogs("hal.client", 4);
		{
			TBS::Services::JsonClientParams mc("localhost", HAL::API::Communication::ManipulatorPort, TBS::Services::JsonClientParams::JsonHttp);
			HAL::API::Manipulator::Json::Client::Ptr manipulatorClient = new HAL::API::Manipulator::Json::Client(mc);


			while (1){

				manipulatorClient->Manipulator().Enable();

				Poco::Thread::sleep(200);

				std::cout << "Iteration" << std::endl;

				for (int j = 15; j < 50; j+= 10){
					int wait = r.next(15);

					for (int i = 0; i < j; i++){
						try {
							manipulatorClient->Manipulator().StartHolder(50);
							Poco::Thread::sleep(wait);
							//std::cout << "Ok" << std::endl;
						} catch (Poco::Exception & e){
							std::cout << "Exc: " << e.displayText() << std::endl;
						}
					}

					for (int i = 0; i < j; i++){
						try {
							manipulatorClient->Manipulator().StartHolder(-50);
							Poco::Thread::sleep(wait);
							//std::cout << "Ok" << std::endl;
						} catch (Poco::Exception & e){
							std::cout << "Exc: " << e.displayText() << std::endl;
						}
					}
				}


				try {
					manipulatorClient->Manipulator().StartRotation(50);
					Poco::Thread::sleep(300);
					//std::cout << "Ok" << std::endl;
				} catch (Poco::Exception & e){
					std::cout << "Exc: " << e.displayText() << std::endl;
				}

				try {
					manipulatorClient->Manipulator().StartRotation(-50);
					Poco::Thread::sleep(300);
					//std::cout << "Ok" << std::endl;
				} catch (Poco::Exception & e){
					std::cout << "Exc: " << e.displayText() << std::endl;
				}

				Poco::Thread::sleep(200);

				manipulatorClient->Manipulator().Disable();

				Poco::Thread::sleep(500);

			}


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
