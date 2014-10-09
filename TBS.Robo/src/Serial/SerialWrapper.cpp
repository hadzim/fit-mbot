/*
 * SerialWrapper.cpp
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#include "TBS/Serial/SerialWrapper.h"
#include <Poco/Thread.h>
#include <iostream>
#include "lin/LinSerial.h"
#include "TBS/Log.h"
namespace TBS {
	namespace Serial {

		SerialWrapper::SerialWrapper(int port, int br) {
			std::cout << "serial wrapper port: " << port << std::endl;
			serial = new LinSerial(port, br);
		}

		SerialWrapper::~SerialWrapper() {
			delete serial;
		}

		void SerialWrapper::send(const VectorBuffer & buffer) {
			if (buffer.empty()) {
				throw Poco::Exception("Buffer to send is empty");
			}
			if (!serial->SendData((unsigned char *) &buffer[0], buffer.size())) {
				throw Poco::Exception("Sending failed");
			}
		}
		SerialWrapper::VectorBuffer SerialWrapper::receive() {

			SerialWrapper::VectorBuffer finalBuffer;
			const int limit = 100;
			unsigned char buffer[limit];
			int val = serial->ReadData(buffer, limit);
			if (val < 0) {
				throw Poco::Exception("Reading failed");
			}
			for (int i = 0; i < val; i++) {
				finalBuffer.push_back(buffer[i]);
			}
			return finalBuffer;
		}

		SerialWrapper::VectorBuffer SerialWrapper::receive(int waitTime, int length) {
			int slept = 0;

			SerialWrapper::VectorBuffer finalBuffer;

			while (slept < waitTime) {

				SerialWrapper::VectorBuffer tmpBuffer = receive();

				int sleepInterval = 2;
				if (tmpBuffer.empty()) {
					Poco::Thread::sleep(sleepInterval);
					slept += sleepInterval;
					continue;
				}

				finalBuffer.insert(finalBuffer.end(), tmpBuffer.begin(), tmpBuffer.end());

				if (finalBuffer.size() >= length)
					break;

			}
			return finalBuffer;
		}

		SerialWrapper::VectorBuffer SerialWrapper::receive(SerialWrapper::ListBuffer charSequence, int waitTime) {
			int slept = 0;

			SerialWrapper::VectorBuffer finalBuffer;

			while (slept < waitTime) {

				SerialWrapper::VectorBuffer tmpBuffer = receive();

				int sleepInterval = 2;
				if (tmpBuffer.empty()) {
					Poco::Thread::sleep(sleepInterval);
					slept += sleepInterval;
					continue;
				}

				finalBuffer.insert(finalBuffer.end(), tmpBuffer.begin(), tmpBuffer.end());

				//check sequence
				SerialWrapper::ListBuffer charSequenceCpy = charSequence;
				for (SerialWrapper::VectorBuffer::iterator i = finalBuffer.begin(); i != finalBuffer.end(); i++) {

					if (charSequenceCpy.empty()) {
						break;
					}
					if (*i == charSequenceCpy.front()) {
						charSequenceCpy.pop_front();
					}
				}
				if (charSequenceCpy.empty()) {
					break;
				} else {
					Poco::Thread::sleep(sleepInterval);
					slept += sleepInterval;
				}
			}
			return finalBuffer;
		}

	}
}
