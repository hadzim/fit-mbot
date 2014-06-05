/*
 * ICanWorker.h
 *
 *  Created on: Jun 3, 2014
 *      Author: dron
 */

#ifndef ICANWORKER_H_
#define ICANWORKER_H_
#include <Poco/BasicEvent.h>
#include "CANFrame.h"

namespace can {

class ICanWorker {
public:
	typedef Poco::SharedPtr<ICanWorker> Ptr;
	ICanWorker();
	virtual ~ICanWorker();

	Poco::BasicEvent <CANFrame::Ptr> FrameReady;
	virtual void sendFrame(CANFrame::Ptr frame) = 0;

	static ICanWorker::Ptr create();
};

} /* namespace can */

#endif /* ICANWORKER_H_ */
