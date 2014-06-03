/*
 * SocketCanWorker.cpp
 *
 *  Created on: Jun 3, 2014
 *      Author: dron
 */

#include <RoboCan/Communicaton/usb/lin/SocketCanWorker.h>

#include "TBS/Log.h"
#include <iostream>
#ifndef _WIN32

namespace can {

SocketCanWorker::SocketCanWorker(int canid) :
		socketCan(canid), t("CanSocket"), finished(false) {

	t.start(*this);
}

SocketCanWorker::~SocketCanWorker() {
	finished = true;
	t.join();
}

void SocketCanWorker::sendFrame(CANFrame::Ptr frame) {
	Poco::Mutex::ScopedLock l(m);
	this->socketCan.canWrite(frame);
}

void SocketCanWorker::run() {

	while (!finished) {
		try {
			CANFrame::PtrList frames;
			{
				Poco::Mutex::ScopedLock l(m);
				socketCan.canRead(frames);
			}
			for (CANFrame::PtrList::iterator i = frames.begin();
					i != frames.end(); i++) {
				this->FrameReady.notify(this, *i);
			}
			Poco::Thread::sleep(5);
		} catch (Poco::Exception & e) {
			std::cerr << "Error in can reading: " << e.displayText() << std::endl;
			LERROR("SocketCan") << "Error in can reading: " << e.displayText() << LE;
			Poco::Thread::sleep(100);
		}
	}
}


} /* namespace can */

#endif
