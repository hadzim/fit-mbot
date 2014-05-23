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

		Task::TaskFinishedStatus::TaskFinishedStatus(std::string errorMessage) :
				statusType(STATUS_ERROR), errorMessage(errorMessage) {
		}
		Task::TaskFinishedStatus::TaskFinishedStatus(StatusType t) :
				statusType(t), errorMessage("") {
		}

		bool Task::TaskFinishedStatus::isOk() const {
			return statusType == STATUS_DONE;
		}
		bool Task::TaskFinishedStatus::isError() const {
			return statusType == STATUS_ERROR;
		}
		bool Task::TaskFinishedStatus::isCanceled() const {
			return statusType == STATUS_CANCELED;
		}
		std::string Task::TaskFinishedStatus::getErrorMessage() const {
			return this->errorMessage;
		}

		Task::Task(std::string name, NotificationWorker::Ptr nw_) :
				name(name), nw_(nw_) {

		}

		Task::~Task() {
			poco_assert(!this->isActive());
			std::cout << this->isActive() << std::endl;
			LOG_STREAM_DEBUG<< "Task destructed: " << this->name << LE;

			if (!this->nw().isBgThread()) {
				if (!check.isNull()) {
					LOG_STREAM_DEBUG<< "Task destructed - wait for output event: " << this->name << LE;
						this->check->wait();
					}
					LOG_STREAM_DEBUG << "Task destructed - wait for output event: " << this->name << " done" << LE;
				}
			LOG_STREAM_DEBUG<< "Task destructed: " << this->name << " done" << LE;
		}

		void Task::start() {
			if (!this->isActive()) {
				this->activate();
			}
		}

		void Task::cancel() {
			bool val = this->isActive();
			//this->BeforeCancel.notify(this, val);
			if (val) {
				this->passivate();

				TaskFinishedStatus status(TaskFinishedStatus::STATUS_CANCELED);
				if (!this->nw().isBgThread()) {
					this->notify<TaskFinishedStatus>(Finished, status);
				} else {
					this->Finished(this, status);
				}
			}

			//this->Finished.notify(this, status);
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
			if (!this->nw().isBgThread()) {
				this->notify<TaskFinishedStatus>(Finished, status);
			} else {
				this->Finished(this, status);
			}
			//this->notify<TaskFinishedStatus>(Finished, status);

			//this->Finished.notify(this, status);
		}

		NotificationWorker & Task::nw() {
			return *(this->nw_.get());
		}

		bool Task::isActive() {
			return ActiveEventObject::isActive();
		}

	}
} /* namespace TBS */

std::ostream & operator<<(std::ostream & stream, const TBS::Task::Task::TaskFinishedStatus & s) {
	if (s.isOk()) {
		stream << "status: OK";
	}
	if (s.isCanceled()) {
		stream << "status: Canceled";
	}
	if (s.isError()) {
		stream << "status: Error (" << s.getErrorMessage() << ")";
	}
	return stream;
}

