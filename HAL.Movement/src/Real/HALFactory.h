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
	HALFactory(int port);
	virtual ~HALFactory();

	virtual HAL::API::Movement::IMovement::Ptr createMovement();
private:
	int port;
};

} /* namespace MBot */
#endif /* HALFACTORY_H_ */
