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
#ifndef NETCHANNEL_H_
#define NETCHANNEL_H_

#include "TBS/Robo/RoboCan/Communicaton/IChannel.h"
#include "TBS/NotificationBasedRunnable.h"
#include "TBS/Robo/RoboCan/Communicaton/CanMessage.h"
#include <Poco/Notification.h>
#include <Poco/AutoPtr.h>
#include <Poco/Runnable.h>
#include <Poco/Thread.h>
#include <Poco/Types.h>
#include <deque>

namespace TBS {
namespace Robo {
namespace RoboCan {

class NetChannel: public Poco::Runnable, public TBS::Robo::RoboCan::IChannel {
	typedef std::deque<TBS::Robo::RoboCan::CanMessage> CanMessages;
public:
	NetChannel();
	virtual ~NetChannel();

	virtual void sendCanMessage(
			const TBS::Robo::RoboCan::CanMessage & canMessage);
protected:
	virtual void run();
	//virtual void processNotification(Poco::Notification::Ptr notification);
private:
	void read(CanMessages & messages);
private:
	Poco::Thread thread;
	bool stopThread;

	CanMessages canList;
	Poco::Mutex m;

};

}
}
}
#endif /* NETCHANNEL_H_ */
