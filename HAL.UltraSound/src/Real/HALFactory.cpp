/*
 * HALFactory.cpp
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#include "HALFactory.h"

#include "UltraSound.h"


namespace MBot {

HALFactory::HALFactory(int port) : port(port) {

}

HALFactory::~HALFactory() {

}

HAL::API::UltraSound::IUltraSound::Ptr HALFactory::createUltraSound(){
	return new UltraSound(port);
}

} /* namespace MBot */
