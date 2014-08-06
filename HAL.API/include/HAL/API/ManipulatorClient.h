/*
 * ManipulatorClient.h
 *
 *  Created on: Jun 16, 2014
 *      Author: dron
 */

#ifndef ManipulatorCLIENT_H_
#define ManipulatorCLIENT_H_
#include "Poco/Runnable.h"
#include "ManipulatorSvc_Json.h"
#include <TBS/Services/Services.h>

namespace HAL {
	namespace API {

		class GEN_SERVICE_API ManipulatorClient: private Poco::Runnable {
			public:

				typedef Poco::SharedPtr<ManipulatorClient> Ptr;

				HAL::API::Manipulator::IManipulator & Manipulator();

				ManipulatorClient(int pollingFrequencyMs = 50, std::string endpoint = "localhost");
				~ManipulatorClient();
			private:
				void run();
			private:
				Manipulator::Json::Client::Ptr client;
				Poco::Thread t;
				int pollingFreq;
				volatile bool finished;

		};

	}
/* namespace API */
} /* namespace HAL */

#endif /* ManipulatorCLIENT_H_ */
