#pragma once

#include <string>

struct IDateTime{
    virtual std::string getDateTime()const=0;
    virtual std::string getDate()const=0;
    virtual std::string getTime()const=0;
};
