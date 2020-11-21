#pragma once

#include <QString>

struct ISettings{
    virtual ~ISettings()=default;
    virtual QString getLanguage()const=0;
    virtual void setLanguage(const QString&)=0;
    virtual bool isSecurityIconShow()const=0;
    virtual void setIsSecurityIconShow(bool)=0;
};

