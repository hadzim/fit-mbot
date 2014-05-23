/*
 * ConsumingModuleTask.h
 *
 *  Created on: 30.4.2014
 *      Author: JV
 */

#ifndef CONSUMINGMODULETASK_H_
#define CONSUMINGMODULETASK_H_
#include "TBS/Task/Task.h"
#include "TBS/NotificationWorker.h"
#include "TBS/Robo/RoboCan/Communicaton/IChannel.h"
#include "TBS/Robo/RoboCan/HW/InternalCanModule.h"
#include "TBS/Robo/RoboCan/HW/ICanModule.h"
#include "TBS/Nullable.h"
#include "TBS/Robo/RoboCan/Communicaton/DataMessage.h"

namespace TBS {
namespace Robo {
namespace RoboCan {

class ConsumingDataModuleTask : public TBS::Task::Task{
public:
	typedef Poco::SharedPtr <ConsumingDataModuleTask> Ptr;
	ConsumingDataModuleTask(const InternalCanModule & module);
	virtual ~ConsumingDataModuleTask();
private:
	void onOuterActivation(TBS::Activation & a);
	void packetRetrieved(CanMessage & m);
private:
	TBS::NotificationWorker::Ptr nw;
	IChannel::Ptr channel;
	ICanModule::CanID canID;

	TBS::Nullable<DataMessage> currentMessage;
};

}
}
} /* namespace MBot */
#endif /* CONSUMINGMODULETASK_H_ */
