/*
 * IModule.h
 *
 *  Created on: Mar 14, 2013
 *      Author: root
 */

#ifndef IMODULE_H_
#define IMODULE_H_
#include <string>
#include <Poco/SharedPtr.h>

namespace TBS {
namespace Robo {

class IModule {
public:
	typedef Poco::SharedPtr<IModule> Ptr;
	typedef std::string Name;

	virtual ~IModule();

	virtual const Name & getName() const  = 0;
};

} /* namespace Robo */
} /* namespace TBS */
#endif /* IMODULE_H_ */
