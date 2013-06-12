/*
 * NotificationBasedRunnable.h
 *
 *  Created on: May 31, 2012
 *      Author: root
 */

#ifndef NOTIFICATIONBASEDRUNNABLE_H_
#define NOTIFICATIONBASEDRUNNABLE_H_
#include <Poco/NotificationQueue.h>
#include <Poco/Thread.h>
#include "Poco/Runnable.h"
#include <string>

namespace TBS {

		class NotificationBasedRunnable: public Poco::Runnable{
			public:
				NotificationBasedRunnable(std::string threadName);
				virtual ~NotificationBasedRunnable();

				bool isBgThread();
			protected:
				void enqueueNotification(Poco::Notification::Ptr notification);
				void run();
				virtual void processNotification(Poco::Notification::Ptr notification) = 0;
				void stop();
			protected:
				int queueSize();
			private:
				Poco::NotificationQueue queue;
				Poco::Thread thread;
				Poco::Mutex m;
				volatile bool stopped;
		};


} /* namespace TBS */
#endif /* NOTIFICATIONBASEDRUNNABLE_H_ */
