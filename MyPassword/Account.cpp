#include "Account.h"

#include <QDebug>
#include <QByteArray>
#include <QCryptographicHash>

Account::Account(const QString& iName,
                 const QString& iLogin,
                 const QString& iPassword,
                 const QString& iDetails,
                 const int iSecurityLvl)
    : _name(iName),
      _login(iLogin),
      _password(iPassword),
      _details(iDetails),
      _severityLvl(iSecurityLvl){}

QString Account::getName() const{
    return _name;
}

QString Account::getLogin() const{
    return _login;
}

QString Account::getPassword() const{
    return _password;
}

QString Account::getDetails() const{
    return _details;
}

int Account::getSeverityLvl() const{
    return _severityLvl;
}
