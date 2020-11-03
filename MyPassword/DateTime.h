#pragma once

#include <ctime>
#include <string>

class DateTime
{
public:
    DateTime()=default;
    DateTime(DateTime const&)=delete;
    DateTime& operator=(DateTime const&)=delete;

    std::string getDateTime()const;
    std::string getDate()const;
    std::string getTime()const;
};
