/*
 * Task.h
 *
 *  Created on: Feb 2, 2012
 *      Author: root
 */

#ifndef NewDEVICE_TASK_H_
#define NewDEVICE_TASK_H_
#include "TBS/ActiveEventObject.h"
#include <Poco/SharedPtr.h>
#include "TBS/NotificationWorker.h"
#include "TBS/OutputNotification.h"
#include "TBS/CommandNotification.h"
#include <memory>

namespace TBS {
	namespace Task {
		class TBS_API Task: protected ActiveEventObject {
			public:
				struct TaskFinishedStatus {
						enum StatusType {
							STATUS_DONE, STATUS_ERROR, STATUS_CANCELED,
						};

						StatusType statusType;
						std::string errorMessage;

						TaskFinishedStatus(std::string errorMessage) :
								statusType(STATUS_ERROR), errorMessage(errorMessage) {
						}
						TaskFinishedStatus(StatusType t = STATUS_DONE) :
								statusType(t), errorMessage("") {
						}

						bool isOk() {
							return statusType == STATUS_DONE;
						}
						bool isError() {
							return statusType == STATUS_ERROR;
						}
						bool isCanceled() {
							return statusType == STATUS_CANCELED;
						}
						std::string getErrorMessage() {
							return this->errorMessage;
						}
				};

				typedef Poco::SharedPtr<Task> Ptr;

				Task(std::string name, NotificationWorker::Ptr nw_);
				virtual ~Task();

				Task(const Task & t);

				void start();
				void cancel();
				Poco::BasicEvent<TaskFinishedStatus> Finished;

				std::string getName();
			protected:

				void finished();
				void failed(std::string message);

				template<class Argument>
				void notify(Poco::BasicEvent<Argument> & event, Argument & value) {
					TBS::CommandExecutorEnqueueAndContinue::execute(this->nw(), new OutputEventCommand<Argument>(this, event, value));
					//this->nw().postNotification(new OutputEventNotification<Argument>(this, event, value));
				}

			protected:
				NotificationWorker & nw();
			private:

				std::string name;
				NotificationWorker::Ptr nw_;

		};

		/**
		 * to keep task as a class member
		 * do not use together with atomic task provider
		 * */
		template<class TaskType>
		class TaskHolder {
			public:
				typedef std::auto_ptr<TaskType> APtr;
				//takes ownership
				TaskHolder(APtr task_) :
						task_(task_) {

				}
				//takes ownership
				TaskHolder(TaskType * task_) :
						task_(APtr(task_)) {

				}
				~TaskHolder() {
					task_->cancel();
				}
				TaskType & task() {
					return *(task_.get());
				}
				TaskType * operator->() {
					return (task_.get());
				}
			private:
				APtr task_;
		};
	}
} /* namespace TBS */
#endif /* TASK_H_ */
