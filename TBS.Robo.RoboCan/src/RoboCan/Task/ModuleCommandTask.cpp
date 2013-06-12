/*
 * ModuleCommandTask.cpp
 *
 *  Created on: 6.3.2013
 *      Author: JV
 */

#include "TBS/Robo/RoboCan/Task/ModuleCommandTask.h"
#include "TBS/Log.h"
namespace TBS {
	namespace Robo {
		namespace RoboCan {
			

				ModuleCommandTask::ModuleCommandTask(const InternalCanModule & module, const CanMessage & cmd) :
						ModuleTask<AckMessage>(module.getName() + ":Command", module.getNotificationWorker(), module.getCommunicationChannel(), cmd), moduleCanId(
								module.getCanID()) {

				}
				ModuleCommandTask::~ModuleCommandTask() {

				}

				void ModuleCommandTask::packetRetrieved(CanMessage & m) {
					std::cout << "ModuleCommandTask::packate retrieved" << std::endl;
					if (m.canID != this->moduleCanId) {
						return;
					}
					try {
						RoboCanMessage message(m);

						if (AckMessage::isAck(message.getCmd())) {
							AckMessage ack(message);

							if (ack.hasFailed()) {
								LOG_NOTICE << "Module " << this->getName() << " ack Failed" << LOG_END;
								this->failed("AckFail");
							}
							if (ack.hasAcked()) {
								LOG_TRACE << "Module " << this->getName() << " ack ok" << LOG_END;
								this->notify<AckMessage>(Acked, ack);
							}
							if (ack.hasFinished()) {
								LOG_TRACE << "Module " << this->getName() << " ack finished" << LOG_END;
								this->setDone(ack);
							}
						}

					} catch (...) {

					}
				}

				ModuleCommandAnyAckTask::ModuleCommandAnyAckTask(const InternalCanModule & module, const CanMessage & cmd) :
						ModuleTask<AckMessage>(module.getName() + ":AnyAckCommand", module.getNotificationWorker(), module.getCommunicationChannel(), cmd), moduleCanId(
								module.getCanID()) {

				}
				ModuleCommandAnyAckTask::~ModuleCommandAnyAckTask() {

				}

				void ModuleCommandAnyAckTask::packetRetrieved(CanMessage & m) {
					if (m.canID != this->moduleCanId) {
						return;
					}
					try {
						RoboCanMessage message(m);

						if (AckMessage::isAck(message.getCmd())) {
							AckMessage ack(message);

							if (ack.hasFailed()) {
								LOG_NOTICE << "Module " << this->getName() << " ack ok" << LOG_END;
								this->failed("AckFail");
							}
							if (ack.hasAcked()) {
								LOG_TRACE << "Module " << this->getName() << " ack ok" << LOG_END;
								this->setDone(ack);
							}
							if (ack.hasFinished()) {
								LOG_TRACE << "Module " << this->getName() << " ack finished" << LOG_END;
								this->setDone(ack);
							}
						}

					} catch (...) {

					}
				}

			
		} /* namespace RoboCan */
	}
}
