/*
 * DummyChannel.h
 *
 *  Created on: 7.3.2013
 *      Author: JV
 */

#ifndef DUMMYCHANNEL_H_
#define DUMMYCHANNEL_H_
#include "TBS/Robo/RoboCan/Communicaton/IChannel.h"
#include "TBS/NotificationBasedRunnable.h"
#include "TBS/Robo/RoboCan/Communicaton/CanMessage.h"


	class Ntf : public Poco::Notification {
		public:
			typedef Poco::AutoPtr<Ntf> Ptr;
			TBS::Robo::RoboCan::CanMessage message;
	};

	class DummyChannel : public TBS::NotificationBasedRunnable, public TBS::Robo::RoboCan::IChannel {
		public:
			DummyChannel();
			virtual ~DummyChannel();

			virtual void sendCanMessage(const TBS::Robo::RoboCan::CanMessage & canMessage);
		protected:
			virtual void processNotification(Poco::Notification::Ptr notification);

	};


#endif /* DUMMYCHANNEL_H_ */
