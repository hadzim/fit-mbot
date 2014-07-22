/*
 * HALFactory.h
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#ifndef HALFACTORY_H_
#define HALFACTORY_H_
#include "IHALFactory.h"
#include "TBS/NotificationWorker.h"
#include "TBS/Robo/RoboCan/Communication/UsbChannel.h"
namespace MBot {

class HALFactory : public IHALFactory {
public:
	HALFactory();
	virtual ~HALFactory();

	virtual HAL::API::BioRadar::IBioRadar::Ptr createBioRadar();
	virtual HAL::API::Camera::ICamera::Ptr createCamera();
	virtual HAL::API::Manipulator::IManipulator::Ptr createManipulator();
private:
	TBS::NotificationWorker::Ptr nw;
	TBS::Robo::RoboCan::UsbChannel::Ptr canChannel;
};

} /* namespace MBot */
#endif /* HALFACTORY_H_ */
