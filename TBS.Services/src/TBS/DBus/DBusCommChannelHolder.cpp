#ifndef _NO_DBUS

#include "TBS/Services/DBus/DBusCommChannelHolder.h"
#include "TBS/Log.h"
#include <iostream>
/*
 * DBusCommChannelHolder.cpp
 *
 *  Created on: Oct 9, 2013
 *      Author: root
 */



namespace TBS {
	namespace Services {

		DBusCommChannelHolder::DBusCommChannelHolder(std::string name) :
				t("DBus" + name) {

		}

		DBusCommChannelHolder::~DBusCommChannelHolder() {
			LTRACE("DBUS") << "dbus destuct entered" << LE;
			this->stop();
			LTRACE("DBUS") << "dbus destuct after stop" << LE;
		}

		void DBusCommChannelHolder::start() {
			LTRACE("DBUS") << "dbus thread started" << LE;
			t.start(*this);
			running = true;
		}

		void DBusCommChannelHolder::stop() {
			LTRACE("DBUS") << "dbus thread stop" << LE;
			running = false;
			dispatcher_.leave();
			LTRACE("DBUS") << "dbus thread stop done" << LE;
		}

		bool DBusCommChannelHolder::isRunning() {
			return running;
		}

		void DBusCommChannelHolder::run() {
			try {
				LTRACE("DBUS") << "dbus thread started BG" << LE;
				dispatcher_.enter();
				LTRACE("DBUS") << "dbus thread finished BG" << LE;
			} catch (::DBus::Error & e){
				LERROR("DBUS") << "dbus thread started exception: " << e.message() << LE;
			}  catch (Poco::Exception & e){
				LERROR("DBUS") << "dbus thread started exception: " << e.displayText() << LE;
			} catch (std::exception & e){
				LERROR("DBUS") << "dbus thread started exception: " << e.what() << LE;
			}
		}
		::DBus::BusDispatcher & DBusCommChannelHolder::dispatcher(){
			LTRACE("DBUS") << "get dispatcher" << LE;

			return this->dispatcher_;
		}

	} /* namespace Services */
} /* namespace TBS */

#endif
