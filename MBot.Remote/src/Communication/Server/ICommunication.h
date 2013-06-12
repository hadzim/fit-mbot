/*
 * ICommunication.h
 *
 *  Created on: 10.6.2013
 *      Author: JV
 */

#ifndef ISCOMMUNICATION_H_
#define ISCOMMUNICATION_H_

#include <Poco/BasicEvent.h>

namespace MBot {
namespace Server {

class ICommunication {

public:
	typedef Poco::SharedPtr <ICommunication> Ptr;

	struct RequestResponse {
		Request::Ptr request;
		Response::Ptr response;
	};

	ICommunication();
	virtual ~ICommunication();

	Poco::BasicEvent <RequestResponse> RequestResponse;
};

} /* namespace Server */
} /* namespace MBot */
#endif /* ICOMMUNICATION_H_ */
