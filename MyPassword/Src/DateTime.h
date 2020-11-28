#pragma once

#include "Interface/IDateTime.h"

#include <string>

class DateTime final : public IDateTime
{
public:
    DateTime()=default;
    DateTime(DateTime const&)=delete;
    DateTime& operator=(DateTime const&)=delete;

    std::string getDateTime()const override final;
    std::string getDate()const override final;
    std::string getTime()const override final;
};
