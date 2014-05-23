/*
 * CameraModules.h
 *
 *  Created on: 15.5.2014
 *      Author: JV
 */

#ifndef CameraMODULES_H_
#define CameraMODULES_H_
#include "TBS/Robo/RoboCan/HW/CanModule.h"
#include "TBS/Robo/RoboCan/Task/ConsumingDataModuleTask.h"

namespace MBot {

	class CameraMotorModule: public TBS::Robo::RoboCan::CanModule {

			enum MotorCommands {
				GoMin = 30, GoMax = 31, GoRel = 32, Enable = 33
			};

		public:
			CameraMotorModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule);
			virtual ~CameraMotorModule();

			TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskGoMin() const;
			TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskGoMax() const;
			TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskGoRel(Poco::Int16 speed = 50, Poco::Int16 timeInMs = 50) const;
			TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskEnable(bool enable) const;
	};


}

#endif /* CameraMODULES_H_ */
