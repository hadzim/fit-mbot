/*
 * NetChannel.h
 *
 *  Created on: 28.3.2013
 *      Author: JV
 */

#ifndef NETCHANNEL_H_
#define NETCHANNEL_H_

#include "TBS/Robo/RoboCan/Communicaton/IChannel.h"
#include "TBS/Thread/NotificationBasedRunnable.h"
#include "TBS/Robo/RoboCan/Communicaton/CanMessage.h"
#include <Poco/Notification.h>
#include <Poco/AutoPtr.h>
#include <Poco/Runnable.h>
#include <Poco/Thread.h>
#include <Poco/Types.h>
#include <deque>

namespace TBS {





	class NetChannel : public Poco::Runnable, public TBS::Robo::RoboCan::IChannel {
			typedef std::deque <TBS::Robo::RoboCan::CanMessage> CanMessages;
		public:
			NetChannel();
			virtual ~NetChannel();

			virtual void sendCanMessage(const TBS::Robo::RoboCan::CanMessage & canMessage);
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

} /* namespace TBS */
#endif /* NETCHANNEL_H_ */
