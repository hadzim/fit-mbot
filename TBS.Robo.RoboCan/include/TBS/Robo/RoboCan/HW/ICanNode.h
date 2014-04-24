/*
 * INode.h
 *
 *  Created on: 4.3.2013
 *      Author: JV
 */

#ifndef ICANNODE_H_
#define ICANNODE_H_
#include <Poco/Types.h>
#include <Poco/SharedPtr.h>
#include "TBS/Robo/RoboCan/Communicaton/IChannel.h"
#include "TBS/NotificationWorker.h"

#include "TBS/Robo/INode.h"

namespace TBS {
	namespace Robo {
		namespace RoboCan {

				class ICanNode : public TBS::Robo::INode {
					public:
						typedef Poco::UInt32 CanID;
						typedef Poco::SharedPtr<ICanNode> Ptr;
						typedef ICanNode * RawPtr;

						virtual ~ICanNode();
						virtual CanID getCanID() const = 0;
						virtual CanID getCanNodeID() const = 0;
						virtual IChannel::Ptr getCommunicationChannel() = 0;
						virtual TBS::NotificationWorker::Ptr getNotificationWorker() = 0;
				};


		} /* namespace RoboCan */
	}
}
#endif /* INODE_H_ */
