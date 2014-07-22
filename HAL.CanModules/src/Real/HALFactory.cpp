/*
 * HALFactory.cpp
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#include "HALFactory.h"
#include "BioRadar.h"
#include "Camera.h"

#include "Manipulator.h"

namespace MBot {

	HALFactory::HALFactory() {
		LDEBUG("HAL")<< "createfactory" << LE;
			nw = new TBS::NotificationWorker("Can");
			canChannel = new TBS::Robo::RoboCan::UsbChannel();
			LDEBUG("HAL") << "createfactory done" << LE;
		}

	HALFactory::~HALFactory() {

	}

	HAL::API::BioRadar::IBioRadar::Ptr HALFactory::createBioRadar() {
		LDEBUG("HAL")<< "createBioRadar" << LE;
			return new BioRadar(nw, canChannel);
		}

	HAL::API::Camera::ICamera::Ptr HALFactory::createCamera() {
		LDEBUG("HAL")<< "createCamera" << LE;
			return new Camera(nw, canChannel);
		}

	HAL::API::Manipulator::IManipulator::Ptr HALFactory::createManipulator(){
		return new Manipulator(nw, canChannel);
	}

	} /* namespace MBot */
