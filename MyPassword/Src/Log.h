#pragma once

#include "Interface/ILog.h"
#include "DateTime.h"

#include <vector>

class Log final: public ILog
{
public:
    Log();
    Log(Log const&)=delete;
    Log& operator=(Log const&)=delete;

    void LOG_DEBUG(const std::string&)const override final;
    void LOG_INFO(const std::string&)const override final;
    void LOG_WARNING(const std::string&)const override final;
    void LOG_CRITICAL(const std::string&)const override final;

private:
    unsigned int getNbrLines()const;
    void getLogsFromStartingLine(int, std::vector<std::string>&)const;
    void clearLogFile()const;
    void fillLogsFileFromVector(const std::vector<std::string>&)const;
    void writeLog(const std::string&,const std::string&)const;

    DateTime _dateTime;
};
