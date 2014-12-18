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
	typedef Poco::SharedPtr<HALService> Ptr;
	HALService();
	virtual ~HALService();

	void defineOptions(Poco::Util::OptionSet& options);

	void displayHelp();
	void handleHelp(const std::string& name, const std::string& value);
	void handleMode(const std::string& name, const std::string& value);
	void handlePort(const std::string& name, const std::string& value);
protected:

	int main(const std::vector<std::string>& args);

private:
	bool help;
	bool virtualMode;
	int port;
};

} /* namespace BB */
#endif /* BoardSensors_H_ */
