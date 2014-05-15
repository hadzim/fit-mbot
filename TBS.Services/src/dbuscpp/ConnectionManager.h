/*
 * ConnectionManager.h
 *
 *  Created on: Jan 21, 2014
 *      Author: dron
 */

#ifndef CONNECTIONMANAGER_H_
#define CONNECTIONMANAGER_H_
#include "Poco/Mutex.h"
#include <deque>
#include <map>

namespace DBus {

	class ConnectionManager {
		public:

			typedef intptr_t PtrType;

			ConnectionManager();
			virtual ~ConnectionManager();

			bool isDeleted(PtrType ptr);
			void setAsDeleted(PtrType ptr);

			static ConnectionManager & instance();

		private:
			static Poco::Mutex globalm;
			Poco::Mutex m;
			typedef std::deque<PtrType> DeletedQueue;
			typedef std::map <PtrType, bool> Deleted;
			DeletedQueue deletedQueue;
			Deleted deleted;
	};

} /* namespace DBus */

#endif /* CONNECTIONMANAGER_H_ */
