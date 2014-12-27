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
@details   Details
@authors   Jan Vana (<ivanajan@fit.vutbr.cz>)
@date      2010-2014
@note      This project was supported by project funds of the MV CR grant VG20102014024.

*/
#ifndef HALFACTORY_H_
#define HALFACTORY_H_
#include "IHALFactory.h"
#include "TBS/NotificationWorker.h"
#include "TBS/Robo/RoboCan/Communication/UsbChannel.h"
namespace MBot {

class HALFactory : public IHALFactory {
public:
	HALFactory(int portMan1, int portMan2);
	virtual ~HALFactory();

	virtual HAL::API::BioRadar::IBioRadar::Ptr createBioRadar();
	virtual HAL::API::Camera::ICamera::Ptr createCamera();
	virtual HAL::API::Manipulator::IManipulator::Ptr createManipulator();
private:
	TBS::NotificationWorker::Ptr nw;
	TBS::Robo::RoboCan::UsbChannel::Ptr canChannel;
	int portMan1; int portMan2;
};

} /* namespace MBot */
#endif /* HALFACTORY_H_ */
