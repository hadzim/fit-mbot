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
#ifndef MANIPULATORMODULE_H_
#define MANIPULATORMODULE_H_

#include "TBS/Serial/SerialWrapper.h"

namespace MBot {

	class ManipulatorModule {
		private:
			TBS::Serial::SerialWrapper w;
		public:
			ManipulatorModule(int portNumber);

			void enable();

			void disable();

			void unbreakMotor();

			void breakMotor();

			void go(int speed);
			void stop();
			void resetPosition();


	};


} /* namespace MBot */
#endif /* MANIPULATORMODULE_H_ */
