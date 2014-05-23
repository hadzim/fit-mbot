/*
 * UsbChannel.h
 *
 *  Created on: 23.4.2014
 *      Author: JV
 */

#ifndef USBCHANNEL_H_
#define USBCHANNEL_H_

#include "Poco/Runnable.h"
#include "TBS/Robo/RoboCan/Communicaton/IChannel.h"
#include <deque>

class CanFrame;

namespace TBS {
namespace Robo {
namespace RoboCan {

class UsbChannel: public Poco::Runnable, public TBS::Robo::RoboCan::IChannel {
	typedef std::deque<TBS::Robo::RoboCan::CanMessage> CanMessages;
public:
	UsbChannel();
	virtual ~UsbChannel();

	virtual void sendCanMessage(
			const TBS::Robo::RoboCan::CanMessage & canMessage);
protected:
	virtual void run();
	//virtual void processNotification(Poco::Notification::Ptr notification);
private:
	void onFrame(Poco::SharedPtr<CANFrame> & f);

private:
	Poco::Thread thread;
	bool stopThread;

	CanMessages canList;
	Poco::Mutex m;

};

}
}
} /* namespace TBS */
#endif /* USBCHANNEL_H_ */
