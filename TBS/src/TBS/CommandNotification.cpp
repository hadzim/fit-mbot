/*
 * CommandNotification.cpp
 *
 *  Created on: Jan 5, 2012
 *      Author: root
 */

#include "TBS/CommandNotification.h"
#include <iostream>

namespace TBS {

		CommandNotification::CommandNotification(ICommand::Ptr command) : command(command), done(false){

		}
		CommandNotification::~CommandNotification(){

		}

		void CommandNotification::run(){
			try {
				command->run();
				done = true;
			} catch (Poco::Exception & e){
				done = false;
				this->errorMsg = "poco error " + e.message();
			} catch (std::exception & e){
				done = false;
				this->errorMsg = "std error " + (std::string)e.what();
			} catch (...){
				this->errorMsg = "unknown error";
				done = false;
			}
			CommandDoneEvent.set();
		}
		std::string CommandNotification::name() const {
			return (std::string)"CMD::" + command->getName();
		}

		bool CommandNotification::failed(){
			return !done;
		}
		bool CommandNotification::passed(){
			return done;
		}
		std::string & CommandNotification::errorMessage(){
			return this->errorMsg;
		}

		void __tseriesCmdExec(NotificationWorker & nw, ICommand::Ptr command, bool alwaysEnque, bool wait){
			if (!alwaysEnque && nw.isBgThread()) {
				command->run();
			} else {
				CommandNotification::Ptr nf = new CommandNotification(command);
				nw.postNotification(nf);
				if (wait) {
					try {
						nf->CommandDoneEvent.wait(15000);
						if (nf->failed()) {
							std::string msg = "Operation failed: ";
							msg.append(nf->errorMessage());
							throw Poco::Exception(msg);
						}
					} catch (Poco::Exception & e) {
						std::cerr << "ERROR runCmd " << command->getName() << " FAILED:" << e.displayText() << std::endl;
						throw;
					}
				}
			}
		}

} /* namespace TBS */
