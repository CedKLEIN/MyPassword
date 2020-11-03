#include "GenerateFile.h"

#include "Account.h"
#include "Error.h"

GenerateFile::GenerateFile(FacAccount& iFacAccount,Error& iError):
    _facAccount(iFacAccount),
    _error(iError)
{}

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
        return Error::ERROR::no_error;
    }
    return Error::ERROR::file_not_generated;
}
