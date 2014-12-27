//------------------------------------------------------------------------------
//
//  Project:   VG20102014024
//             Robot for search of human beings in crushes and avalanches
//
//             Brno University of Technology
//             Faculty of Information Technology
//
//------------------------------------------------------------------------------
//
//             This project was financially supported by project
//                  VG20102014024 funds provided by MV CR.
//
//------------------------------------------------------------------------------
/*!

@file
@brief     US server
@authors   Jan Vana (<ivanajan@fit.vutbr.cz>)
@date      2010-2014
@note      This project was supported by project funds of the MV CR grant VG20102014024.

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
	UltraSound(int port);
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

	int port;


	Poco::Thread t;
	Poco::Mutex dataMutex;


};

} /* namespace MBot */
#endif /* UltraSound_H_ */
