/*
 * SerialWrapper.cpp
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#include "SerialWrapper.h"
#include <Poco/Thread.h>
#include <iostream>
namespace MBot {

SerialWrapper::SerialWrapper(int port, int br) {
	if (!serial.Open(port, br)) {
		throw Poco::Exception("cannot open serial port");
	}
}

SerialWrapper::~SerialWrapper() {
	serial.Close();
}

void SerialWrapper::send(const VectorBuffer & buffer) {
	if (buffer.empty()){
		throw Poco::Exception("Buffer to send is empty");
	}
	if (!serial.SendData(&buffer[0], buffer.size())){
		throw Poco::Exception("Sending failed");
	}
}
SerialWrapper::VectorBuffer SerialWrapper::receive() {
	SerialWrapper::VectorBuffer finalBuffer;
	int limit = 100;
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

SerialWrapper::VectorBuffer SerialWrapper::receive(int waitTime, int length) {
	int slept = 0;

	int sleepInterval = 2;
	while (serial.ReadDataWaiting() < length && slept < waitTime){
		Poco::Thread::sleep(sleepInterval);
		slept += sleepInterval;
	}
	return receive();
}

} /* namespace MBot */
