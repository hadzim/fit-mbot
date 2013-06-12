/*
 * Response.h
 *
 *  Created on: 10.6.2013
 *      Author: JV
 */

#ifndef RESPONSE_H_
#define RESPONSE_H_

namespace MBot {

class Response {
public:

	typedef Poco::SharedPtr <Response> Ptr;

	Response();
	virtual ~Response();
};

} /* namespace MBot */
#endif /* RESPONSE_H_ */
