/*
 * RoboCanMessageData.h
 *
 *  Created on: 4.3.2013
 *      Author: JV
 */

#ifndef ROBORoboCanMESSAGEDATA_H_
#define ROBORoboCanMESSAGEDATA_H_
#include "RoboCanMessage.h"

namespace TBS {
	namespace Robo {
		namespace RoboCan {

				class RoboCanMessageData {
					public:
						RoboCanMessageData();
						~RoboCanMessageData();

						void writeToMessage(RoboCanMessage & message) const;
						void readFromMessage(const RoboCanMessage & message);

						Poco::UInt8 getUCHAR() const;
						void setUCHAR(Poco::UInt8 value);

						Poco::Int8 getCHAR() const;
						void setCHAR(Poco::Int8 value);

						Poco::Int16 getSHORT() const;
						void setSHORT(Poco::Int16 value);

						Poco::UInt16 getUSHORT() const;
						void setUSHORT(Poco::UInt16 value);

						Poco::Int32 getLONG() const;
						void setLONG(Poco::Int32 value);

						Poco::UInt32 getULONG() const;
						void setULONG(Poco::UInt32 value);

						struct UShort2 {
							Poco::UInt16 short1;
							Poco::UInt16 short2;
						};

						UShort2 getUSHORT2() const;
						void setUSHORT2(UShort2 value);

						struct Short2 {
							Poco::Int16 short1;
							Poco::Int16 short2;
						};

						Short2 getSHORT2() const;
						void setSHORT2(Short2 value);

					private:
						void checkLength(int length) const;
						void checkType(RoboCanMessage::eDataType type) const;
						void reset();

					private:

						Poco::UInt8 b0;
						Poco::UInt8 b1;
						Poco::UInt8 b2;
						Poco::UInt8 b3;
						Poco::UInt8 length;
						RoboCanMessage::eDataType dataType;
				};

		}
	}
}

#endif /* ROBORoboCanMESSAGEDATA_H_ */
