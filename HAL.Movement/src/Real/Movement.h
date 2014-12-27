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
@brief     Header file
@authors   Jan Vana (<ivanajan@fit.vutbr.cz>)
@date      2010-2014
@note      This project was supported by project funds of the MV CR grant VG20102014024.

*/
#ifndef Movement_H_
#define Movement_H_
#include "HAL/API/Movement.h"
#include <Poco/Types.h>

namespace MBot {

class MovementImpl;

class Movement: public HAL::API::Movement::IMovement, public Poco::Runnable {
public:
	Movement(int port);
	virtual ~Movement();

	virtual void Move(const double & speedLeft, const double & speedRight);

	virtual void Stop();

	virtual void SetPosition(const int64_t & posLeft, const int64_t & posRight);

	virtual void GetStatus(double & speedLeft, double & speedRight,
			int64_t & posLeft, int64_t & posRight);


private:
	virtual void run();

	int port;

	Poco::SharedPtr<MovementImpl> impl;
	bool finish;

	double speedLeft;
	double speedRight;

	Poco::Int64 posLeft;
	Poco::Int64 posRight;

	Poco::Thread t;
	Poco::Mutex dataMutex;
	Poco::Mutex commandMutex;

};

} /* namespace MBot */
#endif /* Movement_H_ */
