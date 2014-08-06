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

class RotationModule: public TBS::Robo::RoboCan::CanModule {

		enum TwoStateCommands {
			GoRel = 30, Enable = 32
		};

	public:
		RotationModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule) :
				TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule) {
		}
		virtual ~RotationModule() {
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

class HolderModule: public TBS::Robo::RoboCan::CanModule {

		enum TwoStateCommands {
			GoRel = 30, SetThreshold = 31, Enable = 32
		};

	public:
		HolderModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule) :
				TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule) {
		}
		virtual ~HolderModule() {
		}

		TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskGoRel(Poco::Int16 speed, Poco::Int16 timeInMs) const {
			TBS::Robo::RoboCan::RoboCanMessageData data;
			TBS::Robo::RoboCan::RoboCanMessageData::Short2 val;
			val.short1 = speed;
			val.short2 = timeInMs;
			data.setSHORT2(val);
			return new TBS::Robo::RoboCan::ModuleCommandTask("gorel", this->getInternalModule(), this->getInternalModule().composeCommand((int) GoRel, data));
		}

		TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskSetThreshold(Poco::UInt16 thresh) const {
			TBS::Robo::RoboCan::RoboCanMessageData data;
			data.setUSHORT(thresh);
			return new TBS::Robo::RoboCan::ModuleCommandTask("setthresh", this->getInternalModule(),
					this->getInternalModule().composeCommand((int) SetThreshold, data));
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
		TBS::initLogs("manipulator", 8);

		TBS::NotificationWorker::Ptr nw = new TBS::NotificationWorker("CMD");
		TBS::UsbChannel::Ptr dummy = new TBS::UsbChannel();

		TBS::Robo::RoboCan::CanNode node("Manipulator", 4, nw, dummy);
		HolderModule holder("Manipulator.Holder.Motor", &node, 1);
		RotationModule rotation("Manipulator.E1.Motor", &node, 2);

		LightModule light("Manipulator.Light", &node, 3);

		bool lighIsOn = false;

		while (true) {
			Poco::Thread::sleep(500);

			lighIsOn = !lighIsOn;
			try {
				TBS::Task::Task::Ptr tLight = light.taskEnable(lighIsOn);
				TBS::Task::SynchronizedExectution s(tLight, 1500);
				std::cout << "Light switched" << std::endl;
			} catch (Poco::Exception & e) {
				std::cout << "###LIGHT ERR: " << e.displayText() << std::endl;
			}
		}

		/*while (1)*/{
			/*
			 try {
			 ModuleDataTask::Ptr tData = holder.taskGetData();
			 TBS::Task::SynchronizedExectution s(tData, 1500);
			 std::cout << "holder current: " << (int)tData->getOutput().getData(0).getUSHORT2().short1 << std::endl;
			 std::cout << "holder encoder: " << (int)tData->getOutput().getData(0).getUSHORT2().short2 << std::endl;

			 } catch (Poco::Exception & e) {
			 std::cout << "###DATA ERR: " << e.displayText() << std::endl;
			 }

			 Poco::Thread::sleep(500);

			 try {
			 ModuleStatusTask::Ptr tStatus = rotation.taskGetStatus();
			 TBS::Task::SynchronizedExectution s(tStatus, 1500);
			 std::cout << "rotation STATUS: " << tStatus->getOutput().toString() << std::endl;
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
			 */
			/*
			 try {
			 TBS::Task::Task::Ptr t = rotation.taskEnable(true);
			 TBS::Task::SynchronizedExectution s(t, 1500);
			 std::cout << "Enabled" << std::endl;
			 } catch (Poco::Exception & e) {
			 std::cout << "###ENABLE ERR: " << e.displayText() << std::endl;
			 }

			 Poco::Thread::sleep(500);

			 try {
			 TBS::Task::Task::Ptr t = rotation.taskGoRel(100, 100);
			 TBS::Task::SynchronizedExectution s(t, 1500);
			 std::cout << "GO REL" << std::endl;
			 } catch (Poco::Exception & e) {
			 std::cout << "###ROTATE ERR: " << e.displayText() << std::endl;
			 }

			 Poco::Thread::sleep(1000);

			 try {
			 TBS::Task::Task::Ptr t = rotation.taskGoRel(-100, 100);
			 TBS::Task::SynchronizedExectution s(t, 1500);
			 std::cout << "GO REL" << std::endl;
			 } catch (Poco::Exception & e) {
			 std::cout << "###ROTATE ERR: " << e.displayText() << std::endl;
			 }

			 Poco::Thread::sleep(500);

			 Poco::Thread::sleep(500);

			 try {
			 TBS::Task::Task::Ptr t = rotation.taskEnable(false);
			 TBS::Task::SynchronizedExectution s(t, 1500);
			 std::cout << "Disabled" << std::endl;
			 } catch (Poco::Exception & e) {
			 std::cout << "###DISABLE ERR: " << e.displayText() << std::endl;
			 }





			 try {
			 TBS::Task::Task::Ptr t = holder.taskEnable(true);
			 TBS::Task::SynchronizedExectution s(t, 1500);
			 std::cout << "Enabled" << std::endl;
			 } catch (Poco::Exception & e) {
			 std::cout << "###ENABLE ERR: " << e.displayText() << std::endl;
			 }

			 Poco::Thread::sleep(500);

			 try {
			 TBS::Task::Task::Ptr t = holder.taskGoRel(80, 1000);
			 TBS::Task::SynchronizedExectution s(t, 1500);
			 std::cout << "GO REL" << std::endl;
			 } catch (Poco::Exception & e) {
			 std::cout << "###ROTATE ERR: " << e.displayText() << std::endl;
			 }

			 Poco::Thread::sleep(1000);

			 try {
			 TBS::Task::Task::Ptr t = holder.taskGoRel(-80, 1000);
			 TBS::Task::SynchronizedExectution s(t, 1500);
			 std::cout << "GO REL" << std::endl;
			 } catch (Poco::Exception & e) {
			 std::cout << "###ROTATE ERR: " << e.displayText() << std::endl;
			 }

			 Poco::Thread::sleep(500);


			 try {
			 TBS::Task::Task::Ptr t = holder.taskEnable(false);
			 TBS::Task::SynchronizedExectution s(t, 1500);
			 std::cout << "Disabled" << std::endl;
			 } catch (Poco::Exception & e) {
			 std::cout << "###DISABLE ERR: " << e.displayText() << std::endl;
			 }
			 */
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
