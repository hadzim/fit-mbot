/*
 * BoardSensors.cpp
 *
 *  Created on: Jan 31, 2013
 *      Author: root
 */

#include "HALService.h"
#include <iostream>
#include <Poco/Delegate.h>
#include "Poco/Thread.h"

#include "Real/HALFactory.h"
#include "TBS/Log.h"
#include "HAL/API/BioRadarSvc_DBus.h"

namespace HAL {



HALService::HALService() : help(false), virtualMode(false) {
	setUnixOptions(true);
}

HALService::~HALService() {

}

void HALService::defineOptions(Poco::Util::OptionSet& options) {
		Application::defineOptions(options);

		options.addOption(
				Poco::Util::Option("help", "h", "display help information").required(
						false).repeatable(false).argument("name=value").callback(
						Poco::Util::OptionCallback<HALService>(this,
								&HALService::handleHelp)));
		options.addOption(
				Poco::Util::Option("mode", "m",
						"virtual or real mode").required(true).repeatable(
						false).argument("name=value").callback(
						Poco::Util::OptionCallback<HALService>(this,
								&HALService::handleMode)));

	}

	void HALService::displayHelp() {
		help = true;
		Poco::Util::HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("HAL.BioRadar server.");
		helpFormatter.format(std::cout);
	}
	void HALService::handleHelp(const std::string& name, const std::string& value) {
		displayHelp();
		stopOptionsProcessing();
	}
	void HALService::handleMode(const std::string& name, const std::string& value) {
		std::cout << "mode: " << name << " val " << value << std::endl;
		virtualMode = value == "virtual";
	}


int HALService::main(const std::vector<std::string>& args) {
	if (help){
		return EXIT_OK;
	}

	TBS::initLogs("hal", 4);

	std::cout << "-----------" << std::endl;
	std::cout << "HAL Service" << std::endl;
	std::cout << "-----------" << std::endl;

	std::cout << std::endl;

	{
		MBot::IHALFactory::Ptr f;

		if (virtualMode){
			throw Poco::Exception("Cannot run virtual mode - not implemented");
			//f = new MBot::VirtualHALFactory();
		} else {
			f = new MBot::HALFactory();
		}

		HAL::API::BioRadar::DBus::Server::Ptr srv = new HAL::API::BioRadar::DBus::Server();
		{
			TBS::Services::IServer::Ptr bioRadar = srv->createBioRadar(f->createBioRadar());
			waitForTerminationRequest();
		}
	}

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "-----------" << std::endl;
	std::cout << "HAL Service finished" << std::endl;
	std::cout << "-----------" << std::endl;

	return EXIT_OK;
}

} /* namespace BB */
