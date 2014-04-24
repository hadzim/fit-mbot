/*
 * SerialWrapper.h
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#ifndef SERIALWRAPPER_H_
#define SERIALWRAPPER_H_
#include "Serial.h"
#include <vector>

namespace MBot {

class SerialWrapper {
public:
	typedef std::vector <char> VectorBuffer;

	SerialWrapper(int port, int br);
	~SerialWrapper();

	void send(const VectorBuffer & buffer);
	VectorBuffer receive();
	VectorBuffer receive(int waitTime, int length);
private:
	CSerial serial;
};

} /* namespace MBot */
#endif /* SERIALWRAPPER_H_ */
