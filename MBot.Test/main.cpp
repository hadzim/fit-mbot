/*
 * main.cpp
 *
 *  Created on: 19.2.2014
 *      Author: JV
 */

#include <iostream>
#include "Serial.h"
#include <Poco/Thread.h>

int main(int argc, char **argv) {
	CSerial serial;
	if (serial.Open(3, 19200)) {
		std::cout << "Port opened successfully" << std::endl;

		char data[8];
		memset(data, 0, 8);

		 int nBytesSent = serial.SendData(data, 8);
		 std::cout << "bytes sent: " << nBytesSent << std::endl;

		 Poco::Thread::sleep(100);

		  char* lpBuffer = new char[500];
		  int nBytesRead = serial.ReadData(lpBuffer, 500);


		  std::cout << "bytes read: " << nBytesRead << std::endl;
		  for (int i = 0; i < nBytesRead; i++){
			  std::cout << i << ") " << (int)lpBuffer[i] << std::endl;
		  }

		  delete []lpBuffer;

	} else {
		std::cout << "Failed to open port!" << std::endl;
	}




	return 0;

}
