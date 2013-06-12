/*
 * Submodule.h
 *
 *  Created on: 4.3.2013
 *      Author: JV
 */

#include "ICanNode.h"

#ifndef NODE_H_
#define NODE_H_
namespace TBS {
	namespace Robo {
		namespace RoboCan {
			
				class CanNode: public ICanNode {
					public:

						CanNode(const Name & name, const CanID & nodeID, TBS::NotificationWorker::Ptr nw, IChannel::Ptr channel);
						virtual ~CanNode();

						virtual const Name & getName() const;
						virtual CanID getCanID() const;
						virtual CanID getCanNodeID() const;

						virtual IChannel::Ptr getCommunicationChannel();
						virtual TBS::NotificationWorker::Ptr getNotificationWorker();
					private:
						Name name;
						CanID nodeID;
						TBS::NotificationWorker::Ptr nw;
						IChannel::Ptr channel;
				};

			
		} /* namespace RoboCan */
	}
}
#endif /* SUBMODULE_H_ */
