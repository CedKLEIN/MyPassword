#pragma once

#include "Interface/IDatabase.h"

#include <QSqlDatabase>

#include <memory>

class FacAccount;
class Error;

class Database final: public IDatabase
{
public:
    Database(FacAccount&,Error&);
    Database(Database const&)=delete;
    Database& operator=(Database const&)=delete;
    virtual ~Database()=default;

    int create(const QStringList&) final;
    int retrieve() final;
    int remove(const QString&) final;
    int modify(const QStringList&) final;

private:
    bool dbOpen();
    bool dbClose();
    FacAccount& _facAccount;
    Error& _error;
    QSqlDatabase _db;
};
