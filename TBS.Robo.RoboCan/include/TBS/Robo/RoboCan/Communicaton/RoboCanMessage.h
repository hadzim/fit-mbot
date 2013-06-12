/*
 * RoboCanMessage.h
 *
 *  Created on: 4.3.2013
 *      Author: JV
 */

#ifndef RoboCanMessage_H_
#define RoboCanMessage_H_
#include "CanMessage.h"
#include <string>

namespace TBS {
	namespace Robo {
		namespace RoboCan {

				class RoboCanMessage {
					public:

						enum eDataType {
							DT_NODATA = 0,
							DT_ERROR = 1,
							DT_FLOAT = 2,
							DT_LONG = 3,
							DT_ULONG = 4,
							DT_BLONG = 5,
							DT_SHORT = 6,
							DT_USHORT = 7,
							DT_BSHORT = 8,
							DT_CHAR = 9,
							DT_UCHAR = 10,
							DT_BCHAR = 11,
							DT_SHORT2 = 12,
							DT_USHORT2 = 13,
							DT_BSHORT2 = 14,
							DT_CHAR4 = 15,
							DT_UCHAR4 = 16,
							DT_BCHAR4 = 17,
							DT_CHAR2 = 18,
							DT_UCHAR2 = 19,
							DT_BCHAR2 = 20,
							DT_MEMID = 21,
							DT_CHKSUM = 22,
							DT_ACHAR = 23,
							DT_ACHAR2 = 24,
							DT_ACHAR4 = 25,
							DT_CHAR3 = 26,
							DT_UCHAR3 = 27,
							DT_BCHAR3 = 28,
							DT_ACHAR3 = 29,
							DT_DOUBLEH = 30,
							DT_DOUBLEL = 31,
							DT_XXX = 100
						};

						RoboCanMessage(const CanMessage & canMessage = CanMessage());

						Poco::UInt32 getModule() const;
						void setModule(const Poco::UInt32 & module);

						Poco::UInt8 getNodeID() const;
						void setNodeID(const Poco::UInt8 & n);

						eDataType getDataType() const;
						void setDataType(const eDataType & type);

						Poco::UInt8 getCmd() const;
						void setCmd(const Poco::UInt8 & cmd);

						Poco::UInt8 getChannel() const;
						void setChannel(const Poco::UInt8 & ch);

						//static bool areBothSameStatus(const RoboCanMessage & b1, const RoboCanMessage & b2);

						CanMessage getCanMessage() const;
						CanMessage & getCanMessageRef();

						std::string toString();

					private:
						CanMessage canMessage;
				};


		} /* namespace RoboCan */
	}
}
#endif /* RoboCanMessage_H_ */
