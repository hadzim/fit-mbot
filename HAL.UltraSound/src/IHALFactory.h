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
#include "HAL/API/UltraSound.h"

namespace MBot {

class IHALFactory {
public:
	typedef Poco::SharedPtr <IHALFactory> Ptr;
	virtual ~IHALFactory() {
	}
	virtual HAL::API::UltraSound::IUltraSound::Ptr createUltraSound() = 0;
};

} /* namespace MBot */
#endif /* FACTORIES_H_ */
