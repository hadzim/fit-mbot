/*
 * IChannel.h
 *
 *  Created on: 4.3.2013
 *      Author: JV
 */

#ifndef ICHANNEL_H_
#define ICHANNEL_H_

#include <Poco/SharedPtr.h>
#include "TBS/Robo/RoboCan/Communicaton/CanMessage.h"
#include <Poco/BasicEvent.h>
namespace TBS {
	namespace Robo {
		namespace RoboCan {

				class IChannel {
					public:

						typedef Poco::SharedPtr<IChannel> Ptr;

						virtual ~IChannel();

						virtual void sendCanMessage(const CanMessage & canMessage) = 0;

						Poco::BasicEvent<CanMessage> MessageRetrieved;
				};


		} /* namespace RoboCan */
	}
}
#endif /* ICHANNEL_H_ */
