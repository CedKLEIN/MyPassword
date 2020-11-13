#pragma once

#include <QString>

class PasswordSecurity
{
public:
    enum SecurityLvl{NONE,VERY_LOW,LOW,MEDIUM,HIGH,VERY_HIGH};

    PasswordSecurity()=default;
    PasswordSecurity(PasswordSecurity const&)=delete;
    PasswordSecurity& operator=(PasswordSecurity const&)=delete;
    virtual ~PasswordSecurity()=default;

    int getSecurityLevel(const QString&)const;

private:
    bool hasAll(const QString&)const;
    bool hasOnlyNumberAndLowerAndUpper(const QString&)const;
    bool hasOnlyNumberAndLowerAndOthers(const QString&)const;
    bool hasOnlyNumberAndUpperAndOthers(const QString&)const;
    bool hasOnlyLowerAndUpperAndOthers(const QString&)const;
    bool hasOnlyNumberAndLower(const QString&)const;
    bool hasOnlyNumberAndUpper(const QString&)const;
    bool hasOnlyNumberAndOthers(const QString&)const;
    bool hasOnlyLowerAndUpper(const QString&)const;
    bool hasOnlyLowerAndOthers(const QString&)const;
    bool hasOnlyUpperAndOthers(const QString&)const;
    bool hasOneNumbers(const QString&)const;
    bool hasOneLetterLower(const QString&)const;
    bool hasOneLetterUpper(const QString&)const;
    bool hasOneOthers(const QString&)const;
    bool isOnlyNumbers(const QString&)const;
    bool isOnlyLettersLower(const QString&)const;
    bool isOnlyLettersUpper(const QString&)const;
    bool isOnlyOthers(const QString &)const;
};
