/*
 * ModuleStatusTask.h
 *
 *  Created on: 6.3.2013
 *      Author: JV
 */

#ifndef MODULESTATUSTASK_H_
#define MODULESTATUSTASK_H_

#include "TBS/Robo/RoboCan/Communicaton/StatusMessage.h"
#include "TBS/Task/InputOutputTask.h"

#include "TBS/Robo/RoboCan/HW/ICanModule.h"
#include "TBS/Robo/RoboCan/Task/ModuleTask.h"
#include "TBS/Robo/RoboCan/HW/InternalCanModule.h"
namespace TBS {
	namespace Robo {
		namespace RoboCan {

			class ModuleStatusTask: public ModuleTask<StatusMessage> {
				public:
					ModuleStatusTask(const InternalCanModule & module);
					virtual ~ModuleStatusTask();
				protected:
					virtual void packetRetrieved(CanMessage & m);
				private:
					Poco::UInt32 moduleCanId;
			};

		} /* namespace RoboCan */
	}
}
#endif /* MODULESTATUSTASK_H_ */
