/*
 * RoboCanMessageData.cpp
 *
 *  Created on: 4.3.2013
 *      Author: JV
 */

#include "TBS/Robo/RoboCan/Communicaton/RoboCanMessageData.h"
#include <Poco/Exception.h>
namespace TBS {
	namespace Robo {
		namespace RoboCan {

			RoboCanMessageData::RoboCanMessageData() {
				this->reset();
			}

			RoboCanMessageData::~RoboCanMessageData() {

			}

			void RoboCanMessageData::writeToMessage(RoboCanMessage & message) const {

				message.getCanMessageRef().length = (Poco::UInt8)(this->length + 4);
				message.setDataType(this->dataType);

				message.getCanMessageRef().b4 = this->b0;
				message.getCanMessageRef().b5 = this->b1;
				message.getCanMessageRef().b6 = this->b2;
				message.getCanMessageRef().b7 = this->b3;
			}

			void RoboCanMessageData::readFromMessage(const RoboCanMessage & message) {

				CanMessage msg = message.getCanMessage();
				this->length = (Poco::UInt8)(msg.length - 4);
				this->dataType = message.getDataType();

				this->b0 = msg.b4;
				this->b1 = msg.b5;
				this->b2 = msg.b6;
				this->b3 = msg.b7;
			}

			void RoboCanMessageData::checkLength(int length) const {
				if (this->length != length) {
					throw new Poco::Exception("RoboCan length missmatch");
				}
			}
			void RoboCanMessageData::checkType(RoboCanMessage::eDataType type) const {
				if (this->dataType != type) {
					throw new Poco::Exception("RoboCan dataType missmatch");
				}
			}

			void RoboCanMessageData::reset() {
				this->length = 0;
				this->dataType = RoboCanMessage::DT_NODATA;
			}

			Poco::UInt8 RoboCanMessageData::getUCHAR() const {
				this->checkLength(1);
				this->checkType(RoboCanMessage::DT_UCHAR);
				return b0;
			}
			void RoboCanMessageData::setUCHAR(Poco::UInt8 value) {
				this->length = 1;
				this->dataType = RoboCanMessage::DT_UCHAR;
				this->b0 = value;
			}

			Poco::Int8 RoboCanMessageData::getCHAR() const {
				this->checkLength(1);
				this->checkType(RoboCanMessage::DT_CHAR);
				return b0;
			}
			void RoboCanMessageData::setCHAR(Poco::Int8 value) {
				this->length = 1;
				this->dataType = RoboCanMessage::DT_CHAR;
				this->b0 = value;
			}

			Poco::Int16 RoboCanMessageData::getSHORT() const {
				this->checkLength(2);
				this->checkType(RoboCanMessage::DT_SHORT);
				return (Poco::Int16)(this->b0 << 8 | this->b1);
			}
			void RoboCanMessageData::setSHORT(Poco::Int16 value) {
				this->length = 2;
				this->dataType = RoboCanMessage::DT_SHORT;
				this->b1 = (Poco::UInt8)(value & 0xFF);
				this->b0 = (Poco::UInt8)(value >> 8 & 0xFF);
			}

			Poco::UInt16 RoboCanMessageData::getUSHORT() const {
				this->checkLength(2);
				this->checkType(RoboCanMessage::DT_USHORT);
				return (Poco::Int16)(this->b0 << 8 | this->b1);
			}
			void RoboCanMessageData::setUSHORT(Poco::UInt16 value) {
				this->length = 2;
				this->dataType = RoboCanMessage::DT_USHORT;
				this->b1 = (Poco::UInt8)(value & 0xFF);
				this->b0 = (Poco::UInt8)(value >> 8 & 0xFF);
			}

