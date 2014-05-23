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
			

				ModuleCommandTask::ModuleCommandTask(std::string commandName, const InternalCanModule & module, const CanMessage & cmd) :
						ModuleTask<AckMessage>(module.getName() + ":Command:" + commandName, module.getNotificationWorker(), module.getCommunicationChannel(), cmd), moduleCanId(
								module.getCanID()) {

				}
				ModuleCommandTask::~ModuleCommandTask() {

				}

				void ModuleCommandTask::packetRetrieved(CanMessage & m) {
					if (m.canID != this->moduleCanId) {
						return;
					}

					try {

						RoboCanMessage message(m);



						if (AckMessage::isAck(message.getCmd())) {
							AckMessage ack(message);

							std::cout << "COMMAND ack retrieved: " << std::endl;

							if (ack.hasFailed()) {
								LNOTICE("Can") << "Module " << this->getName() << " ack Failed" << LOG_END;
								this->failed("AckFail");
							}
							if (ack.hasAcked()) {
								LNOTICE("Can") << "Module " << this->getName() << " ack ok" << LOG_END;
								this->notify<AckMessage>(Acked, ack);
							}
							if (ack.hasFinished()) {
								LNOTICE("Can") << "Module " << this->getName() << " ack finished" << LOG_END;
								this->setDone(ack);
							}
						}

					} catch (Poco::Exception & e) {
						LWARNING("Can") << "Module " << this->getName() << " error: " << e.displayText() << LOG_END;
					}catch (...) {
						LWARNING("Can") << "Module " << this->getName() << " error: ???" << LOG_END;
					}
				}

				ModuleCommandAnyAckTask::ModuleCommandAnyAckTask(std::string taskname, const InternalCanModule & module, const CanMessage & cmd) :
						ModuleTask<AckMessage>(module.getName() + ":AnyAckCommand:" + taskname, module.getNotificationWorker(), module.getCommunicationChannel(), cmd), moduleCanId(
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
								LNOTICE("Can") << "Module " << this->getName() << " ack ok" << LE;
								this->failed("AckFail");
							}
							if (ack.hasAcked()) {
								LTRACE("Can") << "Module " << this->getName() << " ack ok" << LE;
								this->setDone(ack);
							}
							if (ack.hasFinished()) {
								LTRACE("Can") << "Module " << this->getName() << " ack finished" << LE;
								this->setDone(ack);
							}
						}

					} catch (...) {

					}
				}

			
		} /* namespace RoboCan */
	}
}
