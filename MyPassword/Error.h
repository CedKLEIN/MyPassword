#pragma once

#include <string>

class Error{
public:
    Error()=default;
    Error(Error const&)=delete;
    Error& operator=(Error const&)=delete;

    enum ERROR{
        no_error,
        db_not_open,
        db_unique_key_already_exist,
        db_failed_to_close,
        db_failed_to_remove,
        db_failed_to_get_data,
        password_empty,
        password_confimation_not_the_same,
        file_not_generated
    };

    std::string getMsgError(const int& iError)const{
        std::string errorMsg{""};
        switch (iError) {
        case no_error:
            errorMsg="No error";
            break;
        case db_not_open:
            errorMsg="Db not open";
            break;
        case db_unique_key_already_exist:
            errorMsg="This name is already existing.";
            break;
        case db_failed_to_close:
            errorMsg="Database failed to close.";
            break;
        case db_failed_to_remove:
            errorMsg="Database failed to remove.";
            break;
        case db_failed_to_get_data:
            errorMsg="Couldn't get data from database.";
            break;
        case password_empty:
            errorMsg="The password should not be empty.";
            break;
        case password_confimation_not_the_same:
            errorMsg="Both passwords should be the same.";
            break;
        case file_not_generated:
            errorMsg="File not generated.";
            break;
        }

        return errorMsg;
    }
};
