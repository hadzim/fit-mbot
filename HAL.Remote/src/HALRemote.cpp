/*
 * BoardSensors.cpp
 *
 *  Created on: Jan 31, 2013
 *      Author: root
 */

#include "HALRemote.h"
#include <iostream>
#include <Poco/Delegate.h>
#include "Poco/Thread.h"

#include "HAL/API/MovementSvc_DBus.h"
#include "HAL/API/RemoteSvc_Json.h"

#include "HAL/API/Remote.h"

namespace HAL {

class RemoteJsonServer: public HAL::Remote::IMovement {
public:
	RemoteJsonServer() {
		client = new HAL::API::DBus::Client();
	}
	virtual void Move(const double & speedLeft, const double & speedRight) {
		client->Movement().Move(speedLeft, speedRight);
	}

	virtual void Stop() {
		client->Movement().Stop();
	}
private:
	HAL::API::DBus::Client::Ptr client;

};

RemoteProvider::RemoteProvider() {

}

RemoteProvider::~RemoteProvider() {

}

int RemoteProvider::main(const std::vector<std::string>& args) {

	std::cout << "-------------------" << std::endl;
	std::cout << "HAL Observer Starts" << std::endl;
	std::cout << "-------------------" << std::endl;

	std::cout << std::endl;

	{

		{
			RemoteJsonServer::Ptr jsonSrv = new RemoteJsonServer();
			{
				TBS::Services::JsonServerChannel ch(8080);

				HAL::Remote::Json::Server server(ch);
				{
					TBS::Services::IServer::Ptr srv = server.createMovement(jsonSrv);
					server.start();
					waitForTerminationRequest();
					server.stop();
				}

			}

		}
	}

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "------------------" << std::endl;
	std::cout << "HAL Observer Stops" << std::endl;
	std::cout << "------------------" << std::endl;

	return EXIT_OK;
}

} /* namespace BB */
