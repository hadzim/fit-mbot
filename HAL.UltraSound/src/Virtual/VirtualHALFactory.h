/*
 * VirtualHALFactory.h
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#ifndef VIRTUALHALFACTORY_H_
#define VIRTUALHALFACTORY_H_
#include "IHALFactory.h"
#include "VirtualUS.h"

namespace MBot {

class VirtualHALFactory: public IHALFactory {
public:
	VirtualHALFactory();
	virtual ~VirtualHALFactory();

	virtual HAL::API::UltraSound::IUltraSound::Ptr createUltraSound(){
		return new VirtualUS();
	}
};

} /* namespace MBot */
#endif /* VIRTUALHALFACTORY_H_ */
