/*
 * ModuleDataTask.cpp
 *
 *  Created on: 7.3.2013
 *      Author: JV
 */

#include "TBS/Robo/RoboCan/Task/ModuleDataTask.h"
#include "TBS/Robo/RoboCan/Communicaton/AckMessage.h"
#include "TBS/Robo/RoboCan/HW/InternalCanModule.h"
#include "TBS/Log.h"
namespace TBS {
	namespace Robo {
		namespace RoboCan {
			

				ModuleDataTask::ModuleDataTask(const InternalCanModule & module) :
						ModuleTask<DataMessage>(module.getName() + ":Data", module.getNotificationWorker(), module.getCommunicationChannel(),
								module.cmdGetData()), moduleCanId(module.getCanID()) {

				}
				ModuleDataTask::~ModuleDataTask() {

				}

				void ModuleDataTask::packetRetrieved(CanMessage & m) {

					if (m.canID != this->moduleCanId) {
						return;
					}
					std::cout << "DATA packet retrieved" << std::endl;
					try {
						RoboCanMessage message(m);
						if (AckMessage::isAckFail(message.getCmd())) {
							LNOTICE("Can") << "Module " << this->getName() << " data ack failed" << LE;
							this->failed("AckFail"); //setDone(this->msg.getReference());
							return;
						}

						if (DataMessage::isData(message.getCmd())) {
							try {
								if (msg.isEmpty()) {
									LTRACE("Can") << "Module " << this->getName() << " first data message" << LE;
									msg.set(DataMessage(message));
								} else {
									LTRACE("Can") << "Module " << this->getName() << " next data message" << LE;
									msg.getReference().addMessage(message);
								}

								if (msg.getReference().isComplete()) {
									LTRACE("Can") << "Module " << this->getName() << " complete data message" << LE;
									this->setDone(this->msg.getReference());
								}
							} catch (Poco::Exception & e) {
								LWARNING("Can") << "Module " << this->getName() << " data message failed " << e.message() << LE;
								this->failed(e.message());
							}
						}
					} catch (...) {

					}
				}

			
		} /* namespace RoboCan */
	}
}
