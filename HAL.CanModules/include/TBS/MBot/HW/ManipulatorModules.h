/*
 * ManipulatorModules.h
 *
 *  Created on: Jul 22, 2014
 *      Author: dron
 */

#ifndef MANIPULATORMODULES_H_
#define MANIPULATORMODULES_H_
#include "TBS/Robo/RoboCan/HW/CanModule.h"
#include "TBS/Robo/RoboCan/Task/ConsumingDataModuleTask.h"

namespace MBot {

	class ManipulatorRotationPositionTask: public TBS::Robo::RoboCan::ConsumingDataModuleTask {
		public:
			typedef Poco::SharedPtr<ManipulatorRotationPositionTask> Ptr;
			ManipulatorRotationPositionTask(std::string name, const TBS::Robo::RoboCan::InternalCanModule & module);
			virtual ~ManipulatorRotationPositionTask();

			struct Position {
					double encoder;
			};
			Poco::BasicEvent<Position> PositionChanged;


		private:
			void onDataReady(TBS::Robo::RoboCan::DataMessage & msg);
	};

	class ManipulatorRotationModule: public TBS::Robo::RoboCan::CanModule {

			enum TwoStateCommands {
				GoRel = 30, Enable = 32
			};

		public:
			ManipulatorRotationModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule) :
					TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule) {
			}
			virtual ~ManipulatorRotationModule() {
			}

			TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskGoRel(Poco::Int16 speed, Poco::Int16 timeInMs) const {
				TBS::Robo::RoboCan::RoboCanMessageData data;
				TBS::Robo::RoboCan::RoboCanMessageData::Short2 val;
				val.short1 = speed;
				val.short2 = timeInMs;
				data.setSHORT2(val);
				return new TBS::Robo::RoboCan::ModuleCommandTask("gorel", this->getInternalModule(),
						this->getInternalModule().composeCommand((int) GoRel, data));
			}

			TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskEnable(bool enable) const {
				TBS::Robo::RoboCan::RoboCanMessageData data;
				data.setUSHORT(enable ? 1 : 0);
				return new TBS::Robo::RoboCan::ModuleCommandAnyAckTask("enable", this->getInternalModule(),
						this->getInternalModule().composeCommand((int) Enable, data));
			}

			ManipulatorRotationPositionTask::Ptr taskConsumePosition() const {
				return new ManipulatorRotationPositionTask("consumerotpos", this->getInternalModule());
			}

	};

	class ManipulatorHolderModule: public TBS::Robo::RoboCan::CanModule {

			enum TwoStateCommands {
				GoRel = 30, SetThreshold = 31, Enable = 32
			};

		public:
			ManipulatorHolderModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule) :
					TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule) {
			}
			virtual ~ManipulatorHolderModule() {
			}

			TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskGoRel(Poco::Int16 speed, Poco::Int16 timeInMs) const {
				TBS::Robo::RoboCan::RoboCanMessageData data;
				TBS::Robo::RoboCan::RoboCanMessageData::Short2 val;
				val.short1 = speed;
				val.short2 = timeInMs;
				data.setSHORT2(val);
				return new TBS::Robo::RoboCan::ModuleCommandTask("gorel", this->getInternalModule(),
						this->getInternalModule().composeCommand((int) GoRel, data));
			}

			TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskSetThreshold(Poco::UInt16 thresh) const {
				TBS::Robo::RoboCan::RoboCanMessageData data;
				data.setUSHORT(thresh);
				return new TBS::Robo::RoboCan::ModuleCommandTask("setthresh", this->getInternalModule(),
						this->getInternalModule().composeCommand((int) SetThreshold, data));
			}

			TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskEnable(bool enable) const {
				TBS::Robo::RoboCan::RoboCanMessageData data;
				data.setUSHORT(enable ? 1 : 0);
				return new TBS::Robo::RoboCan::ModuleCommandAnyAckTask("enable", this->getInternalModule(),
						this->getInternalModule().composeCommand((int) Enable, data));
			}

	};

	class ManipulatorPositionTask: public TBS::Robo::RoboCan::ConsumingDataModuleTask {
		public:
			typedef Poco::SharedPtr<ManipulatorPositionTask> Ptr;
			ManipulatorPositionTask(std::string name, const TBS::Robo::RoboCan::InternalCanModule & module);
			virtual ~ManipulatorPositionTask();

			struct Position {
					double encoder1;
					double encoder2;
			};
			Poco::BasicEvent<Position> PositionChanged;
		private:
			void onDataReady(TBS::Robo::RoboCan::DataMessage & msg);
	};

	class ManipulatorMagneticModule: public TBS::Robo::RoboCan::CanModule {

		public:
			ManipulatorMagneticModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule);
			virtual ~ManipulatorMagneticModule();

			ManipulatorPositionTask::Ptr taskConsumePosition() const;
		private:
			std::string n;
	};

	class ManipulatorLightModule: public TBS::Robo::RoboCan::CanModule {

			enum TwoStateCommands {
				Enable = 30
			};

		public:
			ManipulatorLightModule(const std::string & name, TBS::Robo::RoboCan::ICanNode::RawPtr node, int numberWithinModule) :
					TBS::Robo::RoboCan::CanModule(name, node, numberWithinModule) {
			}
			virtual ~ManipulatorLightModule() {
			}

			TBS::Robo::RoboCan::ModuleCommandTask::Ptr taskEnable(bool enable) const {
				TBS::Robo::RoboCan::RoboCanMessageData data;
				data.setUSHORT(enable ? 1 : 0);
				return new TBS::Robo::RoboCan::ModuleCommandAnyAckTask("enable", this->getInternalModule(),
						this->getInternalModule().composeCommand((int) Enable, data));
			}

	};

} /* namespace MBot */

#endif /* MANIPULATORMODULES_H_ */
