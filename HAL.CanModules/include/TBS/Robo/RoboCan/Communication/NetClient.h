//------------------------------------------------------------------------------
//
//  Project:   VG20102014024
//             Robot for search of human beings in crushes and avalanches
//
//             Brno University of Technology
//             Faculty of Information Technology
//
//------------------------------------------------------------------------------
//
//             This project was financially supported by project
//                  VG20102014024 funds provided by MV CR.
//
//------------------------------------------------------------------------------
/*!

@file
@brief     Header file
@details   Details
@authors   Jan Vana (<ivanajan@fit.vutbr.cz>)
@date      2010-2014
@note      This project was supported by project funds of the MV CR grant VG20102014024.

*/
#ifndef NETCLIENT_H_
#define NETCLIENT_H_
#include "Poco/Net/StreamSocket.h"
#include <deque>

namespace TBS {
namespace Robo {
namespace RoboCan {

class CanFrame {
public:

	typedef std::deque<CanFrame> Queue;

	Poco::UInt32 id;             // Identifier (for CAN 2.0A/CAN 2.0B)
	Poco::UInt8 rtr;            // Remote transmission request
	Poco::UInt8 dlc;            // Data length code

	Poco::UInt8 data[8];           // Data field (0 - 8 Bytes).
	Poco::UInt16 time_stamp;       // Time stamp - miliseconds from midnight

	static const Poco::UInt8 frameLength = 16;

	void set(Poco::UInt8 * rawData, int index = 0);
	void get(Poco::UInt8 * rawData, int index = 0) const;
private:

};

class NetClient {

	static const Poco::UInt8 DataPacket = 0x81;
	static const Poco::UInt8 ConfigPacket = 0x82;
	static const Poco::UInt8 CommandPacket = 0x83;

public:

	NetClient(std::string ip, int port);
	virtual ~NetClient();

	void send(const CanFrame::Queue & queue);
	void receive(CanFrame::Queue & queue);

private:
	Poco::Net::StreamSocket socket;
	int modulo;
	Poco::UInt8 data[150000];
};

}
}
}
#endif /* NETCLIENT_H_ */
