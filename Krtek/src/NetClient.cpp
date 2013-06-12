/*
 * NetClient.cpp
 *
 *  Created on: 28.3.2013
 *      Author: JV
 */

#include "NetClient.h"
#include <Poco/AutoPtr.h>

#include <iostream>
namespace TBS {

	void CanFrame::set(Poco::UInt8 * rawData, int index) {

			this->id = (Poco::UInt32) ((rawData[index + 0]) | (rawData[index + 1] << 8) | (rawData[index + 2] << 16) | (rawData[index + 3] << 24));
			this->rtr = rawData[index + 4];
			this->dlc = rawData[index + 5];
			this->data[0] = rawData[index + 6];
			this->data[1] = rawData[index + 7];
			this->data[2] = rawData[index + 8];
			this->data[3] = rawData[index + 9];
			this->data[4] = rawData[index + 10];
			this->data[5] = rawData[index + 11];
			this->data[6] = rawData[index + 12];
			this->data[7] = rawData[index + 13];

			this->time_stamp = (Poco::UInt16) ((rawData[index + 14] << 0) | (rawData[index + 15] << 8));
		}

		void CanFrame::get(Poco::UInt8 * rawData, int index) const {
			rawData[index++] = (Poco::UInt8) this->id;
			rawData[index++] = (Poco::UInt8) ((this->id) >> 8);
			rawData[index++] = (Poco::UInt8) ((this->id) >> 16);
			rawData[index++] = (Poco::UInt8) ((this->id) >> 24);

			rawData[index++] = (Poco::UInt8) this->rtr;
			rawData[index++] = (Poco::UInt8) this->dlc;

			rawData[index++] = (Poco::UInt8) (this->data[0]);
			rawData[index++] = (Poco::UInt8) (this->data[1]);
			rawData[index++] = (Poco::UInt8) (this->data[2]);
			rawData[index++] = (Poco::UInt8) (this->data[3]);
			rawData[index++] = (Poco::UInt8) (this->data[4]);
			rawData[index++] = (Poco::UInt8) (this->data[5]);
			rawData[index++] = (Poco::UInt8) (this->data[6]);
			rawData[index++] = (Poco::UInt8) (this->data[7]);
			rawData[index++] = (Poco::UInt8) ((this->time_stamp));
			rawData[index++] = (Poco::UInt8) ((this->time_stamp) >> 8);

		}

	NetClient::NetClient(std::string ip, int port) :
			socket(Poco::Net::SocketAddress(ip, port)) {

		modulo = 0;
	}

	NetClient::~NetClient() {
		std::cout << "NetClient destruct" << std::endl;
	}

	void NetClient::send(const CanFrame::Queue & queue) {
		int index = 0;
		int numFrames = queue.size();
		if (!numFrames) return;

		int size = (numFrames * (CanFrame::frameLength + 2));
		Poco::UInt8 data[size];

		for (CanFrame::Queue::const_iterator i = queue.begin(); i != queue.end(); i++){

			data[index++] = DataPacket;
			data[index++] = CanFrame::frameLength;


			i->get(data, index);
			index +=  CanFrame::frameLength;

		}

		socket.sendBytes(data, size);
	}

	void NetClient::receive(CanFrame::Queue & queue) {
		try {
			int frameSize = CanFrame::frameLength;

			int index = 0;
			Poco::UInt8 command = 0;
			Poco::UInt8 counter = 0;

			Poco::UInt8 * currAddress = data + modulo;

			socket.setReceiveTimeout(5000);
			int size = socket.receiveBytes(currAddress, sizeof(data) - modulo);

			while (size + modulo > index) {
				command = data[index++];
				counter = data[index++];
				if (command == DataPacket) {
					if (counter != frameSize) {
						throw Poco::Exception("bad size of DataPacket");
					}
					CanFrame frame;
					frame.set(data, index);

					queue.push_back(frame);

					index += CanFrame::frameLength;

				} else if ((command == ConfigPacket) || (command == CommandPacket)) {
					index += 8;
				} else {
					//Console.WriteLine("Network data stream contains corrupted data.");
					//throw new System.ArgumentException("Network data stream contains corrupted data.", "");
				}
			}
		} catch (Poco::TimeoutException & e){

		}
	}


} /* namespace TBS */
