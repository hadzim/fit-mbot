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

	class BioRadar : public HAL::API::BioRadar::IBioRadar, public Poco::Runnable {
		public:

			struct Status {
				bool baseTouchMin;
				bool baseTouchMax;

				double basePosition;
				bool basePositionError;

				bool antennaTouchMin;
				bool antennaTouchMax;

				double antennaPosition;
				bool antennaPositionError;

				bool antennaTouch1;
				bool antennaTouch2;
				bool antennaTouch3;
				bool antennaTouch4;

				int antennaDistance1;
				int antennaDistance2;
				int antennaDistance3;
				int antennaDistance4;
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

			void GetStatus(bool & baseTouchMin, bool & baseTouchMax, double & basePosition, bool & basePositionError, bool & antennaTouchMin, bool & antennaTouchMax, double & antennaPosition, bool & antennaPositionError, bool & antennaTouch1, bool & antennaTouch2, bool & antennaTouch3, bool & antennaTouch4, int32_t & antennaDistance1, int32_t & antennaDistance2, int32_t & antennaDistance3, int32_t & antennaDistance4);


		private:

			virtual void run();
			void onBasePositionChanged(BioRadarPositionTask::Position & pos);
			void onAntennaPositionChanged(BioRadarPositionTask::Position & pos);
		private:

			TBS::Task::OneActiveTaskExectution baseExecution;
			TBS::Robo::RoboCan::CanNode baseNode;
			MBot::BioRadarMotorModule baseMotorModule;
			MBot::BioRadarMagneticModule baseMagneticModule;

			TBS::Task::OneActiveTaskExectution antennaExecution;
			TBS::Robo::RoboCan::CanNode antennaNode;
			MBot::BioRadarMotorModule antennaMotorModule;
			MBot::BioRadarMagneticModule antennaMagneticModule;

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
