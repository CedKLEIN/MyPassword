#pragma once

#include <QString>

class IDatabase{
public:
    virtual ~IDatabase()=default;
    virtual int create(const QStringList&)=0;
    virtual int retrieve()=0;
    virtual int remove(const QString&)=0;
    virtual int removeAll()=0;
    virtual int modify(const QStringList&)=0;
protected:
    virtual bool dbOpen()=0;
    virtual bool dbClose()=0;
};
