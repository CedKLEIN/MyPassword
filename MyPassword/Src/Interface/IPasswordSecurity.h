#pragma once

#include <QString>

struct IPasswordSecurity{
    virtual ~IPasswordSecurity()=default;
    enum SecurityLvl{NONE,VERY_LOW,LOW,MEDIUM,HIGH,VERY_HIGH};
    virtual int getSecurityLevel(const QString&)const=0;
    virtual QString getIconSeverityLvl(int)const=0;
};
