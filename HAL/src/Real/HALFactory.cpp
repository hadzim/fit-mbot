/*
 * HALFactory.cpp
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#include "HALFactory.h"
#include "Movement.h"

namespace MBot {

HALFactory::HALFactory() {

}

HALFactory::~HALFactory() {

}

HAL::API::IMovement::Ptr HALFactory::createMovement(){
	return new Movement();
}

} /* namespace MBot */
