/*
 * ConnectionWrapper.h
 *
 *  Created on: Sep 29, 2013
 *      Author: root
 */

#ifndef _NO_DBUS

#ifndef CONNECTIONWRAPPER_H_
#define CONNECTIONWRAPPER_H_
#include <dbus-c++/connection.h>
#include <dbus-c++/debug.h>
#include <Poco/BasicEvent.h>
#include "TBS/TBSServices.h"



//DBus::debug_log = hdbg;


namespace TBS {
		namespace Services {

			class TBSSERV_API ConnectionWrapper {
				public:

				  static DBus::Connection SystemBus(DBus::Dispatcher & disp);

				  static DBus::Connection SessionBus(DBus::Dispatcher & disp);

				  static DBus::Connection ActivationBus(DBus::Dispatcher & disp);
				private:
				  static Poco::Mutex m;
			};

		} /* namespace Services */
} /* namespace TBS */
#endif /* CONNECTIONWRAPPER_H_ */

#endif
