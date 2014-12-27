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
#ifndef HALFACTORY_H_
#define HALFACTORY_H_
#include "IHALFactory.h"

namespace MBot {

class HALFactory : public IHALFactory {
public:
	HALFactory(int port);
	virtual ~HALFactory();

	virtual HAL::API::Movement::IMovement::Ptr createMovement();
private:
	int port;
};

} /* namespace MBot */
#endif /* HALFACTORY_H_ */
