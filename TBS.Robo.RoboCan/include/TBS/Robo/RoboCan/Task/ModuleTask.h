/*
 * ModuleTask.h
 *
 *  Created on: 7.3.2013
 *      Author: JV
 */

#ifndef MODULETASK_H_
#define MODULETASK_H_
#include "TBS/Robo/RoboCan/Communicaton/CanMessage.h"
#include "TBS/Task/InputOutputTask.h"
#include "TBS/Robo/RoboCan/Communicaton/IChannel.h"
namespace TBS {
	namespace Robo {
		namespace RoboCan {

				template<class Output>
				class ModuleTask: public TBS::Task::OutputTask<Output> {
					public:
						typedef Poco::SharedPtr<ModuleTask<Output> > Ptr;

						ModuleTask(std::string name, TBS::NotificationWorker::Ptr nw, IChannel::Ptr channel, const CanMessage & msg) :
								TBS::Task::OutputTask<Output>(name, nw), channel(channel), message(msg) {

							this->OuterActivation += Poco::delegate(this, &ModuleTask::onOuterActivation);
							this->InnerActivation += Poco::delegate(this, &ModuleTask::onInnerActivation);

						}
						virtual ~ModuleTask() {
							this->OuterActivation -= Poco::delegate(this, &ModuleTask::onOuterActivation);
							this->InnerActivation -= Poco::delegate(this, &ModuleTask::onInnerActivation);
						}
					protected:
						virtual void packetRetrieved(CanMessage & m) = 0;
						void setDone(Output & o) {
							this->setOutput(o);
							TBS::CommandExecutorEnqueueAndContinue::execute(this->nw(),
									new TBS::Command<ModuleTask<Output> >("CmdNtfDone", this, &ModuleTask<Output>::setDoneImpl));
						}
					private:
						void onOuterActivation(TBS::Activation & a) {
							if (a == TBS::Activating) {
								channel->MessageRetrieved += Poco::delegate(this, &ModuleTask::onMessage);
							} else {
								channel->MessageRetrieved -= Poco::delegate(this, &ModuleTask::onMessage);
							}
						}
						void onInnerActivation(TBS::Activation & a) {
							if (a == TBS::Activating) {
								channel->sendCanMessage(this->message);
							} else {

							}
						}

						void onMessage(CanMessage & m) {
							this->packetRetrieved(m);
						}
						void setDoneImpl() {
							this->finished();
						}
					private:

						IChannel::Ptr channel;
						CanMessage message;
				};


		} /* namespace RoboCan */
	}
}
#endif /* MODULETASK_H_ */
