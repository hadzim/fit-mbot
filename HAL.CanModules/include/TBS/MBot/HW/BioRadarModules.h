/*
 * BioRadarModules.h
 *
 *  Created on: 15.5.2014
 *      Author: JV
 */

#ifndef BIORADARMODULES_H_
#define BIORADARMODULES_H_
#include "TBS/Robo/RoboCan/HW/CanModule.h"
#include "TBS/Robo/RoboCan/Task/ConsumingDataModuleTask.h"

namespace MBot {

	class BioRadarMotorModule: public TBS::Robo::RoboCan::CanModule {

			enum MotorCommands {
				GoMin = 30, GoMax = 31, GoRel = 32, Enable = 33, Unbreak = 35,
			};

		public:
			BioRadarMotorModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule);
			virtual ~BioRadarMotorModule();

			TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskGoMin(Poco::Int16 speed = 50) const;
			TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskGoMax(Poco::Int16 speed = 50) const;
			TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskGoRel(Poco::Int16 speed = 50, Poco::Int16 timeInMs = 50) const;
			TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskEnable(bool enable) const;
	};

	class BioRadarPositionTask: public TBS::Robo::RoboCan::ConsumingDataModuleTask {
		public:
			typedef Poco::SharedPtr<BioRadarPositionTask> Ptr;
			BioRadarPositionTask(std::string name, const TBS::Robo::RoboCan::InternalCanModule & module);
			virtual ~BioRadarPositionTask();

			struct Position {
					double position;
					bool isError;
			};
			Poco::BasicEvent<Position> PositionChanged;
		private:
			void onDataReady(TBS::Robo::RoboCan::DataMessage & msg);
	};

	class BioRadarMagneticModule: public TBS::Robo::RoboCan::CanModule {

		public:
			BioRadarMagneticModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule);
			virtual ~BioRadarMagneticModule();

			BioRadarPositionTask::Ptr taskConsumePosition() const;
		private:
			std::string n;
	};

}

#endif /* BIORADARMODULES_H_ */
