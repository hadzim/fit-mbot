/*
 * Manipulator.h
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#ifndef Manipulator_H_
#define Manipulator_H_
#include "HAL/API/Manipulator.h"
#include <Poco/Types.h>
#include "TBS/Robo/RoboCan/Task/ModuleCommandTask.h"

#include "TBS/Robo/RoboCan/HW/CanNode.h"
#include "../../include/TBS/MBot/HW/ManipulatorModules.h"
#include "TBS/Robo/RoboCan/Communicaton/IChannel.h"
#include "TBS/Robo/TaskExecutor.h"
#include "ManipulatorModule.h"
#include <TBS/MBot/HW/ManipulatorModules.h>

#define ALLWORKING 1

namespace MBot {

	class Manipulator: public HAL::API::Manipulator::IManipulator, public Poco::Runnable {
		public:

			struct Status {
				HAL::API::Manipulator::MotorInfo rotation;
				HAL::API::Manipulator::MotorInfo joint1;
				HAL::API::Manipulator::MotorInfo joint2;
				HAL::API::Manipulator::MotorInfo holder;
			};

			Manipulator(TBS::NotificationWorker::Ptr nw, TBS::Robo::RoboCan::IChannel::Ptr canChannel,int portMan1, int portMan2);
			~Manipulator();

			void Enable();
			void Disable();

			virtual void StartRotation(const double & speed);
			virtual void StopRotation();

			virtual void StartJoint1(const double & speed);
			virtual void StopJoint1();

			virtual void StartJoint2(const double & speed);
			virtual void StopJoint2();

			virtual void StartHolder(const double & speed);
			virtual void StopHolder();
			virtual void SetHolderThreshold(const double & threshold);

			 virtual void GetStatus(HAL::API::Manipulator::MotorInfo & rotation, HAL::API::Manipulator::MotorInfo & joint1, HAL::API::Manipulator::MotorInfo & joint2, HAL::API::Manipulator::MotorInfo & holder);

			 virtual void LightOn();
			 virtual void LightOff();

		private:
			 void onPositionChanged(ManipulatorPositionTask::Position & pos);
			 void onRotationChanged(ManipulatorRotationPositionTask::Position & pos);

		private:

			void run();

			void dump();
		private:

			TBS::Robo::RoboCan::CanNode node;

			TBS::Task::OneActiveTaskExectution rotationExecution;
			TBS::Task::OneActiveTaskExectution holderExecution;
			TBS::Task::OneActiveTaskExectution lightExecution;

			MBot::ManipulatorRotationModule rotationModule;
			MBot::ManipulatorHolderModule holderModule;
			MBot::ManipulatorLightModule lightModule;

			MBot::ManipulatorMagneticModule magneticModule;
#if ALLWORKING
			ManipulatorModule joint1;
			ManipulatorModule joint2;
#endif
			int speed;
			int maxRelDurationTimeInMs;

			Poco::Thread t;
			bool finished;
			bool enabled;
			Poco::Mutex m;
			Status currentStatus;
	};

} /* namespace MBot */
#endif /* Manipulator_H_ */
