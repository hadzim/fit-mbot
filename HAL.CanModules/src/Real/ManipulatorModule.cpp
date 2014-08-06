/*
 * ManipulatorModule.cpp
 *
 *  Created on: 22.7.2014
 *      Author: JV
 */

#include "ManipulatorModule.h"
#include <string>
#include <iostream>
#include <Poco/Thread.h>
#include <Poco/NumberFormatter.h>
#include <Poco/NumberParser.h>
#include <cmath>

namespace MBot {

	static TBS::Serial::SerialWrapper::VectorBuffer makeCommand(const std::string & s) {
		TBS::Serial::SerialWrapper::VectorBuffer b;

		for (std::size_t i = 0; i < s.size(); i++) {
			b.push_back(s[i]);
		}
		b.push_back(';');
		return b;
	}

	static void send(TBS::Serial::SerialWrapper & w1, std::string command) {
		std::cout << "mancmd: " << command << std::endl;
		TBS::Serial::SerialWrapper::VectorBuffer buff = makeCommand(command);
		w1.send(buff);
		for (int i = 0; i < 10; i++) {
			Poco::Thread::sleep(10);
			TBS::Serial::SerialWrapper::VectorBuffer buff2 = w1.receive();
			if (!buff2.empty()) {

				//std::cout << "size: " << buff2.size() << std::endl;
				std::cout << "manrecv:" << std::endl;
				for (auto b = buff2.begin(); b != buff2.end(); b++) {
					std::cout << *b << " ";
				}
				std::cout << std::endl;
				break;
			}
		}
	}

	ManipulatorModule::ManipulatorModule(int portNumber) :
			w(portNumber, 115200) {

	}

	void ManipulatorModule::enable() {
		send(w, "AC=1000000000");
		send(w, "DC=1000000000");
		send(w, "SD=1000000000");

		send(w, "SF=0");
		send(w, "FS=0");    //final speed
		send(w, "SP=5000"); //speed
		send(w, "MR[1]=0");
		send(w, "MR[2]=0");

		send(w, "PO=1"); //relative positioning mode
		send(w, "MO=1"); //motor on

		Poco::Thread::sleep(100);

		send(w, "AC=10000");
		send(w, "DC=10000");
		send(w, "SD=30000");
	}

	void ManipulatorModule::disable() {
		send(w, "MO=0");
	}

	void ManipulatorModule::unbreakMotor() {
		send(w, "ob[1]=1");
	}

	void ManipulatorModule::breakMotor() {
		send(w, "ob[1]=0");
	}

#define MAX_MAN_SPEED 30000

	void ManipulatorModule::go(int speed) {
		send(w, "SP=" + Poco::NumberFormatter::format((int) std::abs(speed)));
		if (speed > 0) {
			if (speed > MAX_MAN_SPEED) {
				speed = MAX_MAN_SPEED;
			}
			send(w, "PR=" + Poco::NumberFormatter::format((int) std::abs(speed / 2)));
		}
		if (speed == 0) {
			send(w, "ST[1]");
		}
		if (speed < 0) {
			if (speed < -MAX_MAN_SPEED) {
				speed = -MAX_MAN_SPEED;
			}
			send(w, "PR=-" + Poco::NumberFormatter::format((int) std::abs(speed / 2)));
		}
		send(w, "BG");
	}
	void ManipulatorModule::stop() {
		send(w, "ST[1]");
		send(w, "TW[80]=0");
	}
	void ManipulatorModule::resetPosition() {
		send(w, "HM[1]=1");
	}

} /* namespace MBot */
