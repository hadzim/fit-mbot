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
#include "HAL/API/Movement.h"

namespace MBot {

class IHALFactory {
public:
	typedef Poco::SharedPtr <IHALFactory> Ptr;
	virtual ~IHALFactory() {
	}
	virtual HAL::API::Movement::IMovement::Ptr createMovement() = 0;
};

} /* namespace MBot */
#endif /* FACTORIES_H_ */
