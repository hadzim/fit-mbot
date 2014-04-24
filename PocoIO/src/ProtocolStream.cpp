//
// DigestStream.cpp
//
// $Id: //poco/1.2/DeviceIO/src/ProtocolStream.cpp#1 $
//
// Library: DeviceIO
// Package: DeviceIO
// Module:  ProtocolStream
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/DeviceIO/ProtocolStream.h"
#include "Poco/DeviceIO/Protocol.h"
#include "Poco/BufferedBidirectionalStreamBuf.h"
#include <cstring>


using Poco::BufferedBidirectionalStreamBuf;


namespace Poco {
namespace DeviceIO {


ProtocolStreamBuf::ProtocolStreamBuf(Protocol* protocol):
	BufferedBidirectionalStreamBuf(STREAM_BUFFER_SIZE, std::ios::in | std::ios::out),
	_pProtocol(protocol)
{
	poco_check_ptr (_pProtocol);
	_pProtocol->duplicate();
}


ProtocolStreamBuf::~ProtocolStreamBuf()
{
	_pProtocol->release();
}


int ProtocolStreamBuf::readFromDevice(char* buffer, std::streamsize length)
{
	std::string str;
	_pProtocol->receive(str);
	std::size_t len = str.size() < length ? str.size() : length;
	std::memcpy(buffer, str.data(), len);
	return (int) len;
}


int ProtocolStreamBuf::writeToDevice(const char* buffer, std::streamsize length)
{
	_pProtocol->write(buffer, length, true);
	return length;
}


ProtocolIOS::ProtocolIOS(Protocol* protocol):	_buf(protocol)
{
	poco_ios_init(&_buf);
}


ProtocolIOS::~ProtocolIOS()
{
	try	{ _buf.sync(); }
	catch (...) { }
}


ProtocolStreamBuf* ProtocolIOS::rdbuf()
{
	return &_buf;
}


void ProtocolIOS::close()
{
	_buf.sync();
}


ProtocolOutputStream::ProtocolOutputStream(Protocol* pProtocol):
	ProtocolIOS(pProtocol),
	std::ostream(&_buf)
{
}


ProtocolOutputStream::~ProtocolOutputStream()
{
}


ProtocolInputStream::ProtocolInputStream(Protocol* pProtocol):
	ProtocolIOS(pProtocol),
	std::istream(&_buf)
{
}


ProtocolInputStream::~ProtocolInputStream()
{
}


ProtocolStream::ProtocolStream(Protocol* pProtocol): 
	ProtocolIOS(pProtocol), 
	std::iostream(&_buf)
{
}


ProtocolStream::~ProtocolStream()
{
}


} } // namespace Poco::DeviceIO
