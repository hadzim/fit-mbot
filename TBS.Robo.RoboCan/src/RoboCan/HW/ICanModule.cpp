/*
 * IModule.cpp
 *
 *  Created on: 4.3.2013
 *      Author: JV
 */

#include "TBS/Robo/RoboCan/HW/ICanModule.h"
namespace TBS {
	namespace Robo {
		namespace RoboCan {
			

				ICanModule::ICanModule(std::string name, ICanNode::RawPtr node, int numberWithinNode_) :
						name(name), node(node), numberWithinNode(numberWithinNode_) {

				}

				ICanModule::~ICanModule() {

				}

				ICanModule::CanID ICanModule::getCanID() const {
					return this->node->getCanID() + numberWithinNode;
				}
				ICanModule::CanID ICanModule::getNodeID() const {
					return this->node->getCanNodeID();
				}
				/*
				 int IModule::getNumberWithinNode() const {
				 return this->numberWithinNode;
				 }
				 void IModule::setNumberWithinNode(int n) {
				 this->numberWithinNode = n;
				 }*/

				const ICanModule::Name & ICanModule::getName() const {
					return this->name;
				}

			
		} /* namespace RoboCan */
	}
}
