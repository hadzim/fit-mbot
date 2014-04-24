/*
 * HALFactory.h
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#ifndef HALFACTORY_H_
#define HALFACTORY_H_
#include "IHALFactory.h"

namespace MBot {

class HALFactory : public IHALFactory {
public:
	HALFactory();
	virtual ~HALFactory();

	virtual HAL::API::IMovement::Ptr createMovement();
};

} /* namespace MBot */
#endif /* HALFACTORY_H_ */
