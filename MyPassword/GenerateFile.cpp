#include "GenerateFile.h"

#include "Account.h"
#include "Utility.h"

GenerateFile::GenerateFile(FacAccount& iFacAccount):
    _facAccount(iFacAccount){}

int GenerateFile::generate(const std::string& iPathFile){
    _file.open(iPathFile);

    if(_file.is_open()){
        for(const auto& account: _facAccount.getAll()){
            _file << account->getName().toStdString() << std::endl;
            _file << "Nom de compte : " << account->getLogin().toStdString() << std::endl;
            _file << "Description : " << account->getDetails().toStdString() << std::endl;
            _file << std::endl;
        }
        _file.close();
        return Utility::ERROR::no_error;
    }
    return Utility::ERROR::file_not_generated;
}
