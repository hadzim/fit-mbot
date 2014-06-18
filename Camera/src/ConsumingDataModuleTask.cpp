/*
 * ConsumingModuleTask.cpp
 *
 *  Created on: 30.4.2014
 *      Author: JV
 */

#include "ConsumingDataModuleTask.h"
#include "TBS/Robo/RoboCan/Communicaton/DataMessage.h"

namespace TBS {
namespace Robo {
namespace RoboCan {

ConsumingDataModuleTask::ConsumingDataModuleTask(
		const InternalCanModule & module) :
		TBS::Task::Task(module.getName() + "::ConsumeData",
				module.getNotificationWorker()), channel(
				module.getCommunicationChannel()), canID(module.getCanID()) {
	std::cout << "consume construct" << std::endl;
	this->OuterActivation += Poco::delegate(this,
			&ConsumingDataModuleTask::onOuterActivation);
}

ConsumingDataModuleTask::~ConsumingDataModuleTask() {
	std::cout << "consume destruct" << std::endl;
	this->OuterActivation -= Poco::delegate(this,
			&ConsumingDataModuleTask::onOuterActivation);
}
void ConsumingDataModuleTask::onOuterActivation(TBS::Activation & a) {
	if (a == TBS::Activating) {
		channel->MessageRetrieved += Poco::delegate(this,
				&ConsumingDataModuleTask::packetRetrieved);
	} else {
		channel->MessageRetrieved -= Poco::delegate(this,
				&ConsumingDataModuleTask::packetRetrieved);
	}
}

void ConsumingDataModuleTask::packetRetrieved(CanMessage & m) {

	if (m.canID != this->canID) {
		return;
	}
	std::cout << "DATA packet retrieved" << std::endl;
	try {
		RoboCanMessage message(m);
		if (DataMessage::isData(message.getCmd())) {
			try {

				if (currentMessage.isEmpty()) {
					std::cout << "Module " << this->getName()
							<< " first data message" << std::endl;
					currentMessage.set(DataMessage(message));
				} else {
					std::cout << "Module " << this->getName()
							<< " next data message" << std::endl;
					currentMessage.ref().addMessage(message);
				}

				if (currentMessage.ref().isComplete()) {
					std::cout << "Module " << this->getName()
							<< " complete data message" << std::endl;

					std::cout << "val: " << currentMessage.ref().getData(0).getUSHORT2().short1 << " is error: " << currentMessage.ref().getData(0).getUSHORT2().short2 << std::endl;

					currentMessage.reset();
					//this->setDone(this->msg.getReference());
				}
			} catch (Poco::Exception & e) {
				LWARNING("Can")<< "Module " << this->getName()
					<< " data message failed " << e.message() << LE;
				currentMessage.reset();
				}
			}
		} catch (...) {

		}
	}}
	}
	} /* namespace MBot */
