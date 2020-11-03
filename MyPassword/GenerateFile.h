#pragma once

#include "Interface/IGenerateFile.h"

#include <fstream>

class FacAccount;
class Error;

class GenerateFile final: public IGenerateFile
{
public:
    GenerateFile(FacAccount&, Error&);
    GenerateFile(GenerateFile const&)=delete;
    GenerateFile& operator=(GenerateFile const&)=delete;

    int generate(const std::string&)final;
private:
    FacAccount& _facAccount;
    Error& _error;
    std::ofstream _file;
};
