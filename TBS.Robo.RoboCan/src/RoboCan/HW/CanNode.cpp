/*
 * Submodule.cpp
 *
 *  Created on: 4.3.2013
 *      Author: JV
 */

#include "TBS/Robo/RoboCan/HW/CanNode.h"
namespace TBS {
namespace Robo {
namespace RoboCan {

CanNode::CanNode(const Name & name, const CanID & nodeID, TBS::NotificationWorker::Ptr nw,
		IChannel::Ptr channel) :
		name(name), nodeID(nodeID), nw(nw), channel(channel) {

}

CanNode::~CanNode() {

}

const CanNode::Name & CanNode::getName() const {
	return this->name;
}

CanNode::CanID CanNode::getCanID() const {
	return (300 + (this->getCanNodeID() - 1) * 16);
}

CanNode::CanID CanNode::getCanNodeID() const {
	return this->nodeID;
}

IChannel::Ptr CanNode::getCommunicationChannel() {
	return this->channel;
}
TBS::NotificationWorker::Ptr CanNode::getNotificationWorker() {
	return this->nw;
}

} /* namespace RoboCan */

}
}
