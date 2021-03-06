//
// SQLiteCipherException.h
//
// $Id: //poco/1.4/Data/SQLiteCipher/include/Poco/Data/SQLiteCipher/SQLiteCipherException.h#1 $
//
// Library: Data/SQLiteCipher
// Package: SQLiteCipher
// Module:  SQLiteCipherException
//
// Definition of SQLiteCipherException.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
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


#ifndef SQLiteCipher_SQLiteCipherException_INCLUDED
#define SQLiteCipher_SQLiteCipherException_INCLUDED


#include "Poco/Data/SQLiteCipher/SQLiteCipher.h"
#include "Poco/Data/DataException.h"


namespace Poco {
namespace Data {
namespace SQLiteCipher {


POCO_DECLARE_EXCEPTION(SQLiteCipher_API, SQLiteCipherException, Poco::Data::DataException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, InvalidSQLStatementException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, InternalDBErrorException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, DBAccessDeniedException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, ExecutionAbortedException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, LockedException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, DBLockedException, LockedException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, TableLockedException, LockedException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, NoMemoryException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, ReadOnlyException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, InterruptException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, IOErrorException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, CorruptImageException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, TableNotFoundException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, DatabaseFullException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, CantOpenDBFileException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, LockProtocolException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, SchemaDiffersException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, RowTooBigException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, ConstraintViolationException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, DataTypeMismatchException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, ParameterCountMismatchException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, InvalidLibraryUseException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, OSFeaturesMissingException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, AuthorizationDeniedException, SQLiteCipherException)
POCO_DECLARE_EXCEPTION(SQLiteCipher_API, TransactionException, SQLiteCipherException)


} } } // namespace Poco::Data::SQLiteCipher


#endif
