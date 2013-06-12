/*
 * DummyChannel.cpp
 *
 *  Created on: 7.3.2013
 *      Author: JV
 */

#include "DummyChannel.h"
#include <iostream>
#include "TBS/Log.h"
DummyChannel::DummyChannel() :
		TBS::NotificationBasedRunnable("Dummy") {

}

DummyChannel::~DummyChannel() {
	this->stop();
}
void DummyChannel::processNotification(Poco::Notification::Ptr notification) {
	if (Ntf::Ptr p = notification.cast<Ntf>()) {
		LOG_DEBUG << "Raised Can message: " << p->message.toString() << LOG_END;
		this->MessageRetrieved.notify(this, p->message);
	}
}
void DummyChannel::sendCanMessage(const TBS::Robo::RoboCan::CanMessage & canMessage) {
	LOG_DEBUG << "Send Can message: " << canMessage.toString() << LOG_END;
	Ntf::Ptr ntf = new Ntf();
	ntf->message = canMessage;
	this->enqueueNotification(ntf);
}

