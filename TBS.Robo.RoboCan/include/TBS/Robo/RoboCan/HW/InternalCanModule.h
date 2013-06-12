/*
 * InternalCanModule.h
 *
 *  Created on: 7.3.2013
 *      Author: JV
 */

#ifndef INTERNALMODULE_H_
#define INTERNALMODULE_H_
#include "TBS/Robo/RoboCan/HW/ICanModule.h"
namespace TBS {
	namespace Robo {
		namespace RoboCan {

				class InternalCanModule: public ICanModule {
					public:
						typedef InternalCanModule * RawPtr;

						InternalCanModule(std::string name, ICanNode::RawPtr node, int numberWithinModule);
						virtual ~InternalCanModule();

						IChannel::Ptr getCommunicationChannel() const;
						TBS::NotificationWorker::Ptr getNotificationWorker() const;

						CanMessage composeCommand(ICanModule::Command command, const RoboCanMessageData & data =
								RoboCanMessageData(), ICanModule::Channel channel = 0) const;

						CanMessage cmdStatus() const;
						CanMessage cmdStart() const;
						CanMessage cmdHalt() const;
						CanMessage cmdRestart() const;
						CanMessage cmdStop() const;
						CanMessage cmdGetError() const;
						CanMessage cmdGetData() const;
					private:
						ICanNode::RawPtr myNode;
				};


		} /* namespace RoboCan */
	}
}
#endif /* INTERNALMODULE_H_ */
