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
					std::cout << "ModuleDataTask::packate retrieved" << std::endl;
					if (m.canID != this->moduleCanId) {
						return;
					}
					try {
						RoboCanMessage message(m);
						if (AckMessage::isAckFail(message.getCmd())) {
							LOG_NOTICE << "Module " << this->getName() << " data ack failed" << LOG_END;
							this->failed("AckFail"); //setDone(this->msg.getReference());
							return;
						}

						if (DataMessage::isData(message.getCmd())) {
							try {
								if (msg.isEmpty()) {
									LOG_TRACE << "Module " << this->getName() << " first data message" << LOG_END;
									msg.set(DataMessage(message));
								} else {
									LOG_TRACE << "Module " << this->getName() << " next data message" << LOG_END;
									msg.getReference().addMessage(message);
								}

								if (msg.getReference().isComplete()) {
									LOG_TRACE << "Module " << this->getName() << " complete data message" << LOG_END;
									this->setDone(this->msg.getReference());
								}
							} catch (Poco::Exception & e) {
								LOG_WARNING << "Module " << this->getName() << " data message failed " << e.message() << LOG_END;
								this->failed(e.message());
							}
						}
					} catch (...) {

					}
				}

			
		} /* namespace RoboCan */
	}
}
