/*
 * NetChannel.cpp
 *
 *  Created on: 28.3.2013
 *      Author: JV
 */

#include <iostream>
#include "usb/CANFrame.h"
#include "usb/ICanWorker.h"
#include <Poco/Delegate.h>
#include "TBS/Robo/RoboCan/Communication/UsbChannel.h"

namespace TBS {
namespace Robo {
namespace RoboCan {

static TBS::Robo::RoboCan::CanMessage messageFromFrame(CANFrame::Ptr frame) {
	TBS::Robo::RoboCan::CanMessage message;

	message.canID = frame->ID();
	message.length = frame->DLC();

	message.b0 = frame->getData8(0);
	message.b1 = frame->getData8(1);
	message.b2 = frame->getData8(2);
	message.b3 = frame->getData8(3);
	message.b4 = frame->getData8(4);
	message.b5 = frame->getData8(5);
	message.b6 = frame->getData8(6);
	message.b7 = frame->getData8(7);

	return message;
}

static CANFrame::Ptr frameFromMessage(TBS::Robo::RoboCan::CanMessage msg) {
	CANFrame::Ptr sendframe(new CANFrame());
	sendframe->setID(msg.canID);

	sendframe->setRTR(0);
	sendframe->setDLC(msg.length);

	sendframe->setData8(0, msg.b0);
	sendframe->setData8(1, msg.b1);
	sendframe->setData8(2, msg.b2);
	sendframe->setData8(3, msg.b3);
	sendframe->setData8(4, msg.b4);
	sendframe->setData8(5, msg.b5);
	sendframe->setData8(6, msg.b6);
	sendframe->setData8(7, msg.b7);

	return sendframe;
}

UsbChannel::UsbChannel() :
		thread("Usb"), stopThread(false) {
	std::cout << "usb channel construct" << std::endl;
	thread.start(*this);
	std::cout << "usb channel construct done" << std::endl;
}

UsbChannel::~UsbChannel() {
	std::cout << "usb destruct" << std::endl;
	stopThread = true;
	thread.join();
	std::cout << "usb destructed" << std::endl;
}

void UsbChannel::sendCanMessage(
		const TBS::Robo::RoboCan::CanMessage & canMessage) {
	Poco::Mutex::ScopedLock l(m);
	canList.push_back(canMessage);
}

void UsbChannel::onFrame(CANFrame::Ptr & f) {
	TBS::Robo::RoboCan::CanMessage message = messageFromFrame(f);
	//std::cout << std::endl;
	std::cout << "recv: " << message.toString() << std::endl;
	//std::cout << std::endl;
	this->MessageRetrieved.notify(this, message);
}

void UsbChannel::run() {
	try {
		std::cout << "start usb bg" << std::endl;
		can::ICanWorker::Ptr interface = can::ICanWorker::create();


		interface->FrameReady += Poco::delegate(this, &UsbChannel::onFrame);
		while (!stopThread) {
			CanMessages toSend;
			{
				Poco::Mutex::ScopedLock l(m);
				toSend.swap(this->canList);
			}

			for (CanMessages::iterator msg = toSend.begin();
					msg != toSend.end(); msg++) {
				if (stopThread)
					break;
				CANFrame::Ptr frame = frameFromMessage(*msg);
				std::cout << std::endl;
				std::cout << "send: " << msg->toString() << std::endl;
				std::cout << std::endl;
				interface->sendFrame(frame);
			}

			if (stopThread)
				break;

		}
		interface->FrameReady -= Poco::delegate(this, &UsbChannel::onFrame);
		std::cout << "usb thread loop exit" << std::endl;
	} catch (Poco::Exception & e) {
		std::cerr << "net thread loop failed " << e.displayText() << std::endl;
	}

	/*
	 void NetChannel::processNotification(Poco::Notification::Ptr notification){
	 if (NetNtf::Ptr p = notification.cast<NetNtf>()) {
	 //LOG_DEBUG << "Raised Can message: " << p->message.toString() << LOG_END;
	 //this->MessageRetrieved.notify(this, p->message);
	 }
	 }
	 */
}
}
}
}
/* namespace TBS */
