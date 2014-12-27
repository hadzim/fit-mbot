//------------------------------------------------------------------------------
//
//  Project:   VG20102014024
//             Robot for search of human beings in crushes and avalanches
//
//             Brno University of Technology
//             Faculty of Information Technology
//
//------------------------------------------------------------------------------
//
//             This project was financially supported by project
//                  VG20102014024 funds provided by MV CR.
//
//------------------------------------------------------------------------------
/*!

@file
@brief     Header file
@details   Details
@authors   Jan Vana (<ivanajan@fit.vutbr.cz>)
@date      2010-2014
@note      This project was supported by project funds of the MV CR grant VG20102014024.

*/
#ifndef CONSUMINGMODULETASK_H_
#define CONSUMINGMODULETASK_H_
#include "TBS/Task/Task.h"
#include "TBS/NotificationWorker.h"
#include "TBS/Robo/RoboCan/Communicaton/IChannel.h"
#include "TBS/Robo/RoboCan/HW/InternalCanModule.h"
#include "TBS/Robo/RoboCan/HW/ICanModule.h"
#include "TBS/Nullable.h"
#include "TBS/Robo/RoboCan/Communicaton/DataMessage.h"

namespace TBS {
	namespace Robo {
		namespace RoboCan {

			class ConsumingDataModuleTask: public TBS::Task::Task {
				public:
					typedef Poco::SharedPtr<ConsumingDataModuleTask> Ptr;
					ConsumingDataModuleTask(std::string name, const InternalCanModule & module);
					virtual ~ConsumingDataModuleTask();
				protected:
					Poco::BasicEvent<DataMessage> DataMessageReady;
				private:
					void onOuterActivation(TBS::Activation & a);
					void packetRetrieved(CanMessage & m);
				private:
					TBS::NotificationWorker::Ptr nw;
					IChannel::Ptr channel;
					ICanModule::CanID canID;

					TBS::Nullable<DataMessage> currentMessage;
			};

		}
	}
} /* namespace MBot */
#endif /* CONSUMINGMODULETASK_H_ */
