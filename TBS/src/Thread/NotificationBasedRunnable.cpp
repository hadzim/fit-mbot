/*
 * NotificationBasedRunnable.cpp
 *
 *  Created on: May 31, 2012
 *      Author: root
 */

#include "TBS/Thread/NotificationBasedRunnable.h"
#include <iostream>
#include "Poco/Timestamp.h"

namespace TBS {

	class QuitNotification: public Poco::Notification {

		public:
			typedef Poco::AutoPtr<QuitNotification> Ptr;

			QuitNotification() {

			}
			virtual ~QuitNotification() {

			}

			virtual std::string name() const {
				return "QuitNotification";
			}

	};

	NotificationBasedRunnable::NotificationBasedRunnable(std::string threadName) :
			thread(threadName), stopped(false) {

	}

	void NotificationBasedRunnable::stop() {
		Poco::Mutex::ScopedLock l(m);
		this->stopped = true;
		if (this->thread.isRunning()) {
			this->queue.enqueueUrgentNotification(QuitNotification::Ptr(new QuitNotification()));
			thread.join();
		} else {

		}
	}
	int NotificationBasedRunnable::queueSize() {
		return this->queue.size();
	}
	NotificationBasedRunnable::~NotificationBasedRunnable() {
		this->stop();
	}

	bool NotificationBasedRunnable::isBgThread() {
		return Poco::Thread::currentTid() == thread.tid();
	}

	void NotificationBasedRunnable::enqueueNotification(Poco::Notification::Ptr notification) {
		{
			Poco::Mutex::ScopedLock l(m);

			if (stopped) {
				return;
			}

			if (!this->thread.isRunning()) {
				this->thread.start(*this);
			}
		}
		this->queue.enqueueNotification(notification);
	}

	void NotificationBasedRunnable::run() {

		try {
			Poco::Notification::Ptr pNf(queue.waitDequeueNotification());

			while (pNf) {

				//quit notification
				QuitNotification::Ptr pQuitNf = pNf.cast<QuitNotification>();
				if (pQuitNf) {
					break;
				}

				this->processNotification(pNf);

				pNf = queue.waitDequeueNotification();
				if (!pNf.isNull()) {
				}
			}

		} catch (Poco::Exception & e) {
			std::cerr << thread.name() << ": Worker thread finished with exception " << e.displayText() << std::endl;
		} catch (std::runtime_error & e) {
			std::cerr << thread.name() << ": Worker thread finished with std runtime exception " << e.what() << std::endl;
		} catch (std::exception & e) {
			std::cerr << thread.name() << ": Worker thread finished with std exception " << e.what() << std::endl;
		} catch (...) {
			std::cerr << thread.name() << ": Worker thread finished with unknown exception" << std::endl;
		}

	}

} /* namespace TBS */
