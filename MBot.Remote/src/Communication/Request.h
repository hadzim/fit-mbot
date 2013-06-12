/*
 * Request.h
 *
 *  Created on: 10.6.2013
 *      Author: JV
 */

#ifndef REQUEST_H_
#define REQUEST_H_

#include <Poco/SharedPtr.h>

namespace MBot {

class Request {
public:
	typedef Poco::SharedPtr <Request> Ptr;
	Request();
	virtual ~Request();
};

} /* namespace MBot */
#endif /* REQUEST_H_ */
