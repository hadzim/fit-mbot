/*
 * VirtualHALFactory.h
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#ifndef VIRTUALHALFACTORY_H_
#define VIRTUALHALFACTORY_H_
#include "IHALFactory.h"
#include "VirtualMovement.h"

namespace MBot {

class VirtualHALFactory: public IHALFactory {
public:
	VirtualHALFactory();
	virtual ~VirtualHALFactory();

	virtual HAL::API::Movement::IMovement::Ptr createMovement() {
		return new VirtualMovement();
	}
};

} /* namespace MBot */
#endif /* VIRTUALHALFACTORY_H_ */
