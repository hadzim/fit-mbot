/*
 * MovementClient.cpp
 *
 *  Created on: Jun 16, 2014
 *      Author: dron
 */

#include <HAL/API/MovementClient.h>
#include "HAL/API/api.h"
namespace HAL {
namespace API {

MovementClient::MovementClient(int pollingFrequencyMs, std::string endpoint)
		: t("MovementBg"), pollingFreq(pollingFrequencyMs), finished(false) {
	TBS::Services::JsonClientParams params(endpoint, Communication::MovementPort, TBS::Services::JsonClientParams::JsonHttp);
	client = new Movement::Json::Client(params);
	t.start(*this);
}

MovementClient::~MovementClient() {
	finished = true;
	t.join();
}

HAL::API::Movement::IMovement & MovementClient::Movement(){
	return client->Movement();
}

void MovementClient::run(){
	while (!finished){

		Poco::Thread::sleep(pollingFreq);

		if (finished) break;

		double speedL, speedR;
		Poco::Int64 posL, posR;
		client->Movement().GetStatus(speedL, speedR, posL, posR);

		Movement::IMovement::StatusChangedArg a;
		a.posLeft = posL;
		a.posRight = posR;
		a.speedLeft = speedL;
		a.speedRight = speedR;

		this->Movement().StatusChanged(this, a);
	}
}

} /* namespace API */
} /* namespace HAL */
