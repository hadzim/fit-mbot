/*
 * ModuleDataTask.h
 *
 *  Created on: 7.3.2013
 *      Author: JV
 */

#ifndef MODULEDATATASK_H_
#define MODULEDATATASK_H_

#include "TBS/Robo/RoboCan/Communicaton/DataMessage.h"
#include "TBS/Robo/RoboCan/HW/ICanModule.h"
#include "ModuleTask.h"
#include "TBS/Robo/RoboCan/HW/InternalCanModule.h"
namespace TBS {
	namespace Robo {
		namespace RoboCan {

			class ModuleDataTask: public ModuleTask<DataMessage> {
				public:
					ModuleDataTask(const InternalCanModule & module);
					virtual ~ModuleDataTask();
				private:
					virtual void packetRetrieved(CanMessage & m);
					void onOuterActivation(TBS::Activation & a);

				private:
					TBS::Nullable<DataMessage> msg;
					Poco::UInt32 moduleCanId;
			};

		} /* namespace RoboCan */
	}
}
#endif /* MODULEDATATASK_H_ */
