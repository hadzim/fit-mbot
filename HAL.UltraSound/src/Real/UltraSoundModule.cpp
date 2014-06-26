/*
 * UltraSoundModule.cpp
 *
 *  Created on: Jun 26, 2014
 *      Author: dron
 */

#include <Real/UltraSoundModule.h>

namespace MBot {

UltraSoundModule::UltraSoundModule(int port, int br) :
		serial(port, br) {
	}

void UltraSoundModule::connect() {
		this->send(this->connectCmd());
		std::vector<VectorBuffer> b = this->read(1);
		if (b.at(0) != this->connectAnswer()) {
			throw Poco::Exception("Cannot connect");
		}
	}

void UltraSoundModule::activate() {
	this->send(this->activateCmd());
}
std::vector<int> UltraSoundModule::readData() {
	this->send(this->read1to8Cmd());
	std::vector<VectorBuffer> b = this->read(2);
	if (b.at(0).at(0) != CMD_GET_DATA_1TO8) {
		throw Poco::Exception("Bad header");
	}
	if (b.at(0).at(1) != 0) {
		throw Poco::Exception("Bad first byte");
	}

	std::vector<int> data;
	data.push_back((int) b.at(0).at(2));
	data.push_back((int) b.at(0).at(3));
	data.push_back((int) b.at(0).at(4));
	data.push_back((int) b.at(0).at(5));

	return data;
}

UltraSoundModule::VectorBuffer UltraSoundModule::connectCmd() {
	VectorBuffer buf;
	buf.push_back(CMD_CONNECT);
	return buf;
}
UltraSoundModule::VectorBuffer UltraSoundModule::connectAnswer() {
	VectorBuffer buf;
	buf.push_back(CMD_CONNECT);
	for (DataByte i = 1; i <= 7; i++) {
		buf.push_back(i);
	}
	return buf;
}

UltraSoundModule::VectorBuffer UltraSoundModule::activateCmd() {
	VectorBuffer buf;
	buf.push_back(CMD_SET_CHANNEL_ACTIVE);
	//all sensors are active
	buf.push_back(0xFF);
	buf.push_back(0x00);
	return buf;
}

UltraSoundModule::VectorBuffer UltraSoundModule::read1to8Cmd() {
	VectorBuffer buf;
	buf.push_back(CMD_GET_DATA_1TO8);
	return buf;
}

void UltraSoundModule::send(const VectorBuffer & buffer) {
	SerialLib::VectorBuffer cpy;
	for (int i = 0; i < buffer.size(); i++) {
		cpy.push_back((char) buffer[i]);
	}
	int num = 8 - buffer.size();
	for (int i = 0; i < num; i++) {
		cpy.push_back(0);
	}
	serial.send(cpy);
}

std::vector<UltraSoundModule::VectorBuffer> UltraSoundModule::read(
		int countOfMessages) {
	try {
		static const int OneCmdLength = 11;
		int bytes = OneCmdLength * countOfMessages;
		SerialLib::VectorBuffer buffer = serial.receive(1000, bytes);

		std::vector<VectorBuffer> final;
		for (int i = 0; i < countOfMessages; i++) {

			int startIndex = i * OneCmdLength;

			if ((unsigned char) (buffer.at(startIndex)) != 0xFF) {
				throw Poco::Exception("Wrong first byte");
			}

			VectorBuffer data;
			for (int i = startIndex + 1; i < startIndex + 8 + 1; i++) {
				data.push_back((unsigned char) buffer.at(i));
			}

			if (data.size() != 8) {
				throw Poco::Exception("Wrong buffer length");
			}

			unsigned int chsum = getCheckSum(&data.at(0), 8);

			unsigned int val = 0;
			unsigned char c1 = (unsigned char) buffer.at(startIndex + 9);
			unsigned char c2 = (unsigned char) buffer.at(startIndex + 10);

			val = (c1 << 8) | c2;
			if (val != chsum) {
				std::cout << "expected checksum: " << chsum << std::endl;
				std::cout << "received checksum: " << val << std::endl;
				throw Poco::Exception("Bad checksum");
			}

			final.push_back(data);
		}
		return final;
	} catch (std::exception & e) {
		LERROR("US")<< "bad read" << LE;
			throw;
		}
	}

unsigned int UltraSoundModule::getCheckSum(unsigned char* c, int iNumBytes) {

	unsigned int uCrc16 = 0;
	unsigned char ucData[] = { 0, 0 };
	while (iNumBytes--) {
		ucData[1] = ucData[0];
		ucData[0] = *c++;
		if (uCrc16 & 0x8000) {
			uCrc16 = (uCrc16 & 0x7fff) << 1;
			uCrc16 ^= 0x1021; //generator polynom
		} else {
			uCrc16 <<= 1;
		}
		uCrc16 ^= (unsigned int) (ucData[0])
				| ((unsigned int) (ucData[1]) << 8);
	}
	return uCrc16;
}

} /* namespace MBot */
