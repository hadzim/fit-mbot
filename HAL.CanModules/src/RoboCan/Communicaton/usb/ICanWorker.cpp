/*
 * ICanWorker.cpp
 *
 *  Created on: Jun 3, 2014
 *      Author: dron
 */

#include <RoboCan/Communicaton/usb/ICanWorker.h>

#ifdef _WIN32
#include "win/SystecInterface.h"
#else
#include "lin/SocketCanWorker.h"
#endif

namespace can {

ICanWorker::ICanWorker() {
	// TODO Auto-generated constructor stub

}

ICanWorker::~ICanWorker() {
	// TODO Auto-generated destructor stub
}

ICanWorker::Ptr ICanWorker::create() {
#ifdef _WIN32
	return new SystecInterface(500);
#else
	return new SocketCanWorker(0);
#endif
}

} /* namespace can */
