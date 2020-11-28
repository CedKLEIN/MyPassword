#pragma once

#include <QString>

struct IEncryption
{
    virtual ~IEncryption()=default;
    virtual QString encrypt(const QString&) const=0;
};
