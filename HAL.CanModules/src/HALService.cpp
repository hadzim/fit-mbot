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
#include "HAL/API/BioRadarSvc_Json.h"
#include "HAL/API/CameraSvc_Json.h"
#include "HAL/API/ManipulatorSvc_Json.h"
#include "HAL/API/api.h"

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
	std::cout << "HAL Service json" << std::endl;
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

		TBS::Services::JsonServerParams bp(HAL::API::Communication::BioRadarPort);
		HAL::API::BioRadar::Json::Server::Ptr bioRadarSrv = HAL::API::BioRadar::Json::Server::createJsonServer(bp);

		TBS::Services::JsonServerParams cp(HAL::API::Communication::CameraPort);
		HAL::API::Camera::Json::Server::Ptr cameraSrv = HAL::API::Camera::Json::Server::createJsonServer(cp);

		TBS::Services::JsonServerParams ma(HAL::API::Communication::ManipulatorPort);
		HAL::API::Manipulator::Json::Server::Ptr manipSrv = HAL::API::Manipulator::Json::Server::createJsonServer(ma);
		{
			TBS::Services::IServer::Ptr bioRadar = bioRadarSrv->createBioRadar(f->createBioRadar());
			TBS::Services::IServer::Ptr camera = cameraSrv->createCamera(f->createCamera());
			TBS::Services::IServer::Ptr manip = manipSrv->createManipulator(f->createManipulator());
			bioRadarSrv->start();
			cameraSrv->start();
			manipSrv->start();
			waitForTerminationRequest();
			bioRadarSrv->stop();
			cameraSrv->stop();
			manipSrv->stop();
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
