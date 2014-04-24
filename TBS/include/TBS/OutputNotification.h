/*
 * NotificationWorker.h
 *
 *  Created on: 30.11.2011
 *      Author: Honza
 */

#ifndef TSUNOTIFICATIONWORKER_H_
#define TSUNOTIFICATIONWORKER_H_
#include "Poco/Runnable.h"
#include <Poco/Observer.h>
#include <Poco/Notification.h>
#include <Poco/Thread.h>
#include <Poco/NotificationCenter.h>
#include <Poco/NotificationQueue.h>
#include <Poco/SharedPtr.h>
#include <Poco/BasicEvent.h>
#include "TBS/Command.h"

namespace TBS {

	template<class Argument>
	class OutputEventCommand: public TBS::ICommand {
		public:
			OutputEventCommand(void * object, Poco::BasicEvent<Argument> & event, Argument & value) :
					ICommand("OutputEvent"), object(object), event(event), value(value) {
			}
			virtual void run() {
				event.notify(object, value);
			}
		private:
			void * object;
			Poco::BasicEvent<Argument> & event;
			Argument value;

	};

}
#endif /* NOTIFICATIONWORKER_H_ */
