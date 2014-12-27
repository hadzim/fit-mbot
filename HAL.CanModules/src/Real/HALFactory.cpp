//------------------------------------------------------------------------------
//
//  Project:   VG20102014024
//             Robot for search of human beings in crushes and avalanches
//
//             Brno University of Technology
//             Faculty of Information Technology
//
//------------------------------------------------------------------------------
//
//             This project was financially supported by project
//                  VG20102014024 funds provided by MV CR.
//
//------------------------------------------------------------------------------
/*!

@file
@brief     Implementation of methods
@details   Details
@authors   Jan Vana (<ivanajan@fit.vutbr.cz>)
@date      2010-2014
@note      This project was supported by project funds of the MV CR grant VG20102014024.

*/
#include "HALFactory.h"
#include "BioRadar.h"
#include "Camera.h"

#include "Manipulator.h"

namespace MBot {

	HALFactory::HALFactory(int portMan1, int portMan2) : portMan1(portMan1), portMan2(portMan2) {
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
		return new Manipulator(nw, canChannel, portMan1, portMan2);
	}

	} /* namespace MBot */
