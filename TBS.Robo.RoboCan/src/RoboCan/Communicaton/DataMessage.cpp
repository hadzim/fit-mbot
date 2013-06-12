/*
 * DataMessage.cpp
 *
 *  Created on: 6.3.2013
 *      Author: JV
 */

#include "TBS/Robo/RoboCan/Communicaton/DataMessage.h"

namespace TBS {
	namespace Robo {
		namespace RoboCan {
			

				DataMessage::DataMessage() :
						size(0), failed(true) {
				}

				DataMessage::DataMessage(const RoboCanMessage & m) {
					failed = false;
					if (!isData(m.getCmd())) {
						throw Poco::Exception("Data Message out of range");
					}
					size = getSize(m.getCmd());
					messages.resize(size);
					messages.at(getIndex(m.getChannel())).set(m);
				}

				DataMessage::~DataMessage() {

				}

				void DataMessage::addMessage(const RoboCanMessage & m) {
					if (getSize(m.getCmd()) != size) {
						throw Poco::Exception("Data size missmatch");
					}
					if (messages[getIndex(m.getChannel())].isSet()) {
						throw Poco::Exception("Data already there");
					}
					messages[getIndex(m.getChannel())].set(m);
				}

				bool DataMessage::getFailed() const {
					return this->failed;
				}

				bool DataMessage::isComplete() const {
					for (int i = 0; i < size; i++) {
						if (messages[i].isEmpty()) {
							return false;
						}
					}
					return true;
				}

				RoboCanMessageData DataMessage::getData(int channel) {
					RoboCanMessageData mData;
					mData.readFromMessage(messages.at(channel).getConstReference());
					return mData;
				}

				bool DataMessage::isData(Poco::UInt8 value) {
					int val = value;
					return val >= from && val <= to;
				}
				int DataMessage::getSize(Poco::UInt8 value) {
					return value - from + 1;
				}

				int DataMessage::getIndex(Poco::UInt8 value) {
					return value;
				}
			
		} /* namespace RoboCan */
	}
}
