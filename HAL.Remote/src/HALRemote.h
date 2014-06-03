/*
 * BoardSensors.h
 *
 *  Created on: Jan 31, 2013
 *      Author: root
 */

#ifndef RemoteProvider_H_
#define RemoteProvider_H_
#include <Poco/SharedPtr.h>
#include "Poco/Util/ServerApplication.h"
#include "Poco/Timer.h"
#include "TBS/SafeTimer.h"

namespace HAL {

	class RemoteProvider: public Poco::Util::ServerApplication {

		public:
			typedef Poco::SharedPtr<RemoteProvider> Ptr;
			RemoteProvider();
			virtual ~RemoteProvider();

		protected:

			int main(const std::vector<std::string>& args);

		private:

	};

} /* namespace BB */
#endif /* BoardSensors_H_ */
