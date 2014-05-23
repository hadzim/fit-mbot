/*
 * NetChannel.cpp
 *
 *  Created on: 28.3.2013
 *      Author: JV
 */


#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"


#include <iostream>
#include "TBS/Robo/RoboCan/Communication/NetChannel.h"
#include "TBS/Robo/RoboCan/Communication/NetClient.h"

namespace TBS {
namespace Robo {
namespace RoboCan {

static TBS::Robo::RoboCan::CanMessage messageFromFrame(CanFrame frame) {
	TBS::Robo::RoboCan::CanMessage message;

	message.canID = frame.id;
	message.length = frame.dlc;

	message.b0 = frame.data[0];
	message.b1 = frame.data[1];
	message.b2 = frame.data[2];
	message.b3 = frame.data[3];
	message.b4 = frame.data[4];
	message.b5 = frame.data[5];
	message.b6 = frame.data[6];
	message.b7 = frame.data[7];

	return message;
}

static CanFrame frameFromMessage(TBS::Robo::RoboCan::CanMessage msg) {
	CanFrame sendframe;
	sendframe.id = msg.canID;

	sendframe.rtr = 0;
	sendframe.dlc = msg.length;

	sendframe.data[0] = msg.b0;
	sendframe.data[1] = msg.b1;
	sendframe.data[2] = msg.b2;
	sendframe.data[3] = msg.b3;
	sendframe.data[4] = msg.b4;
	sendframe.data[5] = msg.b5;
	sendframe.data[6] = msg.b6;
	sendframe.data[7] = msg.b7;

	return sendframe;
}

NetChannel::NetChannel() :
		thread("Net"), stopThread(false) {
	std::cout << "net channel construct" << std::endl;
	thread.start(*this);
	std::cout << "net channel construct done" << std::endl;
}

NetChannel::~NetChannel() {
	std::cout << "NetChannel destruct" << std::endl;
	stopThread = true;
	thread.join();
	std::cout << "NetChannel destructed" << std::endl;
}

void NetChannel::sendCanMessage(
		const TBS::Robo::RoboCan::CanMessage & canMessage) {
	Poco::Mutex::ScopedLock l(m);
	canList.push_back(canMessage);
}

void NetChannel::run() {
	try {
		std::cout << "start bg" << std::endl;
		NetClient client("192.168.0.8", 4411);

		while (!stopThread) {
			std::cout << "net" << std::endl;
			CanMessages toSend;
			{
				Poco::Mutex::ScopedLock l(m);
				toSend.swap(this->canList);
			}

			CanFrame::Queue transmit;
			for (CanMessages::iterator msg = toSend.begin();
					msg != toSend.end(); msg++) {
				if (stopThread)
					break;
				CanFrame frame = frameFromMessage(*msg);

				transmit.push_back(frame);
			}
			client.send(transmit);

			if (stopThread)
				break;

			CanFrame::Queue received;
			client.receive(received);

			for (CanFrame::Queue::iterator i = received.begin();
					i != received.end(); i++) {

				TBS::Robo::RoboCan::CanMessage message = messageFromFrame(*i);

				this->MessageRetrieved.notify(this, message);
			}

		}
		std::cout << "net thread loop exit" << std::endl;
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
