/*
 * StatusMessage.h
 *
 *  Created on: 4.3.2013
 *      Author: JV
 */

#ifndef STATUSMESSAGE_H_
#define STATUSMESSAGE_H_
#include <string>
#include "RoboCanMessage.h"
namespace TBS {
	namespace Robo {
		namespace RoboCan {

				class StatusMessage {
					public:

						enum eState {
							STATUS_SLEEPING = 144, STATUS_WAITING = 145, STATUS_RUNNING = 146, STATUS_ERROR = 147
						};

						StatusMessage(const RoboCanMessage & message);
						~StatusMessage();

						RoboCanMessage getMessage();
						eState getState();

						std::string toString();

						static bool isStatus(const Poco::UInt8 & value);

					private:
						RoboCanMessage message;
				};


		} /* namespace RoboCan */
	}
}
#endif /* STATUSMESSAGE_H_ */
