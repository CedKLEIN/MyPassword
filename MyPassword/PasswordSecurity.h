#pragma once

#include "Interface/IPasswordSecurity.h"

#include <QString>

class PasswordSecurity final : public IPasswordSecurity
{
public:
    PasswordSecurity()=default;
    PasswordSecurity(PasswordSecurity const&)=delete;
    PasswordSecurity& operator=(PasswordSecurity const&)=delete;

    int getSecurityLevel(const QString&)const override final;
    QString getIconSeverityLvl(const int)const override final;

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
