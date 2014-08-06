/*
 * Module.cpp
 *
 *  Created on: 4.3.2013
 *      Author: JV
 */

#include "TBS/Robo/RoboCan/HW/CanModule.h"
namespace TBS {
	namespace Robo {
		namespace RoboCan {
			

				CanModule::CanModule(const Name & name, ICanNode::RawPtr node, int numberWithinModule) :
						ICanModule(name, node, numberWithinModule), internalModule(name, node, numberWithinModule) {

				}

				CanModule::~CanModule() {

				}

				const InternalCanModule & CanModule::getInternalModule() const {
					return this->internalModule;
				}
				/*
				 TBS::NotificationWorker::Ptr Module::nw() const{
				 return this->node->getNotificationWorker();
				 }
				 */

				ModuleStatusTask::Ptr CanModule::taskGetStatus() const {
					return new ModuleStatusTask(this->getInternalModule());
				}
				ModuleCommandAnyAckTask::Ptr CanModule::taskGetError() const {
					return new ModuleCommandAnyAckTask("GetError", this->getInternalModule(), this->getInternalModule().cmdGetError());
				}
				ModuleDataTask::Ptr CanModule::taskGetData() const {
					return new ModuleDataTask(this->getInternalModule());
				}
				ModuleCommandAnyAckTask::Ptr CanModule::taskStart() const {
					return new ModuleCommandAnyAckTask("Start", this->getInternalModule(), this->getInternalModule().cmdStart());
				}
				ModuleCommandAnyAckTask::Ptr CanModule::taskHalt() const {
					return new ModuleCommandAnyAckTask("Halt", this->getInternalModule(), this->getInternalModule().cmdHalt());
				}
				ModuleCommandAnyAckTask::Ptr CanModule::taskRestart() const {
					return new ModuleCommandAnyAckTask("Restart", this->getInternalModule(), this->getInternalModule().cmdRestart());
				}
				ModuleCommandAnyAckTask::Ptr CanModule::taskStop() const {
					return new ModuleCommandAnyAckTask("Stop", this->getInternalModule(), this->getInternalModule().cmdStop());
				}

				void CanModule::askData() const {
					this->getInternalModule().getCommunicationChannel()->sendCanMessage(this->getInternalModule().cmdGetData());
				}

			/*

			 void Module::cmdStatus() {
			 this->executeCommand((Command) CMD_GET_STATUS);
			 }
			 void Module::cmdStart() {
			 this->executeCommand((Command) CMD_START);
			 }
			 void Module::cmdHalt() {
			 this->executeCommand((Command) CMD_HALT);
			 }
			 void Module::cmdRestart() {
			 this->executeCommand((Command) CMD_RESTART);
			 }
			 void Module::cmdStop() {
			 this->executeCommand((Command) CMD_STOP);
			 }
			 void Module::cmdGetError() {
			 this->executeCommand((Command) CMD_GET_ERROR);
			 }
			 void Module::cmdGetData() {
			 this->executeCommand((Command) CMD_GET_DATA);
			 }*/
			/*
			 StatusMessage Module::getLastStatusMessage() const {
			 Poco::Mutex::ScopedLock l(mutex);
			 if (this->lastStatusMessage == NULL){
			 throw Poco::Exception("Last status message is empty");
			 }
			 return *this->lastStatusMessage;
			 }
			 void Module::setLastStatusMessage(StatusMessage & m){
			 {
			 Poco::Mutex::ScopedLock l(mutex);
			 delete lastStatusMessage;
			 this->lastStatusMessage = new StatusMessage(m);
			 }
			 //TODO raise event in separate thread with status message copy
			 }
			 */

			
		} /* namespace RoboCan */
	}
}
