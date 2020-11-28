#pragma once

#include <string>

struct ILog{
    virtual ~ILog()=default;
    virtual void LOG_DEBUG(const std::string&)const=0;
    virtual void LOG_INFO(const std::string&)const=0;
    virtual void LOG_WARNING(const std::string&)const=0;
    virtual void LOG_CRITICAL(const std::string&)const=0;
};
