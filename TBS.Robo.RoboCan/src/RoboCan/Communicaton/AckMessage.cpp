/*
 * AckMessage.cpp
 *
 *  Created on: 7.3.2013
 *      Author: JV
 */

#include "TBS/Robo/RoboCan/Communicaton/AckMessage.h"
#include "Poco/Exception.h"
namespace TBS {
	namespace Robo {
		namespace RoboCan {

				AckMessage::AckMessage(const RoboCanMessage & m) :
						message(m) {
					if (!isAck(message.getCmd())) {
						throw Poco::Exception("Ack cmd out of range");
					}

				}

				AckMessage::~AckMessage() {

				}

				bool AckMessage::hasAcked() {
					return message.getCmd() == (Poco::UInt8) ACK_Ok;
				}
				bool AckMessage::hasFinished() {
					return message.getCmd() == (Poco::UInt8) ACK_Finish;
				}
				bool AckMessage::hasFailed() {
					return message.getCmd() == (Poco::UInt8) ACK_Fail;
				}

				bool AckMessage::isPureAck(Poco::UInt8 value) {
					return value >= (Poco::UInt8) ACK_Ok && value <= (Poco::UInt8) ACK_Fail;
				}

				bool AckMessage::isAck(Poco::UInt8 value) {
					return value >= (Poco::UInt8) ACK_Ok && value <= (Poco::UInt8) ACK_Finish;
				}

				bool AckMessage::isAckFail(Poco::UInt8 value) {
					return value == (Poco::UInt8) ACK_Fail;
				}
				bool AckMessage::isAckFinish(Poco::UInt8 value) {
					return value == (Poco::UInt8) ACK_Finish;
				}


		} /* namespace RoboCan */
	}
}
