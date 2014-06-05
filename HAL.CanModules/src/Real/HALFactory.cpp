/*
 * HALFactory.cpp
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#include "HALFactory.h"
#include "BioRadar.h"


namespace MBot {

HALFactory::HALFactory() {
	LDEBUG("HAL") << "createfactory" << LE;
	nw = new TBS::NotificationWorker("Can");
	canChannel = new TBS::Robo::RoboCan::UsbChannel();
	LDEBUG("HAL") << "createfactory done" << LE;
}

HALFactory::~HALFactory() {

}

HAL::API::BioRadar::IBioRadar::Ptr HALFactory::createBioRadar(){
	LDEBUG("HAL") << "createBioRadarBase" << LE;
	return new BioRadar(nw, canChannel);
	//return new Movement();
}

} /* namespace MBot */
