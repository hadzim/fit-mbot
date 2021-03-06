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
#ifndef BioRadar_H_
#define BioRadar_H_
#include "HAL/API/BioRadar.h"
#include <Poco/Types.h>
#include "TBS/Robo/RoboCan/Task/ModuleCommandTask.h"

#include "TBS/Robo/RoboCan/HW/CanNode.h"
#include "MBot/HW/BioRadarModules.h"
#include "TBS/Robo/RoboCan/Communicaton/IChannel.h"
#include "TBS/Robo/TaskExecutor.h"
namespace MBot {

	class BioRadar: public HAL::API::BioRadar::IBioRadar, public Poco::Runnable {
		public:


			struct Status {
					HAL::API::BioRadar::MotorInfo base;
					HAL::API::BioRadar::MotorInfo antenna;

					HAL::API::BioRadar::TouchInfo antenna1;
					HAL::API::BioRadar::TouchInfo antenna2;
					HAL::API::BioRadar::TouchInfo antenna3;
					HAL::API::BioRadar::TouchInfo antenna4;


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

			 virtual void GetStatus(HAL::API::BioRadar::MotorInfo & baseMotor, HAL::API::BioRadar::MotorInfo & antenaMotor, std::vector< HAL::API::BioRadar::TouchInfo > & antenaSensors);

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
