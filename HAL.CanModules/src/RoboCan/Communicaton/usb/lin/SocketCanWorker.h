/*
 * SocketCanWorker.h
 *
 *  Created on: Jun 3, 2014
 *      Author: dron
 */

#ifndef SOCKETCANWORKER_H_
#define SOCKETCANWORKER_H_
#include <RoboCan/Communicaton/usb/ICanWorker.h>
#include "Poco/Runnable.h"

#include "SocketCan.h"

namespace can {

class SocketCanWorker : public ICanWorker, public Poco::Runnable {
public:
	SocketCanWorker(int canId);
	virtual ~SocketCanWorker();

	virtual void sendFrame(CANFrame::Ptr frame);

private:
	virtual void run();
private:
	SocketCan socketCan;
	Poco::Thread t;
	bool finished;
	Poco::Mutex m;
};

} /* namespace can */

#endif /* SOCKETCANWORKER_H_ */
