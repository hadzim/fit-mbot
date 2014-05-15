/*
 * VirtualMovement.h
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#ifndef VirtualMovement_H_
#define VirtualMovement_H_
#include "HAL/API/Movement.h"
#include <iostream>
namespace MBot {

class VirtualMovement: public HAL::API::Movement::IMovement {

public:
	VirtualMovement() :
			speedLeft(0.0), speedRight(0.0), posLeft(0), posRight(0) {
		std::cout << "CONSTRUCT called" << std::endl;
		this->updateSpeed(0, 0);
	}

	virtual ~VirtualMovement() {

	}

	virtual void Move(const double & speedLeft, const double & speedRight) {
		std::cout << "MOVE called" << std::endl;
		this->updateSpeed(speedLeft, speedRight);
	}

	virtual void Stop() {
		this->updateSpeed(0, 0);
	}

	virtual void SetPosition(const int64_t & posLeft,
				const int64_t & posRight){
		this->posLeft = posLeft;
		this->posRight = posRight;
		this->Stop();
	}


	virtual void GetStatus(double & speedLeft, double & speedRight, int64_t & posLeft, int64_t & posRight) {
		Poco::Mutex::ScopedLock l(m);
		speedLeft = this->speedLeft;
		speedRight = this->speedRight;
		posLeft = this->posLeft;
		posRight = this->posRight;
	}
private:
	void updateSpeed(double left, double right) {

		StatusChangedArg a;
		{
			Poco::Mutex::ScopedLock l(m);
			this->speedLeft = left;
			this->speedRight = right;

			this->posLeft += left;
			this->posRight += right;

			a.speedLeft = left;
			a.speedRight = right;

			a.posLeft = this->posLeft;
			a.posRight = this->posRight;

			std::cout << "Speed: (" << left << " " << right
					<< ")" << std::endl;
		}

		//this->StatusChanged.notify(this, a);
	}
private:
	Poco::Mutex m;
	double speedLeft;
	double speedRight;
	Poco::Int64 posLeft;
	Poco::Int64 posRight;
};

} /* namespace MBot */
#endif /* VirtualMovement_H_ */
