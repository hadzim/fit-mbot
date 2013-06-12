/*
 * main.cpp
 *
 *  Created on: 7.3.2013
 *      Author: JV
 */

#include "TBS/Thread/NotificationWorker.h"
#include "TBS/Robo/RoboCan/HW/CanNode.h"
#include "TBS/Robo/RoboCan/HW/CanModule.h"
#include "DummyChannel.h"
#include <iostream>
#include "TBS/Log.h"
#include "TBS/Robo/TaskExecutor.h"

int main(int argc, char **argv) {
	try {
		TBS::initLogs("log.log", 8);

		TBS::NotificationWorker::Ptr nw = new TBS::NotificationWorker("CMD");
		DummyChannel::Ptr dummy = new DummyChannel();

		TBS::Robo::RoboCan::CanNode node("myNode", 10, nw, dummy);
		TBS::Robo::RoboCan::CanModule m("myModule", &node, 5);

		TBS::Task::Task::Ptr t1 = m.taskGetStatus();

		TBS::Task::Task::Ptr t2 = m.taskStart();

		TBS::Task::Task::Ptr t3 = m.taskGetData();

		t2->start();
		t3->start();

		{
			try {
				TBS::Task::SynchronizedExectution s1(t1, 500);
			} catch (Poco::Exception & e){

			}

			t3->cancel();

			try {
				TBS::Task::SynchronizedExectution s1(t1, 500);
			} catch (Poco::Exception & e){

			}

			t2->cancel();

			try {
				TBS::Task::SynchronizedExectution s1(t1, 500);
			} catch (Poco::Exception & e){

			}


		}



		Poco::Thread::sleep(3000);
		std::cout << "cancel" << std::endl;
		std::cout << "cancel done" << std::endl;
	} catch (Poco::Exception & e) {
		std::cerr << e.displayText() << std::endl;
	}
	return 0;
}
