/*
 * main.cpp
 *
 *  Created on: 19.2.2014
 *      Author: JV
 */

#include <iostream>
#include "Serial.h"
#include <Poco/Thread.h>
#include "SerialWrapper.h"
#include <Poco/NumberFormatter.h>
std::ostream & operator<<(std::ostream & o, const MBot::SerialWrapper::VectorBuffer & buffer){
	o << "[";
	for (std::size_t i = 0; i < buffer.size(); i++){
		char c = buffer[i];
		if (c >= 'A' && c <= 'Z'){
			o << "" << c << "";
		} else if (c >= '0' && c <= '9'){
			o << "" << c << "";
		} else if (c >= 'a' && c <= 'z'){
			o << "" << c << "";
		} else if (c == '(' || c == ')' || c == ','){
			o << "" << c << "";
		} else {
			int val = (int)((unsigned char)c);
			o << "0x" << std::hex << val << std::dec << "";
		}
		if (i + 1 < buffer.size()){
			o << " ";
		}
	}
	o << "]";
	return o;
}

MBot::SerialWrapper::VectorBuffer makeCommand(const std::string & s, char destination = 0){
	MBot::SerialWrapper::VectorBuffer b;
	b.push_back(0x80 + destination);
	for (std::size_t i = 0; i < s.size(); i++){
		b.push_back(s[i]);
	}
	b.push_back(0x20);
	return b;
}

void runCommand(MBot::SerialWrapper & serial, const MBot::SerialWrapper::VectorBuffer & cmd){

	std::cout << "C " << cmd;
	serial.send(cmd);

	MBot::SerialWrapper::VectorBuffer response = serial.receive(50, cmd.size());
	if (response != cmd){
		std::cout << " FAILED (" << response << ")" << std::endl;
		throw Poco::Exception("Command rejected");
	}
	std::cout << " OK" << std::endl;
}

void runQuestion(MBot::SerialWrapper & serial,const MBot::SerialWrapper::VectorBuffer & cmd){

	std::cout << "Q " << cmd;
	serial.send(cmd);
	Poco::Thread::sleep(50);
	MBot::SerialWrapper::VectorBuffer response = serial.receive(50, cmd.size());
	std::cout << " ANSWER: " << response << std::endl;
}


void init(MBot::SerialWrapper & serial){
	runCommand(serial, makeCommand("ECHO"));
	runCommand(serial, makeCommand("BAUD9600"));
	runCommand(serial,  makeCommand("WAKE"));
	runCommand(serial,  makeCommand("OCHN(RS2,0,N,9600,1,8,C"));

	runCommand(serial, makeCommand("EIGN(2)"));
	runCommand(serial, makeCommand("EIGN(3)"));
	runCommand(serial, makeCommand("ZS"));


}

void go(MBot::SerialWrapper & serial, int speedLeft, int speedRight){

	//acceleration
	runCommand(serial,  makeCommand("ADT=30"));
	runCommand(serial,  makeCommand("DT=150"));
	//velocity
	runCommand(serial,  makeCommand("VT=" + Poco::NumberFormatter::format(speedLeft), 1));
	runCommand(serial,  makeCommand("VT=" + Poco::NumberFormatter::format(-speedRight), 2));

	int stopAfter = 8;
	//stopAfter = 2;

	runCommand(serial,  makeCommand("PRT=" + Poco::NumberFormatter::format(speedLeft/stopAfter), 1));
	runCommand(serial,  makeCommand("PRT=" + Poco::NumberFormatter::format(-speedRight/stopAfter), 2));

	runCommand(serial, makeCommand("G"));
}

void stopSlow(MBot::SerialWrapper & serial){

	go(serial, 0, 0);

}
void stop(MBot::SerialWrapper & serial){

	runCommand(serial, makeCommand("S"));
	runCommand(serial, makeCommand("O=0"));

	runCommand(serial,  makeCommand("PT=0", 1));
	runCommand(serial,  makeCommand("PT=0", 2));

}

int main(int argc, char **argv) {
	try {
		MBot::SerialWrapper serial(3, 9600);
/*
		runCommand(serial, makeCommand("0SADDR1"));
		runCommand(serial, makeCommand("1ECHO"));
		runCommand(serial, makeCommand("1SLEEP"));
		runCommand(serial, makeCommand("0SADDR2"));
		runCommand(serial, makeCommand("2ECHO"));
		runCommand(serial, makeCommand("2SLEEP"));
		runCommand(serial, makeCommand("0SADDR3"));
		runCommand(serial, makeCommand("3ECHO"));
		runCommand(serial, makeCommand("0WAKE"));
*/

		init(serial);

		{
			//runCommand(serial, makeCommand("MT"));
			//runCommand(serial,  makeCommand("T=3000"));
			//runCommand(serial, makeCommand("G"));
			//Poco::Thread::sleep(500);
			//runCommand(serial,  makeCommand("X"));
		}
		Poco::Thread::sleep(2000);
		{
			runCommand(serial, makeCommand("MP"));
			for (int i = 0; i < 100; i+=4){
				Poco::Thread::sleep(50);
				go(serial, 500000, i*10000);
			}

			for (int i = 0; i < 100; i+=4){
				Poco::Thread::sleep(50);
				go(serial, -500000, -i*10000);
			}


			//Poco::Thread::sleep(200);
			//stop(serial);

		}


	} catch (Poco::Exception & e) {
		std::cerr << "EXC: " << e.displayText() << std::endl;
	} catch (std::exception & e) {
		std::cerr << "EXC: " << e.what() << std::endl;
	}
	return 0;

}