			Poco::Int32 RoboCanMessageData::getLONG() const {
				this->checkLength(4);
				this->checkType(RoboCanMessage::DT_LONG);
				return (Poco::Int32)(b0 << 24 | b1 << 16 | b2 << 8 | b3);
			}
			void RoboCanMessageData::setLONG(Poco::Int32 value) {
				this->length = 4;
				this->dataType = RoboCanMessage::DT_LONG;
				b3 = (Poco::UInt8)(value & 0xFF);
				b2 = (Poco::UInt8)(value >> 8 & 0xFF);
				b1 = (Poco::UInt8)(value >> 16 & 0xFF);
				b0 = (Poco::UInt8)(value >> 24 & 0xFF);
			}

			Poco::UInt32 RoboCanMessageData::getULONG() const {
				this->checkLength(4);
				this->checkType(RoboCanMessage::DT_ULONG);
				return (Poco::Int32)(b0 << 24 | b1 << 16 | b2 << 8 | b3);
			}

			void RoboCanMessageData::setULONG(Poco::UInt32 value) {
				this->length = 4;
				this->dataType = RoboCanMessage::DT_ULONG;
				b3 = (Poco::UInt8)(value & 0xFF);
				b2 = (Poco::UInt8)(value >> 8 & 0xFF);
				b1 = (Poco::UInt8)(value >> 16 & 0xFF);
				b0 = (Poco::UInt8)(value >> 24 & 0xFF);
			}

			RoboCanMessageData::UShort2 RoboCanMessageData::getUSHORT2() const {
				RoboCanMessageData::UShort2 u;

				this->checkLength(4);
				this->checkType(RoboCanMessage::DT_USHORT2);
				u.short1 = (Poco::UInt16)(this->b0 << 8 | this->b1);
				u.short2 = (Poco::UInt16)(this->b2 << 8 | this->b3);
				return u;
			}
			void RoboCanMessageData::setUSHORT2(UShort2 value) {
				this->length = 4;
				this->dataType = RoboCanMessage::DT_USHORT2;
				this->b1 = (Poco::UInt8)(value.short1 & 0xFF);
				this->b0 = (Poco::UInt8)(value.short1 >> 8 & 0xFF);

				this->b3 = (Poco::UInt8)(value.short2 & 0xFF);
				this->b2 = (Poco::UInt8)(value.short2 >> 8 & 0xFF);
			}

			RoboCanMessageData::Short2 RoboCanMessageData::getSHORT2() const {
				RoboCanMessageData::Short2 u;

				this->checkLength(4);
				this->checkType(RoboCanMessage::DT_SHORT2);
				u.short1 = (Poco::Int16)(this->b0 << 8 | this->b1);
				u.short2 = (Poco::Int16)(this->b2 << 8 | this->b3);
				return u;
			}
			void RoboCanMessageData::setSHORT2(Short2 value) {
				this->length = 4;
				this->dataType = RoboCanMessage::DT_SHORT2;
				this->b1 = (Poco::UInt8)(value.short1 & 0xFF);
				this->b0 = (Poco::UInt8)(value.short1 >> 8 & 0xFF);

				this->b3 = (Poco::UInt8)(value.short2 & 0xFF);
				this->b2 = (Poco::UInt8)(value.short2 >> 8 & 0xFF);
			}

			RoboCanMessageData::UChar4 RoboCanMessageData::getUCHAR4() const {
				RoboCanMessageData::UChar4 u;

				this->checkLength(4);
				this->checkType(RoboCanMessage::DT_UCHAR4);
				u.uchar1 = (Poco::UInt8)(this->b0);
				u.uchar2 = (Poco::UInt8)(this->b1);
				u.uchar3 = (Poco::UInt8)(this->b2);
				u.uchar4 = (Poco::UInt8)(this->b3);
				return u;
			}
			void RoboCanMessageData::setUCHAR4(UChar4 value){
				this->length = 4;
				this->dataType = RoboCanMessage::DT_UCHAR4;
				this->b0 = (Poco::UInt8)value.uchar1;
				this->b1 = (Poco::UInt8)value.uchar2;
				this->b2 = (Poco::UInt8)value.uchar3;
				this->b3 = (Poco::UInt8)value.uchar4;
			}

		}

	}
}
