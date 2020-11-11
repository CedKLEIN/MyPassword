#pragma once

#include "Interface/IGenerateFile.h"

#include <fstream>

class FacAccount;

class GenerateFile final: public IGenerateFile
{
public:
    GenerateFile(FacAccount&);
    GenerateFile(GenerateFile const&)=delete;
    GenerateFile& operator=(GenerateFile const&)=delete;

    int generate(const std::string&)override final;
private:
    FacAccount& _facAccount;
    std::ofstream _file;
};
