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

	class LightModule: public TBS::Robo::RoboCan::CanModule {

				enum Commands {
					Enable = 34
				};

			public:
				LightModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule);
				virtual ~LightModule();

				TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskEnable(bool enable) const;
		};


}

#endif /* CameraMODULES_H_ */
