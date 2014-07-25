/*
 * ManipulatorModule.h
 *
 *  Created on: 22.7.2014
 *      Author: JV
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
