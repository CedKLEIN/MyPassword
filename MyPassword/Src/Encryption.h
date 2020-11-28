#pragma once

#include "Interface/IEncryption.h"

#include <QString>

class Encryption final: public IEncryption
{
public:
    Encryption()=default;
    Encryption(Encryption const&)=delete;
    Encryption& operator=(Encryption const&)=delete;

    QString encrypt(const QString&) const;
};
