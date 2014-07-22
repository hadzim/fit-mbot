#include "Poco/Exception.h"
#include <TBS/Serial/SerialWrapper.h>

#include <iostream>
#include "Poco/Thread.h"

typedef TBS::Serial::SerialWrapper SerialLib;

class UltraSonicModule {
	public:
		UltraSonicModule(int port, int br) :
				serial(port, br) {

		}

		enum Commands {
			CMD_CONNECT = 0, 					//Check connection
			CMD_SET_CHANNEL_ACTIVE = 1, 		// Activate channel for sending / receiving
			CMD_GET_DATA_1TO8 = 2, 				//Request data of sensors 1 to 8
			CMD_GET_DATA_9TO16 = 3, 			//Request data of sensors 1 to 8
			CMD_WRITE_PARASET = 4, 				//Upload parameter set to board (volatile)
			CMD_WRITE_PARASET_TO_EEPROM = 5, 	//Write parameter set to board's EEPROM (non-volatile)
			CMD_READ_PARASET = 6, 				//Read current parameter set
			CMD_GET_ANALOGIN = 7 				//	Read values of analog inputs
		};
		typedef unsigned char DataByte;
		typedef std::vector<DataByte> VectorBuffer;

		void connect() {
			this->send(this->connectCmd());
			std::vector<VectorBuffer> b = this->read(1);

			if (b.at(0) != this->connectAnswer()) {
				throw Poco::Exception("Cannot connect");
			}
		}

		void activate() {
			this->send(this->activateCmd());
		}
		void readData(){
			this->send(this->read1to8Cmd());
			std::vector<VectorBuffer> b = this->read(2);
			if (b.at(0).at(0) != CMD_GET_DATA_1TO8){
				throw Poco::Exception("Bad header");
			}
			if (b.at(0).at(1) != 0){
				throw Poco::Exception("Bad first byte");
			}

			std::cout << "distance1: " << (int)b.at(0).at(2) << std::endl;
			std::cout << "distance2: " << (int)b.at(0).at(3) << std::endl;
			std::cout << "distance3: " << (int)b.at(0).at(4) << std::endl;
			std::cout << "distance4: " << (int)b.at(0).at(5) << std::endl;
			//std::cout << (int)(b.at(0).at(7) & 0x03) << std::endl;
		}

		VectorBuffer connectCmd() {
			VectorBuffer buf;
			buf.push_back(CMD_CONNECT);
			return buf;
		}
		VectorBuffer connectAnswer() {
			VectorBuffer buf;
			buf.push_back(CMD_CONNECT);
			for (DataByte i = 1; i <= 7; i++) {
				buf.push_back(i);
			}
			return buf;
		}

		VectorBuffer activateCmd() {
			VectorBuffer buf;
			buf.push_back(CMD_SET_CHANNEL_ACTIVE);
			//all sensors are active
			buf.push_back(0xFF);
			buf.push_back(0x00);
			return buf;
		}

		VectorBuffer read1to8Cmd() {
			VectorBuffer buf;
			buf.push_back(CMD_GET_DATA_1TO8);
			return buf;
		}

		void send(const VectorBuffer & buffer) {
			SerialLib::VectorBuffer cpy;
			for (int i = 0; i < buffer.size(); i++){
				cpy.push_back((char)buffer[i]);
			}
			int num = 8 - buffer.size();
			for (int i = 0; i < num; i++) {
				cpy.push_back(0);
			}
			serial.send(cpy);
		}

		std::vector<VectorBuffer> read(int countOfMessages) {
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
					data.push_back((unsigned char)buffer.at(i));
				}

				if (data.size() != 8) {
					throw Poco::Exception("Wrong buffer length");
				}

				unsigned int chsum = getCheckSum(&data.at(0), 8);
				//std::cout << "expected checksum: " << chsum << std::endl;

				unsigned int val = 0;
				unsigned char c1 = (unsigned char)buffer.at(startIndex + 9);
				unsigned char c2 = (unsigned char)buffer.at(startIndex + 10);

				//std::cout << "received checksum c1: " << (int)c1 << std::endl;
				//std::cout << "received checksum c2: " << (int)c2 << std::endl;

				val = (c1 << 8) | c2;
				//std::cout << "received checksum: " << val << std::endl;
				if (val != chsum) {
					std::cout << "expected checksum: " << chsum << std::endl;
					std::cout << "received checksum: " << val << std::endl;
					throw Poco::Exception("Bad checksum");
				}

				final.push_back(data);
			}
			return final;
		}
	private:
		unsigned int getCheckSum(unsigned char* c, int iNumBytes) {

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
				uCrc16 ^= (unsigned int) (ucData[0]) | ((unsigned int) (ucData[1]) << 8);
			}
			return uCrc16;
		}

	private:
		SerialLib serial;
}
;

int main(int argc, char **argv) {
	try {
		UltraSonicModule module(10, 19200);
		module.connect();
		module.activate();

		for (int i = 0; i < 500; i++){
			module.readData();
			Poco::Thread::sleep(1000);
		}


	} catch (Poco::Exception & e) {
		std::cout << "exc: " << e.displayText() << std::endl;
	}
	return 0;
}
