/*
 * TaskExecutor.cpp
 *
 *  Created on: 7.3.2013
 *      Author: JV
 */

#include "TBS/Robo/TaskExecutor.h"

namespace TBS {
	namespace Task {

		void SynchronizedExectution::afterFinished() {
			this->task = NULL;
			if (this->exitStatus.isCanceled()) {
				throw Poco::Exception("Task canceled");
			}
			if (this->exitStatus.isError()) {
				throw Poco::Exception("Task error");
			}
		}

		SynchronizedExectution::SynchronizedExectution(Task::Ptr t) :
				task(t) {
			task->Finished += Poco::delegate(this, &SynchronizedExectution::onSyncFinished);
			task->start();
			e.wait();
			this->afterFinished();
		}

		SynchronizedExectution::SynchronizedExectution(Task::Ptr t, int timeout) :
				task(t) {

			std::cout << "sync execute done" << std::endl;

			task->Finished += Poco::delegate(this, &SynchronizedExectution::onSyncFinished);
			task->start();
			try {
				e.wait(timeout);
				std::cout << "SUCCESS" << std::endl;
			} catch (Poco::TimeoutException & ){
				std::cout << "ERROR: timeout: " << timeout << std::endl;
				task->cancel();
				ec.wait(timeout);
				//std::cout << "ERROR: timeout done " << std::endl;
			}
			this->afterFinished();
			//std::cout << "sync execute done" << std::endl;
		}

		SynchronizedExectution::~SynchronizedExectution(){
			if (!this->task.isNull()){
				this->task->cancel();
			}
		}


		void SynchronizedExectution::onSyncFinished(TBS::Task::Task::TaskFinishedStatus & s) {
			std::cout << "task finished: " << (s.isOk() ? "ok" : "fail/cancel") << std::endl;
			task->Finished -= Poco::delegate(this, &SynchronizedExectution::onSyncFinished);
			this->exitStatus = s;
			e.set();
			ec.set();
		}

	}
/*
 class TaskExecutorImpl {
 private:
 void onSyncFinished(TBS::Task::Task::TaskFinishedStatus & s) {

 }
 void executeSync(Task::Task::Ptr task) {
 task->Finished += Poco::delegate(this,
 &TaskExecutorImpl::onSyncFinished);
 }

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

/*
 TaskExecutor::TaskExecutor() {
 // TODO Auto-generated constructor stub

 }

 TaskExecutor::~TaskExecutor() {
 // TODO Auto-generated destructor stub
 }
 */
} /* namespace TBS */
