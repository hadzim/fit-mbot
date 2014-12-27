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
#ifndef ULTRASOUNDMODULE_H_
#define ULTRASOUNDMODULE_H_

#include <Poco/SharedPtr.h>
#include "TBS/Serial/SerialWrapper.h"
#include <iostream>
#include "Poco/Exception.h"
#include "TBS/Log.h"
namespace MBot {

typedef TBS::Serial::SerialWrapper SerialLib;


class UltraSoundModule {
public:

	typedef Poco::SharedPtr <UltraSoundModule> Ptr;

	UltraSoundModule(int port, int br);

	enum Commands {
		CMD_CONNECT = 0, 					//Check connection
		CMD_SET_CHANNEL_ACTIVE = 1, // Activate channel for sending / receiving
		CMD_GET_DATA_1TO8 = 2, 				//Request data of sensors 1 to 8
		CMD_GET_DATA_9TO16 = 3, 			//Request data of sensors 1 to 8
		CMD_WRITE_PARASET = 4, 		//Upload parameter set to board (volatile)
		CMD_WRITE_PARASET_TO_EEPROM = 5, //Write parameter set to board's EEPROM (non-volatile)
		CMD_READ_PARASET = 6, 				//Read current parameter set
		CMD_GET_ANALOGIN = 7 				//	Read values of analog inputs
	};
	typedef unsigned char DataByte;
	typedef std::vector<DataByte> VectorBuffer;

	void connect();

	void activate();
	std::vector<int> readData();

	VectorBuffer connectCmd();
	VectorBuffer connectAnswer();

	VectorBuffer activateCmd();

	VectorBuffer read1to8Cmd();

	void send(const VectorBuffer & buffer);

	std::vector<VectorBuffer> read(int countOfMessages);
private:
	unsigned int getCheckSum(unsigned char* c, int iNumBytes);

private:
	SerialLib serial;
}
;

} /* namespace MBot */

#endif /* ULTRASOUNDMODULE_H_ */
