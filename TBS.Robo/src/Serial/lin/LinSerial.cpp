/*
 * LinSerial.cpp
 *
 *  Created on: 24.4.2014
 *      Author: JV
 */

#include "LinSerial.h"
#include "rs232.h"
#include "Poco/Exception.h"

namespace TBS {
	namespace Serial {

		LinSerial::LinSerial(int nPort, int nBaud) :
				port(nPort) {
#ifdef _WIN32
			port -= 1;
#else
			port = 16; //dev/ttyUSB0
#endif
			if (RS232_OpenComport(port, nBaud)) {
				throw Poco::Exception("cannot open serial port");
			}
		}

		LinSerial::~LinSerial() {
			RS232_CloseComport(port);
		}

		int LinSerial::ReadData(unsigned char * buffer, int bufferlen) {
			return RS232_PollComport(port, buffer, bufferlen);
		}

		int LinSerial::SendData(unsigned char * buffer, int length) {
			int val = RS232_SendBuf(port, buffer, length);
			if (val == -1) {
				throw Poco::Exception("cannot send data");
			}
			return val;
		}

//int LinSerial::ReadDataWaiting(void) {
//}

	}
}
