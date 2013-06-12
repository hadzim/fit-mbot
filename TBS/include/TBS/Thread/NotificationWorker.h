/*
 * NotificationWorker.h
 *
 *  Created on: 30.11.2011
 *      Author: Honza
 */

#ifndef TBS_TSERIES_NOTIFICATIONWORKER_H_
#define TBS_TSERIES_NOTIFICATIONWORKER_H_

#include <Poco/Notification.h>
#include <Poco/NotificationCenter.h>
#include <Poco/SharedPtr.h>
#include "TBS/Thread/NotificationBasedRunnable.h"
#include <Poco/NObserver.h>
#include <list>


namespace TBS {


		class NotificationWorker: public NotificationBasedRunnable {

			public:

				typedef Poco::SharedPtr<NotificationWorker> Ptr;

				NotificationWorker(std::string name);
				virtual ~NotificationWorker();

				virtual void addObserver(const Poco::AbstractObserver& observer);
				virtual void removeObserver(const Poco::AbstractObserver& observer);

				virtual void postNotification(Poco::Notification::Ptr pNotification);

			protected:
				void processNotification(Poco::Notification::Ptr notification);

			private:

				Poco::NotificationCenter center;
				std::string name;
		};

		class NotificationObserver {

			public:
				NotificationObserver();
				~NotificationObserver();

				template<class Holder, class Notif>
				void init(NotificationWorker::Ptr nw, Holder& object, void(Holder::*method)(const Poco::AutoPtr<Notif> &)) {
						this->nw = nw;
						Poco::NObserver<Holder, Notif> o(object, method);
						this->set(o.clone());
				}
				void reset();
			private:
				void set(Poco::AbstractObserver * o);

			private:
				Poco::AbstractObserver * observer;
				NotificationWorker::Ptr nw;
		};

		class NotificationObservers {
				typedef std::list<Poco::AbstractObserver * > Observers;
			public:


				NotificationObservers(NotificationWorker::Ptr nw);
				~NotificationObservers();

				template<class Holder, class Notif>
				void add(Holder& object, void(Holder::*method)(const Poco::AutoPtr<Notif> &)) {
					Poco::NObserver<Holder, Notif> o(object, method);
					this->addInternally(o.clone());
				}
				void clear();
			private:
				void addInternally(Poco::AbstractObserver * o);
			private:
				Observers observers;
				NotificationWorker::Ptr nw;
		};


}

#endif /* NOTIFICATIONWORKER_H_ */
