/*
 * main.cpp
 *
 *  Created on: 20.3.2014
 *      Author: JV
 */

#include <iostream>
#include <Poco/NumberParser.h>
#include "HAL/API/MovementSvc_DBus.h"
#include "TBS/Log.h"

int main(int argc, char **argv) {

	try {
		std::cout << "HAL Client Starts" << std::endl;
		TBS::initLogs("hal.client", 6);
		{
			HAL::API::Movement::DBus::Client::Ptr client = new HAL::API::Movement::DBus::Client();
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
}
