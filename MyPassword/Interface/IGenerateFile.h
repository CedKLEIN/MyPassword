#pragma once

#include <string>

struct IGenerateFile{
    virtual int generate(const std::string&)=0;
};
