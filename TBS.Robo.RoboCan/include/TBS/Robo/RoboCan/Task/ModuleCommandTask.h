/*
 * ModuleCommandTask.h
 *
 *  Created on: 6.3.2013
 *      Author: JV
 */

#ifndef COMMANDTASK_H_
#define COMMANDTASK_H_

#include "TBS/Robo/RoboCan/Communicaton/CanMessage.h"
#include <Poco/SharedPtr.h>
#include "TBS/Robo/RoboCan/Communicaton/IChannel.h"
#include "TBS/Robo/RoboCan/Communicaton/AckMessage.h"
#include "TBS/Robo/RoboCan/HW/InternalCanModule.h"
#include "TBS/Robo/RoboCan/Task/ModuleTask.h"
namespace TBS {
	namespace Robo {
		namespace RoboCan {

			/**
			 * This task is finished when finish arrived
			 * */
			class ModuleCommandTask: public ModuleTask<AckMessage> {
				public:
					ModuleCommandTask(std::string commandName, const InternalCanModule & module, const CanMessage & cmd);
					virtual ~ModuleCommandTask();
					//raised from NW thread when pure ACK OK arrived
					Poco::BasicEvent<AckMessage> Acked;
				private:
					virtual void packetRetrieved(CanMessage & m);
				private:
					Poco::UInt32 moduleCanId;
			};

			/**
			 * This task is finished when any ack or finish arrived
			 * */
			class ModuleCommandAnyAckTask: public ModuleTask<AckMessage> {
				public:
					ModuleCommandAnyAckTask(std::string taskname, const InternalCanModule & module, const CanMessage & cmd);
					virtual ~ModuleCommandAnyAckTask();

				private:
					virtual void packetRetrieved(CanMessage & m);
				private:
					Poco::UInt32 moduleCanId;
			};

		} /* namespace RoboCan */
	}
}
#endif /* COMMANDTASK_H_ */
