/*
 * ModuleStatusTask.cpp
 *
 *  Created on: 6.3.2013
 *      Author: JV
 */

#include "TBS/Robo/RoboCan/Task/ModuleStatusTask.h"
#include "TBS/Log.h"
namespace TBS {
	namespace Robo {
		namespace RoboCan {
			

				ModuleStatusTask::ModuleStatusTask(const InternalCanModule & module) :
						ModuleTask<StatusMessage>(module.getName() + ":Status", module.getNotificationWorker(), module.getCommunicationChannel(),
								module.cmdStatus()), moduleCanId(module.getCanID()) {

				}
				ModuleStatusTask::~ModuleStatusTask() {

				}

				void ModuleStatusTask::packetRetrieved(CanMessage & m) {

					if (m.canID != this->moduleCanId) {
						return;
					}
					std::cout << "STATUS packet retrieved" << std::endl;
					try {
						RoboCanMessage message(m);
						StatusMessage s(message);
						LTRACE("Can") << "Module " << this->getName() << " status retrieved " << s.toString() << LOG_END;

						this->setDone(s);
					} catch (...) {

					}
				}

			
		} /* namespace RoboCan */
	}
}
