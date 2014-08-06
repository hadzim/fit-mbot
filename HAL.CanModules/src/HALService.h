/*
 * BoardSensors.h
 *
 *  Created on: Jan 31, 2013
 *      Author: root
 */

#ifndef HALSERVICE_H_
#define HALSERVICE_H_
#include <Poco/SharedPtr.h>
#include "Poco/Util/ServerApplication.h"
#include "Poco/Timer.h"
#include "TBS/SafeTimer.h"

#include <Poco/Util/HelpFormatter.h>
#include <iostream>

namespace HAL {

	class HALService: public Poco::Util::ServerApplication {

		public:

			struct Configuration {
					Configuration();
					bool useBioRadar;
					bool useManipulator;

					int manipulatorJoint1Port;
					int manipulatorJoint2Port;
			};

			typedef Poco::SharedPtr<HALService> Ptr;
			HALService();
			virtual ~HALService();

			void defineOptions(Poco::Util::OptionSet& options);

			void displayHelp();
			void handleHelp(const std::string& name, const std::string& value);
			void handleMode(const std::string& name, const std::string& value);

			void handleBioRadarEnable(const std::string& name, const std::string& value);
			void handleManipulatorEnable(const std::string& name, const std::string& value);

			void handleManipulatorPort1(const std::string& name, const std::string& value);
			void handleManipulatorPort2(const std::string& name, const std::string& value);
		protected:

			void initialize(Application& self);
			void uninitialize();
			void reinitialize(Application& self);

			int main(const std::vector<std::string>& args);

		private:
			Configuration configuration;
			bool help;
			bool virtualMode;

	};

#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/AutoPtr.h"
#include <iostream>

	using Poco::Util::Application;
	using Poco::Util::Option;
	using Poco::Util::OptionSet;
	using Poco::Util::HelpFormatter;
	using Poco::Util::AbstractConfiguration;
	using Poco::Util::OptionCallback;
	using Poco::AutoPtr;

	class SampleApp: public Application
	/// This sample demonstrates some of the features of the Util::Application class,
	/// such as configuration file handling and command line arguments processing.
	///
	/// Try SampleApp --help (on Unix platforms) or SampleApp /help (elsewhere) for
	/// more information.
	{
		public:
			SampleApp() :
					_helpRequested(false) {
			}

		protected:
			void initialize(Application& self) {
				loadConfiguration(); // load default configuration files, if present
				Application::initialize(self);
				// add your own initialization code here
			}

			void uninitialize() {
				// add your own uninitialization code here
				Application::uninitialize();
			}

			void reinitialize(Application& self) {
				Application::reinitialize(self);
				// add your own reinitialization code here
			}

			void defineOptions(OptionSet& options) {
				Application::defineOptions(options);

				options.addOption(
						Option("help", "h", "display help information on command line arguments").required(false).repeatable(false).callback(
								OptionCallback<SampleApp>(this, &SampleApp::handleHelp)));

				options.addOption(
						Option("define", "D", "define a configuration property").required(false).repeatable(true).argument("name=value").callback(
								OptionCallback<SampleApp>(this, &SampleApp::handleDefine)));

				options.addOption(
						Option("config-file", "f", "load configuration data from a file").required(false).repeatable(true).argument("file").callback(
								OptionCallback<SampleApp>(this, &SampleApp::handleConfig)));

				options.addOption(
						Option("bind", "b", "bind option value to test.property").required(false).repeatable(false).argument("value").binding("test.property"));
			}

			void handleHelp(const std::string& name, const std::string& value) {
				_helpRequested = true;
				displayHelp();
				stopOptionsProcessing();
			}

			void handleDefine(const std::string& name, const std::string& value) {
				defineProperty(value);
			}

			void handleConfig(const std::string& name, const std::string& value) {
				loadConfiguration(value);
			}

			void displayHelp() {
				HelpFormatter helpFormatter(options());
				helpFormatter.setCommand(commandName());
				helpFormatter.setUsage("OPTIONS");
				helpFormatter.setHeader("A sample application that demonstrates some of the features of the Poco::Util::Application class.");
				helpFormatter.format(std::cout);
			}

			void defineProperty(const std::string& def) {
				std::string name;
				std::string value;
				std::string::size_type pos = def.find('=');
				if (pos != std::string::npos) {
					name.assign(def, 0, pos);
					value.assign(def, pos + 1, def.length() - pos);
				} else
					name = def;
				config().setString(name, value);
			}

			int main(const std::vector<std::string>& args) {
				if (!_helpRequested) {
					logger().information("Arguments to main():");
					for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it) {
						logger().information(*it);
					}
					logger().information("Application properties:");
					printProperties("");
				}
				return Application::EXIT_OK;
			}

			void printProperties(const std::string& base) {
				AbstractConfiguration::Keys keys;
				config().keys(base, keys);
				if (keys.empty()) {
					if (config().hasProperty(base)) {
						std::string msg;
						msg.append(base);
						msg.append(" = ");
						msg.append(config().getString(base));
						logger().information(msg);
					}
				} else {
					for (AbstractConfiguration::Keys::const_iterator it = keys.begin(); it != keys.end(); ++it) {
						std::string fullKey = base;
						if (!fullKey.empty())
							fullKey += '.';
						fullKey.append(*it);
						printProperties(fullKey);
					}
				}
			}

		private:
			bool _helpRequested;
	};

} /* namespace BB */
#endif /* BoardSensors_H_ */
