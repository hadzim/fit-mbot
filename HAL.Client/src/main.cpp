/*
 * main.cpp
 *
 *  Created on: 20.3.2014
 *      Author: JV
 */

#include <iostream>
#include <Poco/NumberParser.h>
#include "HAL/API/MovementClient.h"
#include "TBS/Log.h"
#include <Poco/Delegate.h>

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


			/*
			while (1){
				std::string str;
				std::cin >> str;

				try {
					if (str == "x"){
						break;
					}

					double val1 = Poco::NumberParser::parseFloat(str);
					double val2 = val1;
					std::cout << "try move: " << val1 << std::endl;
					client->Movement().Move(val1, val2);
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
