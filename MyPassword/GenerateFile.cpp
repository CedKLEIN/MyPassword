#include "GenerateFile.h"

#include "Account.h"
#include "Utility.h"

#include <fstream>

GenerateFile::GenerateFile(FacAccount& iFacAccount):
    _facAccount(iFacAccount){}

int GenerateFile::generate(const std::string& iPathFile) const{
    std::ofstream file(iPathFile);

    if(file.is_open()){
        for(const auto& account: _facAccount.getAll()){
            file << account->getName().toStdString() << std::endl;
            file << "Nom de compte : " << account->getLogin().toStdString() << std::endl;
            file << "Description : " << account->getDetails().toStdString() << std::endl;
            file << std::endl;
        }
        file.close();
        return Utility::ERROR::no_error;
    }
    return Utility::ERROR::file_not_generated;
}
