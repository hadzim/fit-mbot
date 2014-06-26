/*
 * SerialWrapper2.h
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#ifdef _WIN32

#ifndef SerialWrapper2_H_
#define SerialWrapper2_H_
#include <vector>
#include <list>
#include "Serial.h"

namespace TBS {
	namespace Serial {

		class SerialWrapper2 {
			public:
				typedef std::vector<char> VectorBuffer;
				typedef std::list<char> ListBuffer;

				SerialWrapper2(int port, int br);
				~SerialWrapper2();

				void send(const VectorBuffer & buffer);
				VectorBuffer receive();
				VectorBuffer receive(int waitTime, int length);
				VectorBuffer receive(SerialWrapper2::ListBuffer charSequence, int waitTime);
			private:
				CSerial serial;
		};

	}
}
#endif /* SerialWrapper2_H_ */

#endif
