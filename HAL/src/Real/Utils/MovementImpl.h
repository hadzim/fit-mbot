/*
 * MovementImpl.h
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#ifndef MOVEMENTIMPL_H_
#define MOVEMENTIMPL_H_
#include "SerialWrapper.h"
#include <Poco/Types.h>
#include "SerialWrapper2.h"



namespace MBot {

typedef SerialWrapper SerialLib;

class MovementImpl {
public:
	MovementImpl(int port, int br);
	virtual ~MovementImpl();

	void go(Poco::Int64 left, Poco::Int64 right);
	void stop();


	struct Data {
		Poco::Int64 left;
		Poco::Int64 right;
	};

	void setPosition(Data position);

	Data getPosition();
	Data getVelocity();

private:
	SerialLib serial;
};

} /* namespace MBot */
#endif /* MOVEMENTIMPL_H_ */
