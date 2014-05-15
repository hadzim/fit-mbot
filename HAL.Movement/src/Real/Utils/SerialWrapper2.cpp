/*
 * SerialWrapper2.cpp
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#include "SerialWrapper2.h"
#include <Poco/Thread.h>
#include <iostream>
namespace MBot {

SerialWrapper2::SerialWrapper2(int port, int br) {
	if (!serial.Open(port, br)) {
		throw Poco::Exception("cannot open serial port");
	}
}

SerialWrapper2::~SerialWrapper2() {
	serial.Close();
}

void SerialWrapper2::send(const VectorBuffer & buffer) {
	if (buffer.empty()){
		throw Poco::Exception("Buffer to send is empty");
	}
	if (!serial.SendData(&buffer[0], buffer.size())){
		throw Poco::Exception("Sending failed");
	}
}
SerialWrapper2::VectorBuffer SerialWrapper2::receive() {
	SerialWrapper2::VectorBuffer finalBuffer;
	const int limit = 100;
	char buffer[limit];
	int val = serial.ReadData(buffer, limit);
	if (val < 0){
		throw Poco::Exception("Reading failed");
	}
	for (int i = 0; i < val; i++){
		finalBuffer.push_back(buffer[i]);
	}
	return finalBuffer;
}

SerialWrapper2::VectorBuffer SerialWrapper2::receive(int waitTime, int length) {
	int slept = 0;

	int sleepInterval = 2;
	while (serial.ReadDataWaiting() < length && slept < waitTime){
		Poco::Thread::sleep(sleepInterval);
		slept += sleepInterval;
	}
	return receive();
}

SerialWrapper2::VectorBuffer SerialWrapper2::receive(SerialWrapper2::ListBuffer charSequence, int waitTime) {
	int slept = 0;

	SerialWrapper2::VectorBuffer finalBuffer;

	while (slept < waitTime){

		int sleepInterval = 2;
		while (serial.ReadDataWaiting() == 0 && slept < waitTime){
			Poco::Thread::sleep(sleepInterval);
			slept += sleepInterval;
		}
		SerialWrapper2::VectorBuffer tmpBuffer = receive();
		finalBuffer.insert(finalBuffer.end(), tmpBuffer.begin(), tmpBuffer.end());

		//check sequence
		SerialWrapper2::ListBuffer charSequenceCpy = charSequence;
		for (SerialWrapper2::VectorBuffer::iterator i = finalBuffer.begin(); i != finalBuffer.end(); i++){

			if (charSequenceCpy.empty()){
				break;
			}
			if (*i == charSequenceCpy.front()){
				charSequenceCpy.pop_front();
			}
		}
		if (charSequenceCpy.empty()){
			break;
		} else {
			Poco::Thread::sleep(sleepInterval);
			slept += sleepInterval;
		}
	}
	return finalBuffer;
}


} /* namespace MBot */
