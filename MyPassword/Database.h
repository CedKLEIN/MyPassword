#pragma once

#include "Interface/IDatabase.h"

#include <QSqlDatabase>

#include <memory>

class FacAccount;

class Database final: public IDatabase
{
public:
    Database(FacAccount&);
    ~Database();
    Database(Database const&)=delete;
    Database& operator=(Database const&)=delete;

    int create(const QStringList&) override final;
    int retrieve() override final;
    int remove(const QString&) override final;
    int modify(const QStringList&) override final;
    int removeAll() override final;

private:
    bool dbOpen() override final;
    bool dbClose() override final;
    FacAccount& _facAccount;
    QSqlDatabase _db;
};
