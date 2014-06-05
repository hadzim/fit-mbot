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
			} catch (Poco::TimeoutException &) {

				task->cancel();
				ec.wait(timeout);
				//std::cout << "ERROR: timeout done " << std::endl;
			}
			this->afterFinished();

			//std::cout << "sync execute done" << std::endl;
		}

		SynchronizedExectution::~SynchronizedExectution() {
			if (!this->task.isNull()) {
				this->task->Finished -= Poco::delegate(this, &SynchronizedExectution::onSyncFinished);
				this->task->cancel();
			}
		}

		void SynchronizedExectution::onSyncFinished(TBS::Task::Task::TaskFinishedStatus & s) {
			std::cout << "sync task finished: " << s << " after " << (timestamp.elapsed() / 1000) << "ms" << std::endl;
			task->Finished -= Poco::delegate(this, &SynchronizedExectution::onSyncFinished);
			this->exitStatus = s;
			e.set();
			ec.set();
		}

		 Poco::Mutex TaskWrapper::m;

		TaskWrapper::TaskWrapper(Task::Ptr t) :
				t(t), active(true) {
			LERROR("app") << "wrap task " << t->getName() << LE;

			t->Finished += Poco::delegate(this, &TaskWrapper::onFinished);
			t->start();
		}
		TaskWrapper::~TaskWrapper() {
			t->cancel();
			t->Finished -= Poco::delegate(this, &TaskWrapper::onFinished);
		}

		void TaskWrapper::cancel() {
			t->cancel();
		}
		bool TaskWrapper::isActive() {
			return active;
		}

		void TaskWrapper::onFinished(Task::TaskFinishedStatus & status) {
			std::cout << "task finished: " << status << " after " << (tstmp.elapsed() / 1000) << "ms" << std::endl;

			t->Finished -= Poco::delegate(this, &TaskWrapper::onFinished);
			active = false;
		}

		OneActiveTaskExectution::~OneActiveTaskExectution() {
			Poco::Mutex::ScopedLock l(m);
			this->cancelAll();
			LDEBUG("app") << "one active task finished" << LE;
		}

		void OneActiveTaskExectution::addTask(Task::Ptr t) {
			LWARNING("app") << "add task " << t->getName() << LE;
			Poco::Mutex::ScopedLock l(m);
			//cancel all old tasks
			this->cancelAll();


			tasks.push_back(new TaskWrapper(t));


			//remove passive tasks
			std::vector<TaskWrapper::Ptr> cpy = tasks;
			tasks.clear();
			for (std::vector<TaskWrapper::Ptr>::iterator i = cpy.begin(); i != cpy.end(); i++) {
				if ((*i)->isActive()) {
					tasks.push_back(*i);
				}
			}
		}

		void OneActiveTaskExectution::cancelAll() {
			for (std::vector<TaskWrapper::Ptr>::iterator i = tasks.begin(); i != tasks.end(); i++) {
				(*i)->cancel();
			}
			LDEBUG("app") << "all tasks canceled" << LE;
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
