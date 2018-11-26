#include <syslog.h>
#include <iostream>
#include <string>
#include <sstream>
#include <osapi/Log.hpp>
#include <osapi/ILogOutput.hpp>
#include <osapi/Utility.hpp>


class Syslog : public osapi::ILogOutput
{
public:
  Syslog(const std::string& ident, int option = LOG_PID);
  Syslog(const std::string& ident, int option, int facility);

  virtual void log(osapi::Level       lvl, 
                   const char*        fileName, 
                   int                lineNo, 
                   const char*        functionName,
                   osapi::Time        timeStamp,
                   const std::string& logString);

  ~Syslog();
};


Syslog::Syslog(const std::string& ident, int option)
{
  openlog(ident.c_str(), option, LOG_USER);
}


Syslog::Syslog(const std::string& ident, int option, int facility)
{
  openlog(ident.c_str(), option, facility);  
}


void Syslog::log(osapi::Level       lvl, 
                 const char*        fileName, 
                 int                lineNo, 
                 const char*        functionName,
                 osapi::Time        timeStamp,
                 const std::string& logString)
{
  int syslogLevel = LOG_DEBUG;

  switch(lvl)
  {
    case osapi::Emergency:
      syslogLevel = LOG_EMERG;
      break;
      
    case osapi::Alert:
      syslogLevel = LOG_ALERT;
      break;

    case osapi::Critical:
      syslogLevel = LOG_CRIT;
      break;

    case osapi::Error:
      syslogLevel = LOG_ERR;
      break;

    case osapi::Warning:
      syslogLevel = LOG_WARNING;
      break;

    case osapi::Notice:
      syslogLevel = LOG_NOTICE;
      break;

    case osapi::Informational:
      syslogLevel = LOG_INFO;
      break;

    case osapi::Debug:
      syslogLevel = LOG_DEBUG;
      break;
  }

  std::stringstream ss;
  
  ss << " (" << fileName << ":" << lineNo << " - " << functionName << ") " 
     << logString;
  
  syslog(syslogLevel, "%s", ss.str().c_str());
}


Syslog::~Syslog()
{
  closelog();
}


int main(int argc, char* argv[])
{
  OSAPI_LOG_DBG("Hello");
  
  Syslog* sys = new Syslog("TestLog");
  osapi::logSetNewOutput(sys);

  OSAPI_LOG_DBG("Hello");

  osapi::sleep(10000);
}
