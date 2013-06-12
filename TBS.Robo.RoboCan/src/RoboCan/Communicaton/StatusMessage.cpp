/*
 * StatusMessage.cpp
 *
 *  Created on: 4.3.2013
 *      Author: JV
 */

#include "TBS/Robo/RoboCan/Communicaton/StatusMessage.h"
#include "Poco/Exception.h"

namespace TBS {
	namespace Robo {
		namespace RoboCan {
			

				StatusMessage::StatusMessage(const RoboCanMessage & m) {
					if (!isStatus(m.getCmd())) {
						throw Poco::Exception("RoboCan: Status number out of range");
					}
					this->message = m;
				}

				StatusMessage::~StatusMessage() {

				}

				RoboCanMessage StatusMessage::getMessage() {
					return this->message;
				}

				StatusMessage::eState StatusMessage::getState() {
					Poco::UInt8 tmpstauts = this->message.getCmd();
					if (tmpstauts == (Poco::UInt8) STATUS_ERROR) {
						return STATUS_ERROR;
					}
					if (tmpstauts == (Poco::UInt8) STATUS_RUNNING) {
						return STATUS_RUNNING;
					}
					if (tmpstauts == (Poco::UInt8) STATUS_SLEEPING) {
						return STATUS_SLEEPING;
					}
					if (tmpstauts == (Poco::UInt8) STATUS_WAITING) {
						return STATUS_WAITING;
					}
					throw Poco::Exception("Wrong Status value");
				}

				std::string StatusMessage::toString() {
					Poco::UInt8 tmpstauts = this->message.getCmd();
					if (tmpstauts == (Poco::UInt8) STATUS_ERROR) {
						return "STATUS_ERROR";
					}
					if (tmpstauts == (Poco::UInt8) STATUS_RUNNING) {
						return "STATUS_RUNNING";
					}
					if (tmpstauts == (Poco::UInt8) STATUS_SLEEPING) {
						return "STATUS_SLEEPING";
					}
					if (tmpstauts == (Poco::UInt8) STATUS_WAITING) {
						return "STATUS_WAITING";
					}
					throw Poco::Exception("Wrong Status value");
				}

				bool StatusMessage::isStatus(const Poco::UInt8 & value) {
					int val = value;
					return val >= (int) STATUS_SLEEPING && val <= (int) STATUS_ERROR;
				}

			
		} /* namespace RoboCan */
	}
}
