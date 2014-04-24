/*
 * NotificationWorker.cpp
 *
 *  Created on: 30.11.2011
 *      Author: Honza
 */

#include "TBS/NotificationWorker.h"

#include <iostream>
#include "Poco/AbstractObserver.h"
#include "TBS/CommandNotification.h"
#include "Poco/Exception.h"

namespace TBS {

	class CommandObserver: public Poco::AbstractObserver {
		public:
			virtual ~CommandObserver() {
			}
			virtual void notify(Poco::Notification* pNf) const {
				CommandNotification* pCastNf = dynamic_cast<CommandNotification*>(pNf);
				if (pCastNf) {
					CommandNotification::Ptr ptr(pCastNf, true);
					pCastNf->run();

				}
			}
			virtual bool equals(const Poco::AbstractObserver& observer) const {
				const CommandObserver* pObs = dynamic_cast<const CommandObserver*>(&observer);
				return pObs;
			}
			virtual bool accepts(Poco::Notification* pNf) const {
				return dynamic_cast<CommandNotification*>(pNf) != 0;
			}
			virtual Poco::AbstractObserver* clone() const {
				return new CommandObserver();
			}
			virtual void disable() {
			}

	};

	NotificationWorker::NotificationWorker(std::string name_) :
			NotificationBasedRunnable(name_), name(name_) {

		this->addObserver(CommandObserver());

	}

	NotificationWorker::~NotificationWorker() {

		//LOG_STREAM_DEBUG << "delete worker " << this->queue.size() << LOG_STREAM_END

		this->stop();

		this->removeObserver(CommandObserver());

		//LOG_STREAM_DEBUG << "delete worker ok queue " << this->queue.size() << " observers: " << this->center.countObservers() << LOG_STREAM_END

	}

	void NotificationWorker::processNotification(Poco::Notification::Ptr notification) {
		try {
			center.postNotification(notification);
		} catch (Poco::Exception & e) {
			std::cerr << "NotificationWorker::run " << " event exception " << e.displayText() << std::endl;
		}
	}

	void NotificationWorker::addObserver(const Poco::AbstractObserver& observer) {
		this->center.addObserver(observer);
	}
	void NotificationWorker::removeObserver(const Poco::AbstractObserver& observer) {
		this->center.removeObserver(observer);
	}

	void NotificationWorker::postNotification(Poco::Notification::Ptr pNotification) {
		this->enqueueNotification(pNotification);

	}

	NotificationObserver::NotificationObserver() :
			observer(NULL) {

	}
	NotificationObserver::~NotificationObserver() {
		this->reset();
	}

	void NotificationObserver::reset() {
		if (observer) {
			this->nw->removeObserver(*this->observer);
			delete observer;
			this->observer = NULL;
		}
	}

	void NotificationObserver::set(Poco::AbstractObserver * o) {
		if (observer) {
			throw Poco::LogicException("Observer multi inicialization");
		}
		this->observer = o;
		this->nw->addObserver(*this->observer);
	}

	NotificationObservers::NotificationObservers(NotificationWorker::Ptr nw) :
			nw(nw) {

	}
	NotificationObservers::~NotificationObservers() {
		this->clear();
	}

	void NotificationObservers::addInternally(Poco::AbstractObserver * o) {
		this->nw->addObserver(*o);
		this->observers.push_back(o);
	}

	void NotificationObservers::clear() {
		for (Observers::iterator oi = observers.begin(); oi != observers.end(); oi++) {
			this->nw->removeObserver(*(*oi));
			delete *oi;
		}
		observers.clear();
	}

}

