/*
 * IMotorNode.h
 *
 *  Created on: Mar 14, 2013
 *      Author: root
 */

#ifndef IMBOTHWMOTORNODE_H_
#define IMBOTHWMOTORNODE_H_

#include "TBS/Robo/INode.h"

namespace MBot {
namespace HW {

class IMotorNode: public TBS::Robo::INode {
public:
	IMotorNode();
	virtual ~IMotorNode();
};

} /* namespace HW */
} /* namespace MBot */
#endif /* IMBOTHWMOTORNODE_H_ */
