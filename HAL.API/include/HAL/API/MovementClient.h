/*
 * MovementClient.h
 *
 *  Created on: Jun 16, 2014
 *      Author: dron
 */

#ifndef MOVEMENTCLIENT_H_
#define MOVEMENTCLIENT_H_
#include "Poco/Runnable.h"
#include "MovementSvc_Json.h"
#include <TBS/Services/Services.h>

namespace HAL {
namespace API {

class GEN_SERVICE_API MovementClient : private Poco::Runnable {
public:

	typedef Poco::SharedPtr <MovementClient> Ptr;

	HAL::API::Movement::IMovement & Movement();

	MovementClient(int pollingFrequencyMs = 50, std::string endpoint = "localhost");
	~MovementClient();
private:
	void run();
private:
	Movement::Json::Client::Ptr client;
	Poco::Thread t;
	int pollingFreq;
	volatile bool finished;

};

} /* namespace API */
} /* namespace HAL */

#endif /* MOVEMENTCLIENT_H_ */
