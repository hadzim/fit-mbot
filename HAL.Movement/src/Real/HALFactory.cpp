/*
 * HALFactory.cpp
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#include "HALFactory.h"
#include "Movement.h"

namespace MBot {

HALFactory::HALFactory(int port) : port(port) {

}

HALFactory::~HALFactory() {

}

HAL::API::Movement::IMovement::Ptr HALFactory::createMovement(){
	return new Movement(port);
}

} /* namespace MBot */
