/*
 * MovementImpl.cpp
 *
 *  Created on: 1.4.2014
 *      Author: JV
 */

#include "MovementImpl.h"
#include "TBS/Log.h"
#include <sstream>
#include <iostream>
#include <Poco/NumberFormatter.h>
#include <Poco/NumberParser.h>
#include "Poco/Thread.h"
namespace MBot {

std::ostream & operator<<(std::ostream & o, const MBot::SerialLib::VectorBuffer & buffer){
	o << "[";
	for (std::size_t i = 0; i < buffer.size(); i++){
		char c = buffer[i];
		if (c >= 'A' && c <= 'Z'){
			o << "" << c << "";
		} else if (c >= '0' && c <= '9'){
			o << "" << c << "";
		} else if (c >= 'a' && c <= 'z'){
			o << "" << c << "";
		} else if (c == '(' || c == ')' || c == ',' || c == '-'){
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

MBot::SerialLib::VectorBuffer makeCommand(const std::string & s, char destination = 0){
	TBS::Serial::SerialWrapper::VectorBuffer b;
	b.push_back(0x80 + destination);
	for (std::size_t i = 0; i < s.size(); i++){
		b.push_back(s[i]);
	}
	b.push_back(0x20);
	return b;
}

void runCommand(MBot::SerialLib & serial, const MBot::SerialLib::VectorBuffer & cmd){
	std::stringstream s;
	s << "C " << cmd;
	serial.send(cmd);

	TBS::Serial::SerialWrapper::VectorBuffer response = serial.receive(50, cmd.size());
	if (response != cmd){
		s << " FAILED (" << response << ")";
		std::cout << s.str() << std::endl;
		throw Poco::Exception("Command rejected");
	}
	s << " OK";
	LDEBUG("HAL.Movement") << s.str() << LE;
	std::cout << s.str() << std::endl;
}

void runCommandExc(MBot::SerialLib & serial, const MBot::SerialLib::VectorBuffer & cmd){
	try {
		runCommand(serial, cmd);
	} catch (...){

	}
}
void runCommandExcWait(MBot::SerialLib & serial, const MBot::SerialLib::VectorBuffer & cmd){
	runCommandExc(serial, cmd);
	Poco::Thread::sleep(250);
}

std::vector <std::string> runQuestion(MBot::SerialLib & serial,const MBot::SerialLib::VectorBuffer & cmd, std::size_t outParamsSize){

	//std::cout << "Q " << cmd;
	serial.send(cmd);
	TBS::Serial::SerialWrapper::ListBuffer buf;
	buf.push_back(0x20);
	for (std::size_t i = 0; i < outParamsSize; i++){
		buf.push_back(0x0D);
	}
	TBS::Serial::SerialWrapper::VectorBuffer response = serial.receive(buf, 50);
	//std::cout << " ANSWER: " << response << std::endl;

	std::vector <std::string> outParams;

	//parse answer
	std::string currentParam = "";
	for (std::size_t i = cmd.size(); i < response.size(); i++){
		char c = response.at(i);
		if (c != 0x0D){
			currentParam.push_back(c);
		} else {
			//std::cout << "param: " << currentParam << std::endl;
			outParams.push_back(currentParam);
			currentParam = "";
		}
	}

	if (outParams.size() != outParamsSize){
		throw Poco::Exception("Not enough params read");
	}

	//std::cout << "read done" << std::endl;
	return outParams;
}

MovementImpl::Data read2IntAnswer(MBot::SerialLib & serial, std::string cmd){
	std::vector <std::string> res = runQuestion(serial, makeCommand(cmd), 2);
	MovementImpl::Data data;
	data.left = Poco::NumberParser::parse64(res.at(0));
	data.right = Poco::NumberParser::parse64(res.at(1));
	return data;
}

void check(MBot::SerialLib & serial){
	for (int i = 0; i < 5; i++){
		runCommandExc(serial, makeCommand(""));
		try {
			runCommand(serial, makeCommand("ECHO"));
			return;
		} catch (...){

		}
		Poco::Thread::sleep(100);
	}
	runCommand(serial, makeCommand("ECHO"));
}

void init(MBot::SerialLib & serial){
	runCommandExc(serial, makeCommand("ECHO"));

	runCommandExc(serial, makeCommand("BAUD9600"));

	runCommandExc(serial,  makeCommand("WAKE"));
	runCommandExc(serial,  makeCommand("OCHN(RS2,0,N,9600,1,8,C"));

	runCommandExc(serial, makeCommand("ECHO"));
	runCommandExc(serial, makeCommand("END"));

	runCommandExcWait(serial, makeCommand("SADDR0"));
	runCommandExcWait(serial, makeCommand("ECHO_OFF"));

	runCommandExcWait(serial, makeCommand("SADDR1"));
	runCommandExcWait(serial, makeCommand("ECHO", 1));
	runCommandExcWait(serial, makeCommand("SLEEP", 1));

	runCommandExcWait(serial, makeCommand("SADDR2"));
	runCommandExcWait(serial, makeCommand("ECHO", 2));
	runCommandExcWait(serial, makeCommand("SLEEP", 2));

	runCommandExcWait(serial, makeCommand("WAKE"));

	check(serial);

	//claer error flags
	runCommand(serial, makeCommand("EIGN(W,0)"));
	runCommand(serial, makeCommand("EIGN(2)"));
	runCommand(serial, makeCommand("EIGN(3)"));

	runCommand(serial, makeCommand("ZS"));

	runCommand(serial,  makeCommand("PRT=0", 1));
	runCommand(serial,  makeCommand("PRT=0", 2));

	//important - position mode
	runCommand(serial, makeCommand("MP"));
}
MovementImpl::MovementImpl(int port, int br) : serial(port, br) {
	init(serial);
}

MovementImpl::~MovementImpl() {
	try {
		this->go(0,0);
	} catch (...){

	}
}

void MovementImpl::go(Poco::Int64 left, Poco::Int64 right){
	//acceleration
	runCommand(serial,  makeCommand("ADT=30"));
	runCommand(serial,  makeCommand("DT=150"));
	//velocity
	runCommand(serial,  makeCommand("VT=" + Poco::NumberFormatter::format(left), 1));
	runCommand(serial,  makeCommand("VT=" + Poco::NumberFormatter::format(-right), 2));

	int stopAfter = 8;

	runCommand(serial,  makeCommand("PRT=" + Poco::NumberFormatter::format(left/stopAfter), 1));
	runCommand(serial,  makeCommand("PRT=" + Poco::NumberFormatter::format(-right/stopAfter), 2));

	runCommand(serial, makeCommand("G"));
}

void MovementImpl::stop(){
	runCommand(serial, makeCommand("S"));

	runCommand(serial,  makeCommand("PRT=0", 1));
	runCommand(serial,  makeCommand("PRT=0", 2));
}


void MovementImpl::setPosition(Data position){

	runCommand(serial, makeCommand("S"));

	runCommand(serial,  makeCommand("PRT=0", 1));
	runCommand(serial,  makeCommand("PRT=0", 2));

	runCommand(serial,  makeCommand("O=" + Poco::NumberFormatter::format(position.left), 1));
	runCommand(serial,  makeCommand("O=" + Poco::NumberFormatter::format(position.right), 2));
}

MovementImpl::Data MovementImpl::getPosition(){
	return read2IntAnswer(serial, "RPA");
}
MovementImpl::Data MovementImpl::getVelocity(){
	return read2IntAnswer(serial, "RVA");
}


} /* namespace MBot */
