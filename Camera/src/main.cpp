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

class MotorModule : public TBS::Robo::RoboCan::CanModule {

	enum TwoStateCommands {
		GoMin = 30,
		GoMax = 31,
		GoRel = 32,
		Enable = 33
	};

public:
	MotorModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node,
			int numberWithinModule) :
			TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule) {
	}
	virtual ~MotorModule() {
	}

	TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskGoMin(Poco::Int16 speed = 50) const {
		TBS::Robo::RoboCan::RoboCanMessageData data;
		data.setSHORT(speed);
		return new TBS::Robo::RoboCan::ModuleCommandTask("gomin", this->getInternalModule(), this->getInternalModule().composeCommand((int)GoMin, data));
	}
	TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskGoMax(Poco::Int16 speed = 50) const {
		TBS::Robo::RoboCan::RoboCanMessageData data;
		data.setSHORT(speed);
		return new TBS::Robo::RoboCan::ModuleCommandTask("gomax", this->getInternalModule(), this->getInternalModule().composeCommand((int)GoMax, data));
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
			return new TBS::Robo::RoboCan::ModuleCommandAnyAckTask("enable", this->getInternalModule(), this->getInternalModule().composeCommand((int)Enable, data));
		}

};

class MagneticModule : public TBS::Robo::RoboCan::CanModule {

public:
	MagneticModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node,
			int numberWithinModule) :
			TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule) {
	}
	virtual ~MagneticModule() {
	}

	TBS::Robo::RoboCan::ConsumingDataModuleTask::Ptr taskConsumeData() const {
		return new TBS::Robo::RoboCan::ConsumingDataModuleTask(this->getInternalModule());
	}

};

int main(int argc, char **argv) {

	try {
		TBS::initLogs("camera", 4);

		TBS::NotificationWorker::Ptr nw = new TBS::NotificationWorker("CMD");
		TBS::UsbChannel::Ptr dummy = new TBS::UsbChannel();

		TBS::Robo::RoboCan::CanNode node("Camera", 1, nw, dummy);
		MotorModule m("Camera.E1.Motor", &node, 3);
		//MagneticModule mag("BioRadar.Antena.Magnetic", &node, 2);

		//TBS::Robo::RoboCan::ConsumingDataModuleTask::Ptr tConsume = mag.taskConsumeData();
		//tConsume->start();
		ModuleStatusTask::Ptr tStatus = m.taskGetStatus();
		ModuleDataTask::Ptr tData = m.taskGetData();




		TBS::Task::Task::Ptr tStart = m.taskStart();

		TBS::Task::Task::Ptr tHalt = m.taskHalt();

		TBS::Task::Task::Ptr tStop = m.taskStop();

		TBS::Task::Task::Ptr tGoMin = m.taskGoMin(5);
		TBS::Task::Task::Ptr tGoMax = m.taskGoMax(95);

		try {
			TBS::Task::SynchronizedExectution s(tStatus, 1500);
//			std::cout <<
			std::cout << "STATUS: " <<  tStatus->getOutput().toString() << std::endl;
		} catch (Poco::Exception & e) {
			std::cout << "###STATUS eRR: " << e.displayText() << std::endl;
		}

		try {
			TBS::Task::SynchronizedExectution s(tData, 1500);
			std::cout << "position: " << (int)tData->getOutput().getData(0).getUCHAR4().uchar1 << std::endl;
			std::cout << "direction: " << (int)tData->getOutput().getData(0).getUCHAR4().uchar2 << std::endl;
			std::cout << "speed: " << (int)tData->getOutput().getData(0).getUCHAR4().uchar3 << std::endl;
			std::cout << "running: " << (int)tData->getOutput().getData(0).getUCHAR4().uchar4 << std::endl;
		} catch (Poco::Exception & e) {
			std::cout << "###DATA eRR: " << e.displayText() << std::endl;
		}

		try {
			TBS::Task::Task::Ptr tEnable = m.taskEnable(true);
			TBS::Task::SynchronizedExectution s(tEnable, 1500);
			std::cout << "ENABLED" << std::endl;
		} catch (Poco::Exception & e) {
			std::cout << "###DATA eRR: " << e.displayText() << std::endl;
		}

		for (int i = 0; i < 5; i++){
			try {
				TBS::Task::Task::Ptr tGoRel = m.taskGoRel(-100, 25);
				TBS::Task::SynchronizedExectution s(tGoRel, 2500);
				std::cout << "Go REL done" << std::endl;
			} catch (Poco::Exception & e) {
				std::cout << "###DATA eRR: " << e.displayText() << std::endl;
			}
		}

		try {
					TBS::Task::Task::Ptr tEnable = m.taskEnable(false);
					TBS::Task::SynchronizedExectution s(tEnable, 1500);
					std::cout << "ENABLED" << std::endl;
				} catch (Poco::Exception & e) {
					std::cout << "###DATA eRR: " << e.displayText() << std::endl;
				}

			//tConsume->cancel();
			Poco::Thread::sleep(1000);


		LDEBUG("app") << "run is over" << LE;
		std::cout << "run is over" << std::endl;

	} catch (Poco::Exception & e) {
		LERROR("app") << "Exc: " << e.displayText() << LE;
		std::cerr << e.displayText() << std::endl;
	}
	LDEBUG("app") << "return" << LE;
	std::cout << "return" << std::endl;
	return 0;
}
