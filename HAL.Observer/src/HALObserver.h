/*
 * BoardSensors.h
 *
 *  Created on: Jan 31, 2013
 *      Author: root
 */

#ifndef HALObserver_H_
#define HALObserver_H_
#include "Poco/Util/ServerApplication.h"
#include "Poco/Timer.h"
#include "TBS/SafeTimer.h"

namespace HAL {

	class HALObserver: public Poco::Util::ServerApplication {

		public:
			typedef Poco::SharedPtr<HALObserver> Ptr;
			HALObserver();
			virtual ~HALObserver();

		protected:

			int main(const std::vector<std::string>& args);

		private:

	};

} /* namespace BB */
#endif /* BoardSensors_H_ */
