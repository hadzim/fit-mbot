/*
 * RoboCanMessage.cpp
 *
 *  Created on: 4.3.2013
 *      Author: JV
 */

#include "TBS/Robo/RoboCan/Communicaton/RoboCanMessage.h"
#include <sstream>

namespace TBS {
	namespace Robo {
		namespace RoboCan {
			

				RoboCanMessage::RoboCanMessage(const CanMessage & canMessage) :
						canMessage(canMessage) {

				}

				Poco::UInt32 RoboCanMessage::getModule() const {
					return this->canMessage.canID;
				}
				void RoboCanMessage::setModule(const Poco::UInt32 & module) {
					this->canMessage.canID = module;
				}

				Poco::UInt8 RoboCanMessage::getNodeID() const {
					return this->canMessage.b0;
				}

				void RoboCanMessage::setNodeID(const Poco::UInt8 & n) {
					this->canMessage.b0 = n;
				}

				RoboCanMessage::eDataType RoboCanMessage::getDataType() const {
					return (RoboCanMessage::eDataType) this->canMessage.b1;
				}

				void RoboCanMessage::setDataType(const eDataType & type) {
					this->canMessage.b1 = type;
				}

				Poco::UInt8 RoboCanMessage::getCmd() const {
					return this->canMessage.b2;
				}
				void RoboCanMessage::setCmd(const Poco::UInt8 & cmd) {
					this->canMessage.b2 = cmd;
				}

				Poco::UInt8 RoboCanMessage::getChannel() const {
					return this->canMessage.b3;
				}
				void RoboCanMessage::setChannel(const Poco::UInt8 & ch) {
					this->canMessage.b3 = ch;
				}

				CanMessage RoboCanMessage::getCanMessage() const {
					return this->canMessage;
				}
				CanMessage & RoboCanMessage::getCanMessageRef() {
					return this->canMessage;
				}

				std::string RoboCanMessage::toString() {
					std::stringstream s;
					s << "MSG " << this->getModule() << " " << this->getNodeID() << " " << (int) this->getDataType() << " " << this->getCmd();
					return s.str();
				}

			/*
			 static bool areBothSameStatus(const RoboCanMessage & b1, const RoboCanMessage & b2) {
			 return StatusMessage.isStatus(b1.Cmd) && StatusMessage.isStatus(b2.Cmd) && b1.Module == b2.Module && b1.NodeID == b2.NodeID;
			 }*/

			
		} /* namespace RoboCan */
	}
}
