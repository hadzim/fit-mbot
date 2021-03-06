//------------------------------------------------------------------------------
//
//  Project:   VG20102014024
//             Robot for search of human beings in crushes and avalanches
//
//             Brno University of Technology
//             Faculty of Information Technology
//
//------------------------------------------------------------------------------
//
//             This project was financially supported by project
//                  VG20102014024 funds provided by MV CR.
//
//------------------------------------------------------------------------------
/*!

@file
@brief     Real or Virtual interface implementation
@authors   Jan Vana (<ivanajan@fit.vutbr.cz>)
@date      2010-2014
@note      This project was supported by project funds of the MV CR grant VG20102014024.

*/
#include "HALService.h"
#include <iostream>
#include <Poco/Delegate.h>
#include <Poco/NumberParser.h>
#include "Poco/Thread.h"

#include "HAL/API/api.h"
#include "HAL/API/MovementSvc_Json.h"
#include "Virtual/VirtualHALFactory.h"
#include "Real/HALFactory.h"
#include "TBS/Log.h"

namespace HAL {



HALService::HALService() : help(false), virtualMode(false), port(3) {
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

		options.addOption(
						Poco::Util::Option("port", "q", "movement serial port number").required(false).repeatable(false).argument("port=value").callback(
								Poco::Util::OptionCallback<HALService>(this, &HALService::handlePort)));

	}

	void HALService::displayHelp() {
		help = true;
		Poco::Util::HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("HAL server.");
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
	void HALService::handlePort(const std::string& name, const std::string& value){
		port = Poco::NumberParser::parse(value);
	}


int HALService::main(const std::vector<std::string>& args) {
	if (help){
		return EXIT_OK;
	}

	TBS::initLogs("hal", 8);

	std::cout << "-----------" << std::endl;
	std::cout << "HAL Service" << std::endl;
	std::cout << "-----------" << std::endl;

	std::cout << std::endl;

	{
		MBot::IHALFactory::Ptr f;
		if (virtualMode){
			f = new MBot::VirtualHALFactory();
		} else {
			f = new MBot::HALFactory(port);
		}

		TBS::Services::JsonServerParams p(HAL::API::Communication::MovementPort);

		HAL::API::Movement::Json::Server::Ptr srv = HAL::API::Movement::Json::Server::createJsonServer(p);
		{
			TBS::Services::IServer::Ptr movement = srv->createMovement(f->createMovement());
			srv->start();
			waitForTerminationRequest();
			srv->stop();
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
