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
#ifndef USBCHANNEL_H_
#define USBCHANNEL_H_

#include "Poco/Runnable.h"
#include "TBS/Robo/RoboCan/Communicaton/IChannel.h"
#include <deque>

class CANFrame;

namespace TBS {
namespace Robo {
namespace RoboCan {

class UsbChannel: public Poco::Runnable, public TBS::Robo::RoboCan::IChannel {
	typedef std::deque<TBS::Robo::RoboCan::CanMessage> CanMessages;
public:
	UsbChannel();
	virtual ~UsbChannel();

	virtual void sendCanMessage(
			const TBS::Robo::RoboCan::CanMessage & canMessage);
protected:
	virtual void run();
	//virtual void processNotification(Poco::Notification::Ptr notification);
private:
	void onFrame(Poco::SharedPtr<CANFrame> & f);

private:
	Poco::Thread thread;
	bool stopThread;

	CanMessages canList;
	Poco::Mutex m;

};

}
}
} /* namespace TBS */
#endif /* USBCHANNEL_H_ */
