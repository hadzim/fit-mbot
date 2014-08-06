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

			int main(const std::vector<std::string>& args);

		private:
			Configuration configuration;
			bool help;
			bool virtualMode;

	};

} /* namespace BB */
#endif /* BoardSensors_H_ */
