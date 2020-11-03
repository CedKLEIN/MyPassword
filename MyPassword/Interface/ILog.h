#pragma once

#include <string>

struct ILog{
    virtual void LOG_DEBUG(const std::string&)=0;
    virtual void LOG_INFO(const std::string&)=0;
    virtual void LOG_WARNING(const std::string&)=0;
    virtual void LOG_CRITICAL(const std::string&)=0;
};
