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
@brief     Header file
@authors   Jan Vana (<ivanajan@fit.vutbr.cz>)
@date      2010-2014
@note      This project was supported by project funds of the MV CR grant VG20102014024.

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
	int port;
	bool help;
	bool virtualMode;
};

} /* namespace BB */
#endif /* BoardSensors_H_ */
