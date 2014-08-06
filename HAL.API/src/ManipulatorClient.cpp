/*
 * ManipulatorClient.cpp
 *
 *  Created on: Jun 16, 2014
 *      Author: dron
 */

#include <HAL/API/ManipulatorClient.h>
#include "HAL/API/api.h"
namespace HAL {
	namespace API {

		ManipulatorClient::ManipulatorClient(int pollingFrequencyMs, std::string endpoint) :
				t("ManipulatorBg"), pollingFreq(pollingFrequencyMs), finished(false) {
			TBS::Services::JsonClientParams params(endpoint, Communication::ManipulatorPort, TBS::Services::JsonClientParams::JsonHttp);
			client = new Manipulator::Json::Client(params);
			t.start(*this);
		}

		ManipulatorClient::~ManipulatorClient() {
			finished = true;
			t.join();
		}

		HAL::API::Manipulator::IManipulator & ManipulatorClient::Manipulator() {
			return client->Manipulator();
		}

		void ManipulatorClient::run() {
			while (!finished) {

				Poco::Thread::sleep (pollingFreq);

				if (finished)
					break;

				HAL::API::Manipulator::MotorInfo rotation, j1, j2, holder;

				client->Manipulator().GetStatus(rotation, j1, j2, holder);
/*
				Manipulator::IManipulator::StatusChangedArg a;
				a.posLeft = posL;
				a.posRight = posR;
				a.speedLeft = speedL;
				a.speedRight = speedR;

				this->Manipulator().StatusChanged(this, a);
				*/
			}
		}

	} /* namespace API */
} /* namespace HAL */
