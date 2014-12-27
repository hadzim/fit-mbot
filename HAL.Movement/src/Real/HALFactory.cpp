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
@brief     Real implementation of movement module
@authors   Jan Vana (<ivanajan@fit.vutbr.cz>)
@date      2010-2014
@note      This project was supported by project funds of the MV CR grant VG20102014024.

*/
#include "HALFactory.h"
#include "Movement.h"

namespace MBot {

HALFactory::HALFactory(int port) : port(port) {

}

HALFactory::~HALFactory() {

}

HAL::API::Movement::IMovement::Ptr HALFactory::createMovement(){
	return new Movement(port);
}

} /* namespace MBot */
