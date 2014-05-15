/*
 * TaskExecutor.h
 *
 *  Created on: 7.3.2013
 *      Author: JV
 */

#ifndef TASKEXECUTOR_H_
#define TASKEXECUTOR_H_
#include "TBS/Task/Task.h"
#include "Poco/Event.h"
namespace TBS {

	namespace Task {

		class SynchronizedExectution {
			public:
				SynchronizedExectution(Task::Ptr t);
				SynchronizedExectution(Task::Ptr t, int timeout);
				~SynchronizedExectution();
			private:
				void onSyncFinished(Task::TaskFinishedStatus & s);
				void afterFinished();
			private:
				Poco::Event e;
				Poco::Event ec;
				Task::Ptr task;
				Task::TaskFinishedStatus exitStatus;
				Poco::Timestamp timestamp;
		};

	}


	class TaskExecutorImpl;

	class TaskExecutor {
		public:
			TaskExecutor();
			virtual ~TaskExecutor();

			void executeSync(Task::Task::Ptr task);
			void execute(Task::Task::Ptr task);

			void executeSyncWithTimeout(Task::Task::Ptr task);
			void executeWithTimeout();

		private:
			TaskExecutorImpl * impl;

	};

/*
 class ITaskExecutor {
 public:
 virtual ~ITaskExecutor(){}
 virtual void execute(Task::Task::Ptr task) = 0;
 };

 class TaskExecutor {
 public:
 virtual ~TaskExecutor(){
 if (!this->runningTask.isNull()){
 this->runningTask->cancel();
 }
 }
 virtual void execute(Task::Task::Ptr task){
 if (this->runningTask.isNull() && this->doneTask.isNull()){
 throw Poco::Exception("Already pending task");
 }
 this->runningTask = task;
 this->doneTask = NULL;
 }
 private:



 Task::Task::Ptr runningTask;
 Task::Task::Ptr doneTask;
 };

 class TaskExecutor {
 public:
 TaskExecutor();
 virtual ~TaskExecutor();

 void executeSync(Task::Task::Ptr task);
 void execute(Task::Task::Ptr task);

 void executeSyncWithTimeout(Task::Task::Ptr task);
 void executeWithTimeout();
 };
 */
} /* namespace TBS */
#endif /* TASKEXECUTOR_H_ */
