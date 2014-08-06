/*
 * Module.h
 *
 *  Created on: 4.3.2013
 *      Author: JV
 */

#ifndef MODULE_H_
#define MODULE_H_
#include <string>
#include <Poco/Types.h>
#include "TBS/Robo/RoboCan/Communicaton/IChannel.h"
#include "TBS/Robo/RoboCan/Communicaton/RoboCanMessageData.h"
#include "TBS/Robo/RoboCan/HW/ICanNode.h"
#include <Poco/Mutex.h>
#include <Poco/Event.h>
#include "TBS/Robo/RoboCan/HW/ICanModule.h"
#include "TBS/Robo/RoboCan/HW/InternalCanModule.h"
#include "TBS/Robo/RoboCan/Task/ModuleStatusTask.h"
#include "TBS/Robo/RoboCan/Task/ModuleDataTask.h"
#include "TBS/Robo/RoboCan/Task/ModuleCommandTask.h"
namespace TBS {
	namespace Robo {
		namespace RoboCan {
			

				class CanModule: public ICanModule {
					public:

						typedef Poco::UInt8 Command;
						typedef Poco::UInt8 Channel;

						CanModule(const std::string & name, ICanNode::RawPtr node, int numberWithinModule/*, IChannel::Ptr channel*/);
						virtual ~CanModule();

						ModuleStatusTask::Ptr taskGetStatus() const;

						ModuleDataTask::Ptr taskGetData() const;

						ModuleCommandTask::Ptr taskGetError() const;

						ModuleCommandAnyAckTask::Ptr taskStart() const;
						ModuleCommandAnyAckTask::Ptr taskHalt() const;
						ModuleCommandAnyAckTask::Ptr taskRestart() const;
						ModuleCommandAnyAckTask::Ptr taskStop() const;

						void askData() const;
					protected:

						const InternalCanModule & getInternalModule() const;
					private:
						InternalCanModule internalModule;

						//sending commands
						/*
						 void cmdStatus();
						 void cmdStart();
						 void cmdHalt();
						 void cmdRestart();
						 void cmdStop();
						 void cmdGetError();
						 void cmdGetData();
						 */
						/*
						 StatusMessage getLastStatusMessage() const;
						 void setLastStatusMessage(StatusMessage & m);
						 */
						/*
						 private:
						 struct AnswerPackage {
						 public:
						 RoboCanMessage message;
						 Poco::Event event;
						 };
						 */
					protected:
						//void executeCommand(Command command);
						//void executeCommand(Command command, const RoboCanMessageData & data);
						//void executeCommand(Command command, const RoboCanMessageData & data, Channel channel);

					private:
						//std::string name;
						//INode::RawPtr node;
						//int numberWithinNode;

						//max event execution time in miliseconds
						static const int maxExecutionTimeInMs = 1000;

						//Poco::Mutex mutex;

