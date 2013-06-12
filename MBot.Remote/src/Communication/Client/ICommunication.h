/*
 * ICommunication.h
 *
 *  Created on: 10.6.2013
 *      Author: JV
 */

#ifndef ICOMMUNICATION_H_
#define ICOMMUNICATION_H_

namespace MBot {
namespace Client {

class ICommunication {
public:

	typedef Poco::SharedPtr <ICommunication> Ptr;

	ICommunication();
	virtual ~ICommunication();

	Response::Ptr sendRequest(Request::Ptr request) = 0;
};

} /* namespace Client */
} /* namespace MBot */
#endif /* ICOMMUNICATION_H_ */
