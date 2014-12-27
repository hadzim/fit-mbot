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
#ifndef Manipulator_H_
#define Manipulator_H_
#include "HAL/API/Manipulator.h"
#include <Poco/Types.h>
#include "TBS/Robo/RoboCan/Task/ModuleCommandTask.h"

#include "TBS/Robo/RoboCan/HW/CanNode.h"
#include "MBot/HW/ManipulatorModules.h"
#include "TBS/Robo/RoboCan/Communicaton/IChannel.h"
#include "TBS/Robo/TaskExecutor.h"
#include "ManipulatorModule.h"
#include <MBot/HW/ManipulatorModules.h>

#include <Poco/Activity.h>
#include <TBS/SimpleTimer.h>

#define ALLWORKING 1

namespace MBot {

	struct CurrentCommand {
			Poco::Mutex commandLock;
			TBS::Nullable<double> speed;
			TBS::Nullable<double> startPosition;
			TBS::Nullable<double> finalPosition;
	};

	struct CurrentExec {
		TBS::Nullable<double> speed;
		TBS::Nullable<bool> stop;
	};


	class JointControl {
		public:
			JointControl(int portMan, HAL::API::Manipulator::MotorInfo & info, Poco::Mutex & infoLock);
			~JointControl();
			void StartJoint(const double & speed);
			void StartJointTo(const double & speed, const double & destination);
			void StopJoint();

			ManipulatorModule & lowLevelModule();
		private:
			void feedbackLoopJoint();
			void execLoopJoint();
		private:

			ManipulatorModule joint;

			HAL::API::Manipulator::MotorInfo & info;
			Poco::Mutex & infoLock;

			CurrentExec execJointCmd;
			Poco::Mutex execLock;
			CurrentCommand feedbackJointCmd;

			Poco::Activity<JointControl> jointFeedback;
			Poco::Activity<JointControl> jointExec;
	};

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

			void execLoopJoint1();
			void execLoopJoint2();

/*
			enum JointID {
				J1,
				J2,
				Rot
			};
*/
			//void checkActivity(JointID jid, HAL::API::Manipulator::MotorInfo & motorInfo, CurrentCommand & cmd);

			//void updateCmd(double & speed, TBS::Nullable<double> final, HAL::API::Manipulator::MotorInfo & motorInfo, CurrentCommand & cmd, bool isRot);
			//void resetCmd(CurrentCommand & cmd);

			void dump();
			void rotateInternally(double sp, TBS::Nullable<double> pos);
			void lightInt(int timeout);
			void onLightTimer(TBS::SimpleTimer::TimerArg & a);
		private:

			TBS::Robo::RoboCan::CanNode node;

			TBS::Task::OneActiveTaskExectution rotationExecution;
			TBS::Task::OneActiveTaskExectution holderExecution;
			TBS::Task::OneActiveTaskExectution lightExecution;

			MBot::ManipulatorRotationModule rotationModule;
			MBot::ManipulatorHolderModule holderModule;
			MBot::ManipulatorLightModule lightModule;

			MBot::ManipulatorMagneticModule magneticModule;

			int speed;
			int maxRelDurationTimeInMs;

			Poco::Thread t;
			bool finished;
			bool enabled;
			Poco::Mutex m;
			Status currentStatus;

			Poco::Activity<Manipulator> rotationFeedback;

			CurrentCommand rotationcmd;

			TBS::SimpleTimer lightTimer;

#if ALLWORKING
			JointControl j1;
			JointControl j2;
			//ManipulatorModule joint1;
			//ManipulatorModule joint2;
#endif
	};

} /* namespace MBot */
#endif /* Manipulator_H_ */
