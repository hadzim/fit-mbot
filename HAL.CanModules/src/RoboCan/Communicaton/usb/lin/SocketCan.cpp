/*
 * SocketCan.cpp
 *
 *  Created on: Jun 3, 2014
 *      Author: dron
 */
#include "TBS/Log.h"

#ifndef _WIN32

#include "SocketCan.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/* At time of writing, these constants are not defined in the headers */
#ifndef PF_CAN
#define PF_CAN 29
#endif

#ifndef AF_CAN
#define AF_CAN PF_CAN
#endif

#define SOCK_DEBUG 0

namespace can {

const int TX_QUEUE_SIZE = 2047;
const int RX_QUEUE_SIZE = 2047;

SocketCan::SocketCan(int netId) {
	int canTxQueue = TX_QUEUE_SIZE;
	int canRxQueue = RX_QUEUE_SIZE;
	int txTimeout = 500;
	int rxTimeout = 500;

	int so_timestamping_flags = 0;
	/* Create the socket */
	if ((socketHandler = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		throw Poco::Exception("Cannot create can socket");
	}

	/* Locate the interface you wish to use */
	struct ifreq ifr;
	sprintf(ifr.ifr_name, "can%d", netId);
	LNOTICE("INFO") << "open interface: " << ifr.ifr_name << LE;
	int resi = ioctl(socketHandler, SIOCGIFINDEX, &ifr); // ifr.ifr_ifindex gets filled with that device's index
	if (resi == -1){
		throw Poco::Exception("Cannot create can socket - ioctl");
	}

	/* Select that CAN interface, and bind the socket to it. */
	struct sockaddr_can addr;
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	int resb = bind(socketHandler, (struct sockaddr*) &addr, sizeof(addr));
	if (resb == -1){
		throw Poco::Exception("Cannot create can socket - bind");
	}
	int flags;
	if (-1 == (flags = fcntl(socketHandler, F_GETFL, 0)))
		flags = 0;
	int resf = fcntl(socketHandler, F_SETFL, flags | O_NONBLOCK);
	if (resf == -1){
		throw Poco::Exception("Cannot create can socket - fcntl");
	}
}

SocketCan::~SocketCan() {

}

void SocketCan::canRead(CANFrame::PtrList &msgs) {

	int s = sizeof(can_frame);
	char buffer[sizeof(can_frame)];
	int readbytes = read(this->socketHandler, buffer, s);
	if (readbytes == -1) {
		int nerr = errno;
		if (nerr == EAGAIN){
			return;
		} else {
			LWARNING("Can") << "read: " << readbytes << " expected: " << s << " failed with: " << nerr << LE;
			throw Poco::Exception("can read failed");
		}
	}
	if (readbytes == 0) {
		return;
	}
	if (readbytes != s) {
		LWARNING("Can") << "read: " << readbytes << " expected: " << s << LE;
		throw Poco::Exception("can read size missmatch");
	}
	std::vector<Poco::UInt8> bytes(s, 0);
	for (int i = 0; i < s; i++) {
		bytes[i] = buffer[i];
	}

	msgs.push_back(new CANFrame(bytes));
}

void SocketCan::canWrite(CANFrame::Ptr frame) {


	can_frame f;
	f.can_dlc = frame->DLC();
	f.can_id = frame->getFrameID();
	frame->initDataBuffer(f.data, 8);


	int ret = write(this->socketHandler, &f, sizeof(can_frame));
	if (ret == -1){
		int nerr = errno;
		LWARNING("Can") << "can write failed with: " << nerr << LE;
		throw Poco::Exception("can read failed");
	}
	if (ret != sizeof(can_frame)) {
		throw Poco::Exception("Could not write message");
	}
}

#endif

} /* namespace can */
