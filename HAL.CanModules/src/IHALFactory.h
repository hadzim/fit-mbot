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
#ifndef FACTORIES_H_
#define FACTORIES_H_

#include "ObjectFactory.h"
#include <Poco/SharedPtr.h>
#include "HAL/API/BioRadar.h"
#include "HAL/API/Camera.h"
#include "HAL/API/Manipulator.h"

namespace MBot {

class IHALFactory {
public:
	typedef Poco::SharedPtr <IHALFactory> Ptr;
	virtual ~IHALFactory() {
	}
	virtual HAL::API::BioRadar::IBioRadar::Ptr createBioRadar() = 0;
	virtual HAL::API::Camera::ICamera::Ptr createCamera() = 0;

	virtual HAL::API::Manipulator::IManipulator::Ptr createManipulator() = 0;


};

} /* namespace MBot */
#endif /* FACTORIES_H_ */
