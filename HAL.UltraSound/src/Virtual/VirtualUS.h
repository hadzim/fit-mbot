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
@brief     Virtual server
@authors   Jan Vana (<ivanajan@fit.vutbr.cz>)
@date      2010-2014
@note      This project was supported by project funds of the MV CR grant VG20102014024.

*/
#ifndef VirtualUS_H_
#define VirtualUS_H_
#include "HAL/API/Movement.h"
#include <iostream>

#include "HAL/API/UltraSound.h"
namespace MBot {

class VirtualUS: public HAL::API::UltraSound::IUltraSound {

public:
	VirtualUS() :
			val(50), en(false) {

	}

	virtual ~VirtualUS() {

	}

	virtual void Reconnect() {
		en = true;
	}

	virtual void GetStatus(HAL::API::UltraSound::TouchSensors & frontSensors,
			HAL::API::UltraSound::TouchSensors & backSensors, bool & isValid) {

		if (en) {

			frontSensors.left.distance = val + 1;
			frontSensors.right.distance = val - 1;

			backSensors.left.distance = val + 2;
			backSensors.right.distance = val - 2;

			isValid = true;

			val++;
			if (val > 150) {
				val = 30;
			}

		} else {
			frontSensors.left.distance = -1;
			frontSensors.right.distance = -1;

			backSensors.left.distance = -1;
			backSensors.right.distance = -1;

			isValid = false;
		}
	}

private:
	bool en;
	int val;

};

} /* namespace MBot */
#endif /* VirtualUS_H_ */
