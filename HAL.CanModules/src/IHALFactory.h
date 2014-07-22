/*
 * Factories.h
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#ifndef FACTORIES_H_
#define FACTORIES_H_

#include "ObjectFactory.h"
#include <Poco/SharedPtr.h>
#include "HAL/API/BioRadar.h"
#include "HAL/API/Camera.h"
#include "HAL/API/Manipulator.h"

namespace MBot {

class IHALFactory {
public:
	typedef Poco::SharedPtr <IHALFactory> Ptr;
	virtual ~IHALFactory() {
	}
	virtual HAL::API::BioRadar::IBioRadar::Ptr createBioRadar() = 0;
	virtual HAL::API::Camera::ICamera::Ptr createCamera() = 0;

	virtual HAL::API::Manipulator::IManipulator::Ptr createManipulator() = 0;


};

} /* namespace MBot */
#endif /* FACTORIES_H_ */
