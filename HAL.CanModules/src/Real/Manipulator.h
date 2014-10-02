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

#include <Poco/Activity.h>

#define ALLWORKING 1

namespace MBot {



	class Manipulator: public HAL::API::Manipulator::IManipulator, public Poco::Runnable {

			struct CurrentCommand {
					Poco::Mutex commandLock;
					TBS::Nullable<double> speed;
					TBS::Nullable<double> startPosition;
					TBS::Nullable<double> finalPosition;
			};

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
			virtual void StartRotationTo(const double & speed, const double & destination);
			virtual void StopRotation();

			virtual void StartJoint1(const double & speed);
			virtual void StartJoint1To(const double & speed, const double & destination);
			virtual void StopJoint1();

			virtual void StartJoint2(const double & speed);
			virtual void StartJoint2To(const double & speed, const double & destination);
			virtual void StopJoint2();

			virtual void StartHolder(const double & speed);
			virtual void StopHolder();
			virtual void SetHolderThreshold(const double & threshold);

			 virtual void GetStatus(double & rotation, double & joint1, double & joint2, double & holder);

			 virtual void LightOn();
			 virtual void LightOff();

		private:
			 void onPositionChanged(ManipulatorPositionTask::Position & pos);
			 void onRotationChanged(ManipulatorRotationPositionTask::Position & pos);

		private:

			void run();

			void feedbackLoopJoint1();
			void feedbackLoopJoint2();
			void feedbackLoopRot();

			enum JointID {
				J1,
				J2,
				Rot
			};

			void checkActivity(JointID jid, HAL::API::Manipulator::MotorInfo & motorInfo, CurrentCommand & cmd);

			void updateCmd(double & speed, TBS::Nullable<double> final, HAL::API::Manipulator::MotorInfo & motorInfo, CurrentCommand & cmd, bool isRot);
			void resetCmd(CurrentCommand & cmd);

			void dump();
			void rotateInternally(double sp, TBS::Nullable<double> pos);
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

			Poco::Activity<Manipulator> joint1Feedback;
			Poco::Activity<Manipulator> joint2Feedback;
			Poco::Activity<Manipulator> rotationFeedback;

			CurrentCommand joint1cmd;
			CurrentCommand joint2cmd;
			CurrentCommand rotationcmd;
	};

} /* namespace MBot */
#endif /* Manipulator_H_ */
