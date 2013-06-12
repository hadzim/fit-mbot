/*
 * DataMessage.h
 *
 *  Created on: 6.3.2013
 *      Author: JV
 */

#ifndef DATAMESSAGE_H_
#define DATAMESSAGE_H_
#include "TBS/Nullable.h"
#include "RoboCanMessage.h"
#include "TBS/Robo/RoboCan/Communicaton/RoboCanMessageData.h"
#include <vector>
namespace TBS {
	namespace Robo {
		namespace RoboCan {

				class DataMessage {
					public:
						typedef std::vector<TBS::Nullable<RoboCanMessage> > Messages;
						DataMessage();
						DataMessage(const RoboCanMessage & m);

						~DataMessage();

						bool getFailed() const;
						bool isComplete() const;
						void addMessage(const RoboCanMessage & m);

						RoboCanMessageData getData(int channel);

						static bool isData(Poco::UInt8 value);
						static int getSize(Poco::UInt8 value);
					private:
						static int getIndex(Poco::UInt8 value);
					private:
						static const Poco::UInt8 from = 0xA0;
						static const Poco::UInt8 to = 0xAF;

						int size;
						bool failed;
						Messages messages;
				};


		} /* namespace RoboCan */
	}
}
#endif /* DATAMESSAGE_H_ */
