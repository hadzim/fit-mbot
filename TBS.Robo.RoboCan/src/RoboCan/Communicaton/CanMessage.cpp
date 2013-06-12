/*
 * CanMessage.cpp
 *
 *  Created on: 4.3.2013
 *      Author: JV
 */

#include "TBS/Robo/RoboCan/Communicaton/CanMessage.h"
#include <sstream>
namespace TBS {
	namespace Robo {
		namespace RoboCan {
			

				CanMessage::CanMessage() {
					canID = 0;
					length = 0;
					b0 = b1 = b2 = b3 = b4 = b5 = b6 = b7 = 0;
				}
				std::string CanMessage::toString() const{
					std::stringstream s;
					s << "canID: " << canID << " len: " << (int)length;
					s << " (";
					if (length > 0) s << " "<< (int)b0;
					if (length > 1) s << " "<< (int)b1;
					if (length > 2) s << " "<< (int)b2;
					if (length > 3) s << " "<< (int)b3;
					if (length > 4) s << " "<< (int)b4;
					if (length > 5) s << " "<< (int)b5;
					if (length > 6) s << " "<< (int)b6;
					if (length > 7) s << " "<< (int)b7;
					s << " "<< ")";
					return s.str();
				}
			
		} /* namespace RoboCan */

	}
}
