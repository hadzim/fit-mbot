/*
 * main.cpp
 *
 *  Created on: 7.3.2013
 *      Author: JV
 */

#include "TBS/Thread/NotificationWorker.h"
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

class LEDModule : public TBS::Robo::RoboCan::CanModule {

	enum TwoStateCommands {
		On = 20,
		Off = 21,
		Value = 22
	};

public:
	LEDModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node,
			int numberWithinModule) :
			TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule) {
	}
	virtual ~LEDModule() {
	}

	TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskTurnOnLEDs(char intensity) const {
		TBS::Robo::RoboCan::RoboCanMessageData data;
		data.setUCHAR(intensity);
		return new TBS::Robo::RoboCan::ModuleCommandTask(this->getInternalModule(), this->getInternalModule().composeCommand((int)Value, data));
	}
};

int main(int argc, char **argv) {

	try {
		TBS::initLogs("log.log", 8);

		TBS::NotificationWorker::Ptr nw = new TBS::NotificationWorker("CMD");
		TBS::NetChannel::Ptr dummy = new TBS::NetChannel();

		TBS::Robo::RoboCan::CanNode node("HEAD", 1, nw, dummy);
		LEDModule m("CAMERA_LIGHT_LED", &node, 2);

		TBS::Task::Task::Ptr tStatus = m.taskGetStatus();

		TBS::Task::Task::Ptr tStart = m.taskStart();

		TBS::Task::Task::Ptr tHalt = m.taskHalt();

		TBS::Task::Task::Ptr tStop = m.taskStop();

		TBS::Task::Task::Ptr tLED1 = m.taskTurnOnLEDs(25);
		TBS::Task::Task::Ptr tLED2 = m.taskTurnOnLEDs(50);


		{
			try {
				TBS::Task::SynchronizedExectution s(tStatus, 500);
			} catch (Poco::Exception & e) {

			}

			try {
				TBS::Task::SynchronizedExectution s(tStart, 500);
			} catch (Poco::Exception & e) {

			}

			try {
				TBS::Task::SynchronizedExectution s(tStatus, 500);
			} catch (Poco::Exception & e) {

			}

			Poco::Thread::sleep(1000);

			try {
				TBS::Task::SynchronizedExectution s(tLED1, 500);
			} catch (Poco::Exception & e) {

			}

			Poco::Thread::sleep(1000);

			try {
				TBS::Task::SynchronizedExectution s(tLED2, 500);
			} catch (Poco::Exception & e) {

			}


			try {
				TBS::Task::SynchronizedExectution s(tStatus, 500);
			} catch (Poco::Exception & e) {

			}

			try {
				TBS::Task::SynchronizedExectution s(tStop, 500);
			} catch (Poco::Exception & e) {

			}

			try {
				TBS::Task::SynchronizedExectution s(tStatus, 500);
			} catch (Poco::Exception & e) {

			}

			try {
				TBS::Task::SynchronizedExectution s(tHalt, 500);
			} catch (Poco::Exception & e) {

			}

			try {
				TBS::Task::SynchronizedExectution s(tStatus, 500);
			} catch (Poco::Exception & e) {

			}

		}

		std::cout << "run is over" << std::endl;
	} catch (Poco::Exception & e) {
		std::cerr << e.displayText() << std::endl;
	}
	std::cout << "return" << std::endl;
	return 0;
}
