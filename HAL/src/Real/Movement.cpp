/*
 * Movement.cpp
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#include "Movement.h"
#include "Real/Utils/MovementImpl.h"
#include <iostream>

namespace MBot {

//slow is 50000
//max is 200 000
const double MAXSPEED = 800000;

Poco::Int64 relativeSpeedToAbsolute(double speed){
	if (speed > 1) speed = 1;
	if (speed < -1) speed = -1;
	return speed * MAXSPEED;
}
double absoluteSpeedToRelative(Poco::Int64 speed){
	return speed * 1.0 / MAXSPEED;
}

Movement::Movement() : finish(false), speedLeft(0), speedRight(0), posLeft(0), posRight(0) {
	impl = new MovementImpl(3, 9600);
	t.start(*this);
}

Movement::~Movement() {
	finish = true;
	t.join();
	impl = NULL;
}


void Movement::Move(const double & speedLeft, const double & speedRight) {

	Poco::Int64 sl = relativeSpeedToAbsolute(speedLeft);
	Poco::Int64 sr = relativeSpeedToAbsolute(speedRight);
	Poco::Mutex::ScopedLock l(commandMutex);
	impl->go(sl,sr);
}

void Movement::Stop() {
	Poco::Mutex::ScopedLock l(commandMutex);
	impl->stop();
}

void Movement::SetPosition(const int64_t & posLeft, const int64_t & posRight){
	Poco::Mutex::ScopedLock l(commandMutex);
	MovementImpl::Data data;
	data.left = -posLeft;
	data.right = posRight;
	impl->setPosition(data);
}

void Movement::GetStatus(double & speedLeft, double & speedRight,
		int64_t & posLeft, int64_t & posRight){
		Poco::Mutex::ScopedLock l(dataMutex);
		speedLeft = this->speedLeft;
		speedRight = this->speedRight;
		posLeft = this->posLeft;
		posRight = this->posRight;
}


void Movement::run(){

	while (!this->finish){

		try {
			MovementImpl::Data pos;
			MovementImpl::Data speed;
			{
				Poco::Mutex::ScopedLock l(commandMutex);
				pos = impl->getPosition();
				speed = impl->getVelocity();
			}
			{
				Poco::Mutex::ScopedLock l(dataMutex);
				this->posLeft = -pos.left;
				this->posRight = pos.right;

				this->speedLeft = -absoluteSpeedToRelative(speed.left);
				if (this->speedLeft < 0 && this->speedLeft > -0.00001) this->speedLeft = 0;
				this->speedRight = absoluteSpeedToRelative(speed.right);
			}
			{
				StatusChangedArg a;
				a.speedLeft = this->speedLeft;
				a.speedRight = this->speedRight;
				a.posLeft = this->posLeft;
				a.posRight = this->posRight;
				this->StatusChanged.notify(this, a);
			}
		} catch (Poco::Exception & e){
			std::cerr << "EXC: " << e.displayText() << std::endl;
		} catch (std::exception & e){
			std::cerr << "EXC: " << e.what() << std::endl;
		} catch (...){
			std::cerr << "EXC: ?" << std::endl;
		}

		Poco::Thread::sleep(100);
	}
}

} /* namespace MBot */
