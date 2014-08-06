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
#include <Poco/NumberParser.h>

namespace HAL {

	HALService::Configuration::Configuration() {
		useBioRadar = false;
		useManipulator = false;
#ifdef __WIN32__
		manipulatorJoint1Port = 3;
		manipulatorJoint2Port = 20;
#else
		manipulatorJoint1Port = 17;
		manipulatorJoint2Port = 18;
#endif
	}

	HALService::HALService() :
			help(false), virtualMode(false) {
		setUnixOptions(true);
	}

	HALService::~HALService() {

	}

	void HALService::defineOptions(Poco::Util::OptionSet& options) {
		Application::defineOptions(options);

		options.addOption(
				Poco::Util::Option("help", "h", "display help information").required(false).repeatable(false).callback(
						Poco::Util::OptionCallback<HALService>(this, &HALService::handleHelp)));

		//options.addOption(
		//		Poco::Util::Option("mode", "m", "virtual or real mode").required(true).repeatable(false)/*.argument("mode=value")*/.callback(
		//				Poco::Util::OptionCallback<HALService>(this, &HALService::handleMode)));

		options.addOption(
				Poco::Util::Option("bioradar", "b", "use bio radar").required(false).repeatable(false).argument("bioradar=value").callback(
						Poco::Util::OptionCallback<HALService>(this, &HALService::handleBioRadarEnable)));

		options.addOption(
				Poco::Util::Option("manipulator", "m", "use manipulator").required(false).repeatable(false).argument("manipulator=value").callback(
						Poco::Util::OptionCallback<HALService>(this, &HALService::handleManipulatorEnable)));

		options.addOption(
				Poco::Util::Option("port1", "q1", "manipulator serial port 1 number").required(false).repeatable(false).argument("manport1=value").callback(
						Poco::Util::OptionCallback<HALService>(this, &HALService::handleManipulatorPort1)));
		options.addOption(
				Poco::Util::Option("port2", "q2", "manipulator serial port 2 number").required(false).repeatable(false).argument("manport2=value").callback(
						Poco::Util::OptionCallback<HALService>(this, &HALService::handleManipulatorPort2)));



	}

	void HALService::displayHelp() {
		help = true;
		Poco::Util::HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("HAL.CanModules server.");
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

	void HALService::handleBioRadarEnable(const std::string& name, const std::string& value) {
		int val = Poco::NumberParser::parse(value);//int val = Poco::NumberParser::parse(value.substr(1));
				this->configuration.useBioRadar = val != 0;
	}
	void HALService::handleManipulatorEnable(const std::string& name, const std::string& value) {
		int val = Poco::NumberParser::parse(value);//int val = Poco::NumberParser::parse(value.substr(1));
		this->configuration.useManipulator = val != 0;
	}

	void HALService::handleManipulatorPort1(const std::string& name, const std::string& value) {
		int val = Poco::NumberParser::parse(value);//int val = Poco::NumberParser::parse(value.substr(1));
				this->configuration.manipulatorJoint1Port = val;
	}
	void HALService::handleManipulatorPort2(const std::string& name, const std::string& value) {
		int val = Poco::NumberParser::parse(value);//int val = Poco::NumberParser::parse(value.substr(1));
				this->configuration.manipulatorJoint2Port = val;
	}

	int HALService::main(const std::vector<std::string>& args) {
		if (help) {
			return EXIT_OK;
		}

		TBS::initLogs("hal", 4);

		std::cout << "-----------" << std::endl;
		std::cout << "HAL Service json" << std::endl;
		std::cout << "-----------" << std::endl;

		std::cout << "use BioRadar: " << (configuration.useBioRadar ? 1 : 0) << std::endl;
		std::cout << "use Manipulator: " << (configuration.useManipulator ? 1 : 0) << " port1: " << configuration.manipulatorJoint1Port << " port2: " << configuration.manipulatorJoint2Port << std::endl;
		std::cout << "-----------" << std::endl;


		std::cout << std::endl;

		{
			MBot::IHALFactory::Ptr f;

			if (virtualMode) {
				throw Poco::Exception("Cannot run virtual mode - not implemented");
				//f = new MBot::VirtualHALFactory();
			} else {
				f = new MBot::HALFactory(configuration.manipulatorJoint1Port, configuration.manipulatorJoint2Port);
			}

			TBS::Services::JsonServerParams bp(HAL::API::Communication::BioRadarPort);
			HAL::API::BioRadar::Json::Server::Ptr bioRadarSrv = HAL::API::BioRadar::Json::Server::createJsonServer(bp);

			TBS::Services::JsonServerParams cp(HAL::API::Communication::CameraPort);
			HAL::API::Camera::Json::Server::Ptr cameraSrv = HAL::API::Camera::Json::Server::createJsonServer(cp);

			TBS::Services::JsonServerParams ma(HAL::API::Communication::ManipulatorPort);
			HAL::API::Manipulator::Json::Server::Ptr manipSrv = HAL::API::Manipulator::Json::Server::createJsonServer(ma);
			{

				TBS::Services::IServer::Ptr camera = cameraSrv->createCamera(f->createCamera());

				TBS::Services::IServer::Ptr bioRadar;

				if (configuration.useBioRadar) {
					bioRadar = bioRadarSrv->createBioRadar(f->createBioRadar());
				}

				TBS::Services::IServer::Ptr manip;
				if (configuration.useManipulator) {
					manip = manipSrv->createManipulator(f->createManipulator());
				}
				cameraSrv->start();

				if (bioRadar) {
					bioRadarSrv->start();
				}
				if (manip) {
					manipSrv->start();
				}

				waitForTerminationRequest();

				cameraSrv->stop();

				if (bioRadar) {
					bioRadarSrv->stop();
				}
				if (manip) {
					manipSrv->stop();
				}
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
