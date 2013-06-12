/*
 * Module.cpp
 *
 *  Created on: 4.3.2013
 *      Author: JV
 */

#include <string>
#include "MBot/HW/MotorModule.h"

namespace MBot {
namespace HW {

MotorModule::MotorModule(Name name) {

}

MotorModule::~MotorModule() {

}

const MotorModule::Name & MotorModule::getName() const {
	return name;
}

} /* namespace HW */
} /* namespace MBot */

