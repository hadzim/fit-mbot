/*
 * AckMessage.h
 *
 *  Created on: 7.3.2013
 *      Author: JV
 */

#ifndef ASKMESSAGE_H_
#define ASKMESSAGE_H_
#include "RoboCanMessage.h"
namespace TBS {
	namespace Robo {
		namespace RoboCan {

				class AckMessage {
					public:

						enum eAcks {
							ACK_Ok = 128, ACK_Fail = 129, ACK_Finish = 130
						};

						AckMessage(const RoboCanMessage & m);
						virtual ~AckMessage();

						bool hasAcked();
						bool hasFinished();
						bool hasFailed();

						static bool isPureAck(Poco::UInt8 value);
						static bool isAck(Poco::UInt8 value);
						static bool isAckFail(Poco::UInt8 value);
						static bool isAckFinish(Poco::UInt8 value);

					private:
						RoboCanMessage message;
				};


		} /* namespace RoboCan */
	}
}
#endif /* ASKMESSAGE_H_ */
