/*
 * INode.h
 *
 *  Created on: Mar 14, 2013
 *      Author: root
 */

#ifndef INODE_H_
#define INODE_H_
#include <Poco/SharedPtr.h>
#include <Poco/Types.h>

namespace TBS {
namespace Robo {

class INode {
public:
	typedef Poco::SharedPtr<INode> Ptr;
	typedef std::string Name;


	virtual ~INode();

	virtual const Name & getName() const = 0;

};

} /* namespace Robo */
} /* namespace TBS */
#endif /* INODE_H_ */
