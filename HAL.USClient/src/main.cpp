/*
 * main.cpp
 *
 *  Created on: 20.3.2014
 *      Author: JV
 */

#include <iostream>
#include <Poco/NumberParser.h>
#include "HAL/API/UltraSoundSvc_Json.h"
#include "HAL/API/api.h"
#include "TBS/Log.h"
#include <Poco/Delegate.h>



int main(int argc, char **argv) {

	try {
		std::cout << "HAL Client Starts" << std::endl;
		TBS::initLogs("hal.client", 4);
		{
			TBS::Services::JsonClientParams p("localhost", HAL::API::Communication::UltraSoundPort, TBS::Services::JsonClientParams::JsonHttp);
			HAL::API::UltraSound::Json::Client client(p);
			client.UltraSound().Reconnect();

			while (1){

				try {
					bool isValid = false;
					HAL::API::UltraSound::TouchSensors f;
					HAL::API::UltraSound::TouchSensors b;
					client.UltraSound().GetStatus(f,b, isValid);
					if (isValid){
						std::cout << "Ok: fl: " << f.left.distance  << " fr: " << f.right.distance << " bl: " << b.left.distance << " br: " << b.right.distance << std::endl;
					} else {
						std::cout << "invalid" << std::endl;
					}
					Poco::Thread::sleep(1000);
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
