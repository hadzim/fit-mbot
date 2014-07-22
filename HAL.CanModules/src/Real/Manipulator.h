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
namespace MBot {

	class Manipulator: public HAL::API::Manipulator::IManipulator, public Poco::Runnable {
		public:

			struct Status {

			};

			Manipulator(TBS::NotificationWorker::Ptr nw, TBS::Robo::RoboCan::IChannel::Ptr canChannel);
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

		private:

			void run();

		private:

			TBS::Robo::RoboCan::CanNode node;

			TBS::Task::OneActiveTaskExectution rotationExecution;
			TBS::Task::OneActiveTaskExectution holderExecution;

			MBot::ManipulatorRotationModule rotationModule;
			MBot::ManipulatorHolderModule holderModule;

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
