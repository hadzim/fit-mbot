/*
 * BioRadar.h
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#ifndef BioRadar_H_
#define BioRadar_H_
#include "HAL/API/BioRadar.h"
#include <Poco/Types.h>
#include "TBS/Robo/RoboCan/Task/ModuleCommandTask.h"

#include "TBS/Robo/RoboCan/HW/CanNode.h"
#include "../../include/TBS/MBot/HW/BioRadarModules.h"
#include "TBS/Robo/RoboCan/Communicaton/IChannel.h"
#include "TBS/Robo/TaskExecutor.h"
namespace MBot {

	class BioRadar: public HAL::API::BioRadar::IBioRadar, public Poco::Runnable {
		public:
			struct MotorStatus {
					bool touchMin;
					bool touchMax;

					double position;
					bool positionError;

					MotorStatus();
			};

			struct AntennaSensor {
					bool touch;
					int distance;

					AntennaSensor();
			};

			struct Status {
					MotorStatus base;
					MotorStatus antenna;

					AntennaSensor antenna1;
					AntennaSensor antenna2;
					AntennaSensor antenna3;
					AntennaSensor antenna4;


			};

			BioRadar(TBS::NotificationWorker::Ptr nw, TBS::Robo::RoboCan::IChannel::Ptr canChannel);
			virtual ~BioRadar();

			void Enable();
			void Disable();

			void GoMinAntenna();
			void GoMaxAntenna();
			void GoRelAntenna(const double & speed);

			void GoMinBase();
			void GoMaxBase();
			void GoRelBase(const double & speed);

			void GetMotorStatus(const bool & isBase, bool & touchMin, bool & touchMax, double & position, bool & positionError);

			/**
			 *
			 * [out] std::vector< TBS::Services::Tuple< bool, int32_t > > antenaSensors: array of structs(isTouch,distance)
			 */
			std::vector<TBS::Services::Tuple<bool, int32_t> > GetAntenaStatus();

		private:

			virtual void run();
			void onBasePositionChanged(BioRadarPositionTask::Position & pos);
			void onAntennaPositionChanged(BioRadarPositionTask::Position & pos);
			void onAntennaTouchChanged(BioRadarTouchTask::Positions & pos);
		private:

			TBS::Task::OneActiveTaskExectution baseExecution;
			TBS::Robo::RoboCan::CanNode baseNode;
			MBot::BioRadarMotorModule baseMotorModule;
			MBot::BioRadarMagneticModule baseMagneticModule;

			TBS::Task::OneActiveTaskExectution antennaExecution;
			TBS::Robo::RoboCan::CanNode antennaNode;
			MBot::BioRadarMotorModule antennaMotorModule;
			MBot::BioRadarMagneticModule antennaMagneticModule;
			MBot::BioRadarTouchModule antennaTouchModule;

			int speed;
			int maxRelDurationTimeInMs;

			Poco::Thread t;
			bool finished;
			bool enabled;
			Poco::Mutex m;
			Status currentStatus;
	};

} /* namespace MBot */
#endif /* BioRadar_H_ */
