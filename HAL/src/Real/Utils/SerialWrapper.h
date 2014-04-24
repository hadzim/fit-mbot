/*
 * SerialWrapper.h
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#ifndef SERIALWRAPPER_H_
#define SERIALWRAPPER_H_

#include <vector>
#include <list>
#include "lin/LinSerial.h"

namespace MBot {

class SerialWrapper {
public:
	typedef std::vector <char> VectorBuffer;
	typedef std::list <char> ListBuffer;

	SerialWrapper(int port, int br);
	~SerialWrapper();

	void send(const VectorBuffer & buffer);
	VectorBuffer receive();
	VectorBuffer receive(int waitTime, int length);
	VectorBuffer receive(SerialWrapper::ListBuffer charSequence, int waitTime);
private:
	LinSerial serial;
};

} /* namespace MBot */
#endif /* SERIALWRAPPER_H_ */
