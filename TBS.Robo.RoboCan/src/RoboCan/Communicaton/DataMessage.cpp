/*
 * DataMessage.cpp
 *
 *  Created on: 6.3.2013
 *      Author: JV
 */

#include "TBS/Robo/RoboCan/Communicaton/DataMessage.h"
#include <iostream>
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
					size = getDataMessageSize(m.getCmd());
					messages.resize(size);
					messages.at(getIndex(m.getChannel())).set(m);
				}

				DataMessage::~DataMessage() {

				}

				void DataMessage::addMessage(const RoboCanMessage & m) {
					if (getDataMessageSize(m.getCmd()) != size) {
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

				int DataMessage::getSize() const{
					return this->size;
				}

				RoboCanMessageData DataMessage::getData(int channel) {
					//std::cout << "channel: " << channel << " size is " << messages.size() << std::endl;
					RoboCanMessageData mData;
					if (messages.size() <= channel || channel < 0){
						throw Poco::Exception("wrong channel index");
					}
					if (messages.at(channel).isEmpty()){
						throw Poco::Exception("data on channel are not filled");
					}
					mData.readFromMessage(messages.at(channel).getConstReference());
					//std::cout << "channel: " << channel << " size is " << messages.size() << "done" << std::endl;
					return mData;
				}

				bool DataMessage::isData(Poco::UInt8 value) {
					int val = value;
					return val >= from && val <= to;
				}
				int DataMessage::getDataMessageSize(Poco::UInt8 value) {
					return value - from + 1;
				}

				int DataMessage::getIndex(Poco::UInt8 value) {
					return value;
				}
			
		} /* namespace RoboCan */
	}
}
