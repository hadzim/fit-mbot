/*
 * Services.h
 *
 *  Created on: Oct 7, 2013
 *      Author: root
 */

#ifndef TBS_SERVICES_H_
#define TBS_SERVICES_H_
#include <Poco/SharedPtr.h>
#include <Poco/Exception.h>
#include <vector>
#include "TBS/TBSServices.h"
namespace TBS {
	namespace Services {

		typedef std::vector <unsigned char> Binary;

		class TBSSERV_API ICommChannelHolder {
			public:
				typedef Poco::SharedPtr <ICommChannelHolder> Ptr;
				virtual ~ICommChannelHolder();
		};

		class TBSSERV_API IStoppableCommChannelHolder : public ICommChannelHolder {
			public:
				typedef Poco::SharedPtr <IStoppableCommChannelHolder> Ptr;
				virtual ~IStoppableCommChannelHolder();

				virtual void start() = 0;
				virtual void stop() = 0;
				virtual bool isRunning() = 0;
		};


		class TBSSERV_API IServer {
			public:
				typedef Poco::SharedPtr<IServer> Ptr;

				virtual ~IServer();
		};


		POCO_DECLARE_EXCEPTION(TBSSERV_API, ServiceException, Poco::Exception);
		POCO_DECLARE_EXCEPTION(TBSSERV_API, RuntimeServiceException, ServiceException);
		POCO_DECLARE_EXCEPTION(TBSSERV_API, ChannelServiceException, ServiceException);

	} // namespace Services

} // namespace TBS



#endif /* SERVICES_H_ */
