/*
 * InternalCanModule.cpp
 *
 *  Created on: 7.3.2013
 *      Author: JV
 */

#include "TBS/Robo/RoboCan/HW/InternalCanModule.h"
namespace TBS {
	namespace Robo {
		namespace RoboCan {
			

				InternalCanModule::InternalCanModule(std::string name, ICanNode::RawPtr node, int numberWithinModule) :
						ICanModule(name, node, numberWithinModule), myNode(node) {
				}

				InternalCanModule::~InternalCanModule() {

				}

				IChannel::Ptr InternalCanModule::getCommunicationChannel() const {
					return this->myNode->getCommunicationChannel();
				}
				TBS::NotificationWorker::Ptr InternalCanModule::getNotificationWorker() const {
					return this->myNode->getNotificationWorker();
				}

				CanMessage InternalCanModule::composeCommand(ICanModule::Command command, const RoboCanMessageData & data,
						ICanModule::Channel channel) const {
					RoboCanMessage message;

					message.setModule(this->getCanID());
					message.setNodeID(this->getNodeID());
					message.setChannel(channel);
					message.setCmd(command);

					data.writeToMessage(message);

					return message.getCanMessage();
				}

				CanMessage InternalCanModule::cmdStatus() const {
					return this->composeCommand((Command) CMD_GET_STATUS);
				}
				CanMessage InternalCanModule::cmdStart() const {
					return this->composeCommand((Command) CMD_START);
				}
				CanMessage InternalCanModule::cmdHalt() const {
					return this->composeCommand((Command) CMD_HALT);
				}
				CanMessage InternalCanModule::cmdRestart() const {
					return this->composeCommand((Command) CMD_RESTART);
				}
				CanMessage InternalCanModule::cmdStop() const {
					return this->composeCommand((Command) CMD_STOP);
				}
				CanMessage InternalCanModule::cmdGetError() const {
					return this->composeCommand((Command) CMD_GET_ERROR);
				}
				CanMessage InternalCanModule::cmdGetData() const {
					return this->composeCommand((Command) CMD_GET_DATA);
				}

			
		} /* namespace RoboCan */
	}
}
