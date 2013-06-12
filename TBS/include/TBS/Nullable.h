/*
 * NullableType.h
 *
 *  Created on: 23.9.2011
 *      Author: Honza
 */

#ifndef NULLABLETYPE_H_
#define NULLABLETYPE_H_

#include <sstream>
#include <typeinfo>
#include <Poco/Timestamp.h>
#include <Poco/Exception.h>

namespace TBS {

	template<class BasicType>
	class Nullable {
			BasicType * value;
		public:

			typedef BasicType NestedType;

			///default false constructor
			Nullable() :
					value(NULL) {
			}
			//contruct by value
			Nullable(BasicType value) {
				this->value = new BasicType(value);
			}

			Nullable(const Nullable& from) {
				if (from.value) {
					this->value = new BasicType(*from.value);
				} else {
					this->value = NULL;
				}
			}

			Nullable& operator=(const Nullable& from) {
				if (this == &from) {
					return *this;
				}
				if (this->value) {
					delete this->value;
				}
				if (from.value) {
					this->value = new BasicType(*from.value);
				} else {
					this->value = NULL;
				}
				return *this;
			}

			~Nullable() {
				if (this->value)
					delete this->value;
			}

			void reset() {
				if (this->value) {
					delete this->value;
					this->value = NULL;
				}
			}

			void swap(Nullable<BasicType>& other) {
				BasicType * temp(this->value);
				this->value = other.value;
				other.value = temp;
			}

			/*void setByReference(BasicType & newValue){
			 this->value = newValue;
			 this->isNull = false;
			 }*/
			void set(const BasicType & newValue) {
				if (this->value) {
					*this->value = newValue;
				} else {
					this->value = new BasicType(newValue);
				}
			}

			bool isEmpty() const {
				return this->value == NULL;
			}
			bool isSet() const {
				return this->value != NULL;
			}

			BasicType getValue() {
				if (this->isEmpty()) {
					std::stringstream s;
					s << "Nullable: getValue Value is not set " << typeid(BasicType).name() << " sizeof(" << sizeof(BasicType) << ")";
					throw Poco::Exception(s.str());
				}
				return *this->value;
			}
			BasicType & getReference() {
				if (this->isEmpty()) {
					std::stringstream s;
					s << "Nullable: getReference Value is not set " << typeid(BasicType).name() << " sizeof(" << sizeof(BasicType) << ")";
					throw Poco::Exception(s.str());
				}
				return *this->value;
			}
			BasicType & getConstReference() const {
				if (this->isEmpty()) {
					std::stringstream s;
					s << "Nullable: getConstReference Value is not set " << typeid(BasicType).name() << " sizeof(" << sizeof(BasicType) << ")";
					throw Poco::Exception(s.str());
				}
				return const_cast<BasicType &>(*this->value);
			}

			bool operator ==(const Nullable<BasicType>& other) const {
				if (this->isEmpty()) {
					return other.isEmpty();
				} else if (other.isEmpty()) {
					return false;
				}

				return this->getConstReference() == other.getConstReference();
			}

			bool operator !=(const Nullable<BasicType>& other) const {
				return !(*this == other);
			}
	};

//typedef Nullable<Poco::Timestamp> NullableTimestamp;

}

#endif /* NULLABLETYPE_H_ */

