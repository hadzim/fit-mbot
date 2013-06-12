/*
 * Module.h
 *
 *  Created on: 4.3.2013
 *      Author: JV
 */

#ifndef MOTORMODULE_H_
#define MOTORMODULE_H_
#include <string>

#include "TBS/Robo/IModule.h"
#include <Poco/SharedPtr.h>

namespace MBot {
namespace HW {

class MotorModule: public TBS::Robo::IModule {
public:
	typedef Poco::SharedPtr<MotorModule> Ptr;
	typedef MotorModule * RawPtr;

	MotorModule(Name name);
	virtual ~MotorModule();

	const Name & getName() const;

private:
	Name name;
};

}
}
#endif /* MODULE_H_ */
