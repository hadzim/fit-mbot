/*
 * UltraSound.h
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#ifndef UltraSound_H_
#define UltraSound_H_
#include <Poco/SharedPtr.h>
#include "HAL/API/UltraSound.h"
#include <Poco/Types.h>
#include <Real/UltraSoundModule.h>

namespace MBot {


class UltraSound: public HAL::API::UltraSound::IUltraSound, public Poco::Runnable {
public:
	UltraSound();
	virtual ~UltraSound();

	virtual void Reconnect() ;

	virtual void GetStatus(HAL::API::UltraSound::TouchSensors & frontSensors, HAL::API::UltraSound::TouchSensors & backSensors, bool & isValid) ;

private:
	virtual void run();

	bool finish;

	bool reconnect;
	bool isDataValid;

	int frontLeft;
	int frontRight;

	int backLeft;
	int backRight;



	Poco::Thread t;
	Poco::Mutex dataMutex;


};

} /* namespace MBot */
#endif /* UltraSound_H_ */
