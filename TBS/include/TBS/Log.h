/*
 * Log.h
 *
 *  Created on: 12.10.2011
 *      Author: Honza
 */

#ifndef TSERIES_LOG_H_
#define TSERIES_LOG_H_

#include <Poco/Logger.h>
#include <Poco/LogStream.h>
#include <Poco/NullStream.h>

#define LOG_THREAD  "THREAD"
#define LOG_TIME 	"TIME"

#define LOG_STREAM { Poco::LogStream(Poco::Logger::get(__FILE__)) str; { str
#define LOG_STREAM_END " (in " << __func__ << ":" << __LINE__ << ")"<< std::endl; }}

#define LOG_NAMED_FATAL(name) { Poco::Logger & pl = Poco::Logger::get(name); Poco::LogStream str(pl); if (pl.fatal()) { str.fatal()
#define LOG_NAMED_CRITICAL(name) { Poco::Logger & pl = Poco::Logger::get(name); Poco::LogStream str(pl); if (pl.critical()) { str.critical()
#define LOG_NAMED_ERROR(name) { Poco::Logger & pl = Poco::Logger::get(name); Poco::LogStream str(pl); if (pl.error()) { str.error()
#define LOG_NAMED_WARNING(name)  { Poco::Logger & pl = Poco::Logger::get(name); Poco::LogStream str(pl); if (pl.warning()) { str.warning()
#define LOG_NAMED_NOTICE(name)  { Poco::Logger & pl = Poco::Logger::get(name); Poco::LogStream str(pl); if (pl.notice()) { str.notice()
#define LOG_NAMED_INFO(name) { Poco::Logger & pl = Poco::Logger::get(name); Poco::LogStream str(pl); if (pl.information()) { str.information()
#define LOG_NAMED_DEBUG(name) { Poco::Logger & pl = Poco::Logger::get(name); Poco::LogStream str(pl); if (pl.debug()) { str.debug()
#define LOG_NAMED_TRACE(name) { Poco::Logger & pl = Poco::Logger::get(name); Poco::LogStream str(pl); if (pl.trace()) { str.trace()

#define LOG_FATAL 	 LOG_NAMED_FATAL("TBS")
#define LOG_CRITICAL LOG_NAMED_CRITICAL("TBS")
#define LOG_ERROR 	 LOG_NAMED_ERROR("TBS")
#define LOG_WARNING  LOG_NAMED_WARNING("TBS")
#define LOG_NOTICE   LOG_NAMED_NOTICE("TBS")
#define LOG_INFO     LOG_NAMED_INFO("TBS")
#define LOG_DEBUG    LOG_NAMED_DEBUG("TBS")
#define LOG_TRACE    LOG_NAMED_TRACE("TBS")

#define LOG_END std::endl; }}

namespace TBS {

	void initLogs(std::string logName, int level = 4, std::string logDir = "");

	void separeLog(std::string logName, std::string fileName);

}

#endif /* LOG_H_ */
