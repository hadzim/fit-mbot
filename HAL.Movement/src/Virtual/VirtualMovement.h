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
#ifndef VirtualMovement_H_
#define VirtualMovement_H_
#include "HAL/API/Movement.h"
#include <iostream>
namespace MBot {

class VirtualMovement: public HAL::API::Movement::IMovement,
		public Poco::Runnable {

public:
	VirtualMovement() :
			t("bgmovement"), finished(false), speedLeft(0.0), speedRight(0.0), posLeft(
					0), posRight(0) {

		this->t.start(*this);

		std::cout << "CONSTRUCT called" << std::endl;
		this->updateSpeed(0, 0);
	}

	virtual ~VirtualMovement() {

	}

	virtual void Move(const double & speedLeft, const double & speedRight) {
		std::cout << "MOVE called" << std::endl;

		this->updateSpeed(speedLeft, speedRight);
		Poco::Thread::sleep(200);
	}

	virtual void Stop() {
		this->updateSpeed(0, 0);
	}

	virtual void SetPosition(const int64_t & posLeft,
			const int64_t & posRight) {
		this->posLeft = posLeft;
		this->posRight = posRight;
		this->Stop();
	}

	virtual void GetStatus(double & speedLeft, double & speedRight,
			int64_t & posLeft, int64_t & posRight) {
		Poco::Mutex::ScopedLock l(m);
		speedLeft = this->speedLeft;
		speedRight = this->speedRight;
		posLeft = this->posLeft;
		posRight = this->posRight;
	}

	virtual void run() {
		while (!finished) {
			StatusChangedArg a;
			{
				Poco::Mutex::ScopedLock l(m);

				a.speedLeft = this->speedLeft;
				a.speedRight = this->speedRight;

				a.posLeft = this->posLeft;
				a.posRight = this->posRight;

				std::cout << "Ntf: (" << this->speedLeft << " " << this->speedRight << ") odo: " << this->posLeft << " " << this->posRight << std::endl;
			}

			this->StatusChanged.notify(this, a);
			Poco::Thread::sleep(501);
		}
	}

private:
	void updateSpeed(double left, double right) {

		{
			Poco::Mutex::ScopedLock l(m);
			this->speedLeft = left;
			this->speedRight = right;

			this->posLeft += left * 10;
			this->posRight += right * 10;

		}
		std::cout << "Speed: (" << left << " " << right << ") odo: " << this->posLeft << " " << this->posRight << std::endl;
	}
private:

	Poco::Thread t;
	bool finished;
	Poco::Mutex m;
	double speedLeft;
	double speedRight;
	Poco::Int64 posLeft;
	Poco::Int64 posRight;
};

} /* namespace MBot */
#endif /* VirtualMovement_H_ */
