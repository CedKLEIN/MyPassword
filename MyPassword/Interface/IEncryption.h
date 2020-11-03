#pragma once

#include <QString>

struct IEncryption
{
    virtual QString encrypt(const QString&) const=0;
};
