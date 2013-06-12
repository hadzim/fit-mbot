/*
 * CanMessage.h
 *
 *  Created on: 4.3.2013
 *      Author: JV
 */

#ifndef RoboCanMESSAGE_H_
#define RoboCanMESSAGE_H_

#include <Poco/Types.h>
#include <string>
namespace TBS {
	namespace Robo {
		namespace RoboCan {

				class CanMessage {
					public:
						Poco::UInt32 canID;
						Poco::UInt8 length;

						Poco::UInt8 b0;
						Poco::UInt8 b1;
						Poco::UInt8 b2;
						Poco::UInt8 b3;
						Poco::UInt8 b4;
						Poco::UInt8 b5;
						Poco::UInt8 b6;
						Poco::UInt8 b7;

						CanMessage();

						std::string toString() const;
				};


		} /* namespace RoboCan */
	}
}
#endif /* RoboCanMESSAGE_H_ */
