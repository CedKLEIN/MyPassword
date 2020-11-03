#pragma once

#include "Interface/ILog.h"
#include "DateTime.h"

#include <iostream>
#include <fstream>

class Log final: public ILog
{
public:
    Log()=default;
    Log(Log const&)=delete;
    Log& operator=(Log const&)=delete;

    void LOG_DEBUG(const std::string&)final;
    void LOG_INFO(const std::string&)final;
    void LOG_WARNING(const std::string&)final;
    void LOG_CRITICAL(const std::string&)final;

    void writeLog(const std::string&,const std::string&);

private:
    DateTime _dateTime;
    std::ofstream _file;
};
