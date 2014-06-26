/*
 * LinSerial.h
 *
 *  Created on: 24.4.2014
 *      Author: JV
 */

#ifndef LINSERIAL_H_
#define LINSERIAL_H_

namespace TBS {
	namespace Serial {
		class LinSerial {
			public:
				LinSerial(int nPort = 2, int nBaud = 9600);
				virtual ~LinSerial();

				int ReadData(unsigned char * buffer, int bufferlen);
				int SendData(unsigned char *, int);
				//int ReadDataWaiting(void);
			private:
				int port;
		};

	}
}
#endif /* LINSERIAL_H_ */
