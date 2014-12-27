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
#ifndef VIRTUALHALFACTORY_H_
#define VIRTUALHALFACTORY_H_
#include "IHALFactory.h"
#include "VirtualMovement.h"

namespace MBot {

class VirtualHALFactory: public IHALFactory {
public:
	VirtualHALFactory();
	virtual ~VirtualHALFactory();

	virtual HAL::API::Movement::IMovement::Ptr createMovement() {
		return new VirtualMovement();
	}
};

} /* namespace MBot */
#endif /* VIRTUALHALFACTORY_H_ */
