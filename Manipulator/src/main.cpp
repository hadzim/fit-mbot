/*
 * main.cpp
 *
 *  Created on: 7.3.2013
 *      Author: JV
 */

#include "TBS/NotificationWorker.h"
#include "TBS/Robo/RoboCan/HW/CanNode.h"
#include "TBS/Robo/RoboCan/HW/CanModule.h"
#include <iostream>
#include "TBS/Log.h"
#include "TBS/Robo/TaskExecutor.h"

#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/StreamCopier.h"
#include <iostream>
#include "NetChannel.h"
#include "UsbChannel.h"
#include "ConsumingDataModuleTask.h"
#include "TBS/Robo/RoboCan/Task/ModuleStatusTask.h"
#include "TBS/Robo/RoboCan/Task/ModuleDataTask.h"

using TBS::Robo::RoboCan::ModuleStatusTask;
using TBS::Robo::RoboCan::ModuleDataTask;

class MotorModule: public TBS::Robo::RoboCan::CanModule {

		enum TwoStateCommands {
			GoMin = 30, GoMax = 31, GoRel = 32, Enable = 33
		};

	public:
		MotorModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule) :
				TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule) {
		}
		virtual ~MotorModule() {
		}

		TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskGoMin(Poco::Int16 speed = 50) const {
			TBS::Robo::RoboCan::RoboCanMessageData data;
			data.setSHORT(speed);
			return new TBS::Robo::RoboCan::ModuleCommandTask("gomin", this->getInternalModule(), this->getInternalModule().composeCommand((int) GoMin, data));
		}
		TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskGoMax(Poco::Int16 speed = 50) const {
			TBS::Robo::RoboCan::RoboCanMessageData data;
			data.setSHORT(speed);
			return new TBS::Robo::RoboCan::ModuleCommandTask("gomax", this->getInternalModule(), this->getInternalModule().composeCommand((int) GoMax, data));
		}

		TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskGoRel(Poco::Int16 speed, Poco::Int16 timeInMs) const {
			TBS::Robo::RoboCan::RoboCanMessageData data;
			TBS::Robo::RoboCan::RoboCanMessageData::Short2 val;
			val.short1 = speed;
			val.short2 = timeInMs;
			data.setSHORT2(val);
			return new TBS::Robo::RoboCan::ModuleCommandTask("gorel", this->getInternalModule(), this->getInternalModule().composeCommand((int) GoRel, data));
		}

		TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskEnable(bool enable) const {
			TBS::Robo::RoboCan::RoboCanMessageData data;
			data.setUSHORT(enable ? 1 : 0);
			return new TBS::Robo::RoboCan::ModuleCommandAnyAckTask("enable", this->getInternalModule(),
					this->getInternalModule().composeCommand((int) Enable, data));
		}

};

class LightModule: public TBS::Robo::RoboCan::CanModule {

		enum LightModuleCommands {
			Enable = 30
		};

	public:
		LightModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule) :
				TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule) {
		}
		virtual ~LightModule() {
		}

		TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskEnable(bool enable) const {
			TBS::Robo::RoboCan::RoboCanMessageData data;
			data.setUSHORT(enable ? 1 : 0);
			return new TBS::Robo::RoboCan::ModuleCommandAnyAckTask("enable", this->getInternalModule(),
					this->getInternalModule().composeCommand((int) Enable, data));
		}

};

int main(int argc, char **argv) {

	try {
		TBS::initLogs("manipulator", 4);

		TBS::NotificationWorker::Ptr nw = new TBS::NotificationWorker("CMD");
		TBS::UsbChannel::Ptr dummy = new TBS::UsbChannel();

		TBS::Robo::RoboCan::CanNode node("Manipulator", 4, nw, dummy);
		MotorModule rotator("Manipulator.E1.Motor", &node, 1);
		MotorModule holder("Manipulator.Holder.Motor", &node, 2);
		LightModule light("Manipulator.Light", &node, 3);

		bool lighIsOn = false;

		while (1) {

			try {
				ModuleDataTask::Ptr tData = holder.taskGetData();
				TBS::Task::SynchronizedExectution s(tData, 1500);
				std::cout << "current: " << (int)tData->getOutput().getData(0).getUSHORT2().short1 << std::endl;
				std::cout << "encoder: " << (int)tData->getOutput().getData(0).getUSHORT2().short2 << std::endl;

			} catch (Poco::Exception & e) {
				std::cout << "###DATA ERR: " << e.displayText() << std::endl;
			}

			Poco::Thread::sleep(500);

			try {
				ModuleStatusTask::Ptr tStatus = rotator.taskGetStatus();
				TBS::Task::SynchronizedExectution s(tStatus, 1500);
				std::cout << "Motor STATUS: " << tStatus->getOutput().toString() << std::endl;
			} catch (Poco::Exception & e) {
				std::cout << "###STATUS ERR: " << e.displayText() << std::endl;
			}

			Poco::Thread::sleep(500);

			lighIsOn = !lighIsOn;
			try {
				TBS::Task::Task::Ptr tLight = light.taskEnable(lighIsOn);
				TBS::Task::SynchronizedExectution s(tLight, 1500);
				std::cout << "Light switched" << std::endl;
			} catch (Poco::Exception & e) {
				std::cout << "###LIGHT ERR: " << e.displayText() << std::endl;
			}

			Poco::Thread::sleep(500);

		}



		LDEBUG("app")<< "run is over" << LE;
		std::cout << "run is over" << std::endl;

	} catch (Poco::Exception & e) {
		LERROR("app")<< "Exc: " << e.displayText() << LE;
			std::cerr << e.displayText() << std::endl;
		}
		LDEBUG("app") << "return" << LE;
		std::cout << "return" << std::endl;
		return 0;
	}
