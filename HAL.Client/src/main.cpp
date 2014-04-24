/*
 * main.cpp
 *
 *  Created on: 20.3.2014
 *      Author: JV
 */

#include <iostream>
#include <Poco/NumberParser.h>
#include "HAL/API/MovementSvc_DBus.h"

int main(int argc, char **argv) {

	try {
		std::cout << "HAL Client Starts" << std::endl;

		{
			HAL::API::DBus::Client::Ptr client = new HAL::API::DBus::Client();
			while (1){
				std::string str;
				std::cin >> str;

				try {
					if (str == "x"){
						break;
					}

					double val1 = Poco::NumberParser::parseFloat(str);
					double val2 = val1;
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
