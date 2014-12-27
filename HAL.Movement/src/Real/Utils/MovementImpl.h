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
#ifndef MOVEMENTIMPL_H_
#define MOVEMENTIMPL_H_
#include "TBS/Serial/SerialWrapper.h"
#include <Poco/Types.h>




namespace MBot {

typedef TBS::Serial::SerialWrapper SerialLib;

class MovementImpl {
public:
	MovementImpl(int port, int br);
	virtual ~MovementImpl();

	void go(Poco::Int64 left, Poco::Int64 right);
	void stop();


	struct Data {
		Poco::Int64 left;
		Poco::Int64 right;
	};

	void setPosition(Data position);

	Data getPosition();
	Data getVelocity();

private:
	SerialLib serial;
};

} /* namespace MBot */
#endif /* MOVEMENTIMPL_H_ */
