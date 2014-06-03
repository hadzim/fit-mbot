/*
 * SocketCan.h
 *
 *  Created on: Jun 3, 2014
 *      Author: dron
 */

#ifndef SOCKETCAN_H_
#define SOCKETCAN_H_
#include <RoboCan/Communicaton/usb/CANFrame.h>

namespace can {

class SocketCan {

public:
    SocketCan(int netId);
    ~SocketCan();

    /* ICanBus */


    void canRead(CANFrame::PtrList &msgs);

    void canWrite(CANFrame::Ptr msgs);

private:
    int socketHandler;
};

} /* namespace can */

#endif /* SOCKETCAN_H_ */
