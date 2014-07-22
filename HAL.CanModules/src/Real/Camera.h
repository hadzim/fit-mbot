/*
 * Camera.h
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#ifndef Camera_H_
#define Camera_H_
#include "HAL/API/Camera.h"
#include <Poco/Types.h>
#include "TBS/Robo/RoboCan/Task/ModuleCommandTask.h"

#include "TBS/Robo/RoboCan/HW/CanNode.h"
#include "../../include/TBS/MBot/HW/CameraModules.h"
#include "TBS/Robo/RoboCan/Communicaton/IChannel.h"
#include "TBS/Robo/TaskExecutor.h"
namespace MBot {

	class Camera: public HAL::API::Camera::ICamera, public Poco::Runnable {
		public:

			struct Status {

			};

			Camera(TBS::NotificationWorker::Ptr nw, TBS::Robo::RoboCan::IChannel::Ptr canChannel);
			~Camera();

			void Enable();
			void Disable();

			void GoMinEngine();
			void GoMaxEngine();
			void GoRelEngine(const double & speed);

			void GoMinServo1();
			void GoMaxServo1();
			void GoRelServo1(const double & speed);

			void GoMinServo2();
			void GoMaxServo2();
			void GoRelServo2(const double & speed);

			void LightOn();
			void LightOff();

		private:

			void run();

		private:

			TBS::Robo::RoboCan::CanNode node;

			TBS::Task::OneActiveTaskExectution motorExecution;
			TBS::Task::OneActiveTaskExectution servo1Execution;
			TBS::Task::OneActiveTaskExectution servo2Execution;
			TBS::Task::OneActiveTaskExectution lightExecution;

			MBot::CameraMotorModule motorModule;
			MBot::CameraMotorModule servo1Module;
			MBot::CameraMotorModule servo2Module;
			MBot::LightModule lightModule;

			int speed;
			int maxRelDurationTimeInMs;

			Poco::Thread t;
			bool finished;
			bool enabled;
			Poco::Mutex m;
			Status currentStatus;
	};

} /* namespace MBot */
#endif /* Camera_H_ */
