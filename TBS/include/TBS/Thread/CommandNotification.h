/*
 * CommandNotification.h
 *
 *  Created on: Jan 5, 2012
 *      Author: root
 */

#ifndef COMMANDNOTIFICATION_H_
#define COMMANDNOTIFICATION_H_

#include <Poco/Notification.h>
#include "TBS/Command.h"
#include "Poco/Event.h"
#include "TBS/Thread/NotificationWorker.h"

namespace TBS {

		class  CommandNotification: public Poco::Notification {

			public:

				typedef Poco::AutoPtr<CommandNotification> Ptr;

				CommandNotification(ICommand::Ptr command);
				virtual ~CommandNotification();

				void run();
				virtual std::string name() const;

				Poco::Event CommandDoneEvent;

				bool failed();
				bool passed();
				std::string & errorMessage();
			private:
				ICommand::Ptr command;
				bool done;
				std::string errorMsg;

		};

		void __tseriesCmdExec(NotificationWorker & nw, ICommand::Ptr command, bool alwaysEnque, bool wait);

		template<bool AlwaysEnque, bool Wait>
		class CommandExecutor {
			public:
				static void execute(NotificationWorker & nw, ICommand::Ptr command) {
					__tseriesCmdExec(nw, command, AlwaysEnque, Wait);
				}
				static void execute(NotificationWorker::Ptr nw, ICommand::Ptr command) {
					execute(*(nw.get()), command);
				}

		};

		//typedef CommandExecutor <true, true> CommandExecutorEnqueueAndBlock;
		typedef CommandExecutor <true, false> CommandExecutorEnqueueAndContinue;
		typedef CommandExecutor <false, true> CommandExecutorAutoAndBlock;
		typedef CommandExecutor <false, false> CommandExecutorAutoAndContinue;


} /* namespace TBS */
#endif /* MODULECOMMANDNOTIFICATION_H_ */
