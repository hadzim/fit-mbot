/*
 * Task.cpp
 *
 *  Created on: Feb 2, 2012
 *      Author: root
 */

#include "TBS/Task/Task.h"
#include <iostream>

namespace TBS {
	namespace Task {

		Task::Task(std::string name, NotificationWorker::Ptr nw_) :
				name(name), nw_(nw_) {
		}

		Task::~Task() {
			if (this->isActive()) {
				std::cerr << "Task: " << this->name << " is active" << std::endl;
			}
			poco_assert(!this->isActive());
		}

		void Task::start() {
			if (!this->isActive()) {
				this->activate();
			}
		}

		void Task::cancel() {
			bool val = this->isActive();
			if (val) {
				this->passivate();
			}
			TaskFinishedStatus status(TaskFinishedStatus::STATUS_CANCELED);
			this->notify<TaskFinishedStatus>(Finished, status);
		}

		std::string Task::getName() {
			return this->name;
		}
		void Task::finished() {
			this->passivate();
			TaskFinishedStatus status(TaskFinishedStatus::STATUS_DONE);
			this->notify<TaskFinishedStatus>(Finished, status);
			//this->Finished.notify(this, status);
		}
		void Task::failed(std::string message) {
			this->passivate();
			TaskFinishedStatus status(message);
			//status.errorMessage = message;
			this->notify<TaskFinishedStatus>(Finished, status);
			//this->Finished.notify(this, status);
		}

		NotificationWorker & Task::nw() {
			return *(this->nw_.get());
		}

	}
} /* namespace TBS */