						//StatusMessage * lastStatusMessage;
						//IChannel::Ptr channel;
				};
			/*



			 #region Retrieving messages


			 private class AnswerPackage {
			 public BetaLabMessage message = null;
			 public ManualResetEvent lastEvent = new ManualResetEvent(false);
			 }

			 private Dictionary<Listener<BetaLabMessage>, AnswerPackage> activeListeners = new Dictionary<Listener<BetaLabMessage>,AnswerPackage>();

			 object o = new object();

			 private void answerArrived(Listener<BetaLabMessage> listener, BetaLabMessage message) {
			 lock (o) {
			 if (!listener.isActive()) return;
			 //Log.LogObserver.Instance.acceptLog(new Scanner.Controlling.Log.LogMessage("<-" + listener.GetType().Name + listener.GetHashCode().ToString(), Scanner.Controlling.Log.LogMessage.eStatus.ERROR));

			 if (this.activeListeners.ContainsKey(listener)) {
			 try {
			 lock (lockObject) {
			 this.activeListeners[listener].message = message.clone();
			 }
			 listener.passivate();
			 this.activeListeners[listener].lastEvent.Set();
			 //Log.LogObserver.Instance.acceptLog(new Scanner.Controlling.Log.LogMessage("OK", Scanner.Controlling.Log.LogMessage.eStatus.INFO));

			 } catch {
			 Scanner.Controlling.Log.LogObserver.Instance.acceptLog(new Scanner.Controlling.Log.LogMessage("Error during lister Event", Scanner.Controlling.Log.LogMessage.eStatus.ERROR));

			 listener.passivate();
			 }
			 } else {
			 Scanner.Controlling.Log.LogObserver.Instance.acceptLog(new Scanner.Controlling.Log.LogMessage("No listener is active " + message.ToString(), Scanner.Controlling.Log.LogMessage.eStatus.ERROR));
			 listener.passivate();
			 }
			 }
			 }

			 private BetaLabMessage readAnswer(NewComunication.Listeners.GeneralListener listener) {
			 //Log.LogObserver.Instance.acceptLog(new Scanner.Controlling.Log.LogMessage("->" + listener.GetType().Name + listener.GetHashCode().ToString(), Scanner.Controlling.Log.LogMessage.eStatus.INFO));
			 AnswerPackage package = new AnswerPackage();

			 this.activeListeners.Add(listener, package);

			 //set listner action
			 listener.onMessageAcceptEvent += new Listener<BetaLabMessage>.MessageAcceptedHandler(answerArrived);
			 //add listener
			 ComunicationChannelProvider.Instance.ComunicationChannel.addListener(listener);

			 if (!package.lastEvent.WaitOne(this.maxExecutionTime, false)) {
			 activeListeners.Remove(listener);
			 throw new Exception("Waiting for answer failed");
			 } else {
			 activeListeners.Remove(listener);
			 lock (this.lockObject) {
			 return package.message.clone();
			 }
			 }

			 }

			 private ManualResetEvent dataReadingDoneEvent = null;
			 private DataMessage lastDataMessage = null;

			 public DataMessage LastDataMessage {
			 get {return lastDataMessage;}
			 set {
			 lastDataMessage = value;
			 if (this.ModuleDataChanged != null) {
			 this.ModuleDataChanged.Invoke(this, LastDataMessage);
			 }
			 }
			 }

			 private DataMessage readDataAnswer() {
			 //wait anouncement
			 this.dataReadingDoneEvent = new ManualResetEvent(false);

			 var listener = new NewComunication.Listeners.ModuleDataListener(this);
			 //set listner action
			 listener.onDataMessageAcceptEvent += new NewComunication.Listeners.ModuleDataListener.MessageDataAcceptedHandler(listener_onDataMessageAcceptEvent);
			 //add listener
			 ComunicationChannelProvider.Instance.ComunicationChannel.addListener(listener);

			 if (!this.dataReadingDoneEvent.WaitOne(this.maxExecutionTime, false)) {
			 throw new Exception("Waiting for data failed");
			 } else {
			 lock (this.lockObject) {
			 return this.lastDataMessage.clone();
			 }
			 }

			 }

			 void listener_onDataMessageAcceptEvent(NewComunication.Listeners.ModuleDataListener listener, DataMessage message) {
			 lock (lockObject) {
			 if (message == null) {
			 this.lastDataMessage = null;
			 } else {
			 this.lastDataMessage = message.clone();
			 }
			 }
			 listener.passivate();
			 this.dataReadingDoneEvent.Set();
			 }

			 #region COMPOSED

			 public bool readAcknowledgement() {
			 try {
			 AckMessage m = new AckMessage(this.readAnswer(new NewComunication.Listeners.ModuleAckListener(this)));
			 if (!m.Acked) {
			 Scanner.Controlling.Log.LogObserver.Instance.acceptLog(new Scanner.Controlling.Log.LogMessage(this.Name + " Ack fail by message CMD = " + m.InnerMessage.Cmd.ToString(), Scanner.Controlling.Log.LogMessage.eStatus.ERROR));
			 }
			 return m.Acked;
			 } catch (Exception exc) {
			 Scanner.Controlling.Log.LogObserver.Instance.acceptLog(new Scanner.Controlling.Log.LogMessage(this.Name + " Ack fail exc " + exc.Message, Scanner.Controlling.Log.LogMessage.eStatus.ERROR));
			 return false;
			 }
			 }

			 public StatusMessage readStatus() {
			 //Scanner.Controlling.Log.LogObserver.Instance.acceptLog(new Scanner.Controlling.Log.LogMessage("read status 1", Scanner.Controlling.Log.LogMessage.eStatus.INFO));

			 this.CmdStatus();
			 //Scanner.Controlling.Log.LogObserver.Instance.acceptLog(new Scanner.Controlling.Log.LogMessage("read status 2", Scanner.Controlling.Log.LogMessage.eStatus.INFO));
			 BetaLabMessage blMessage = this.readAnswer(new NewComunication.Listeners.ModuleStatusListener(this));
			 //Scanner.Controlling.Log.LogObserver.Instance.acceptLog(new Scanner.Controlling.Log.LogMessage("read status 3", Scanner.Controlling.Log.LogMessage.eStatus.INFO));
			 this.LastStatusMessage = new StatusMessage(blMessage);
			 //Scanner.Controlling.Log.LogObserver.Instance.acceptLog(new Scanner.Controlling.Log.LogMessage("read status 4", Scanner.Controlling.Log.LogMessage.eStatus.INFO));
			 return this.LastStatusMessage;
			 }

			 public DataMessage readData() {
			 //this.();
			 this.CmdGetData();
			 this.LastDataMessage = this.readDataAnswer();
			 return this.LastDataMessage.clone();
			 }



			 protected void checkWaiting() {
			 if (this.readStatus().State != NewComunication.StatusMessage.eState.Waiting) {
			 throw new Exception("Module not ready");
			 }
			 }

			 public void goWaiting() {
			 //Scanner.Controlling.Log.LogObserver.Instance.acceptLog(new Scanner.Controlling.Log.LogMessage("goWait 1", Scanner.Controlling.Log.LogMessage.eStatus.INFO));
			 StatusMessage.eState state = this.readStatus().State;
			 //Scanner.Controlling.Log.LogObserver.Instance.acceptLog(new Scanner.Controlling.Log.LogMessage("goWait 2", Scanner.Controlling.Log.LogMessage.eStatus.INFO));
			 if (state == StatusMessage.eState.Error) {
			 throw new Exception("Module in error mode");
			 }
			 if (state == StatusMessage.eState.Running) {
			 this.CmdStop();
			 if (!this.readAcknowledgement()) {
			 throw new Exception("Cannot stop module");
			 }
			 }
			 if (state == StatusMessage.eState.Sleeping) {
			 this.CmdStart();
			 if (!this.readAcknowledgement()) {
			 throw new Exception("Cannot start module");
			 }
			 }
			 //Scanner.Controlling.Log.LogObserver.Instance.acceptLog(new Scanner.Controlling.Log.LogMessage("goWait 3", Scanner.Controlling.Log.LogMessage.eStatus.INFO));
			 }

			 public void goHalt() {
			 StatusMessage.eState state = this.readStatus().State;
			 if (state == StatusMessage.eState.Error) {
			 throw new Exception("Module in error mode");
			 }
			 if (state != StatusMessage.eState.Sleeping) {
			 this.CmdHalt();
			 if (!this.readAcknowledgement()) {
			 throw new Exception("Cannot halt module");
			 }
			 }
			 }

			 #endregion


			 #endregion

			 #region Module Status

			 public delegate void ModuleStateChange(Module module, StatusMessage statusMessage);
			 public event ModuleStateChange ModuleStateChanged;

			 #endregion

			 #region Module Data Status

			 public delegate void ModuleDataChange(Module module, DataMessage dataMessage);
			 public event ModuleDataChange ModuleDataChanged;

			 public virtual string getReadableData() {
			 return "NOT IMPLEMENTED";
			 }

			 #endregion

			 }
			 }*/

			
		} /* namespace RoboCan */
	}
}
#endif /* MODULE_H_ */
