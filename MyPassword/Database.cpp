#include "Database.h"

#include "Account.h"
#include "Utility.h"

#include <QDebug>
#include <QDir>
#include <QSqlQuery>
#include <QSqlError>

Database::Database(FacAccount& iFacAccount):
    _facAccount(iFacAccount)
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(QDir::currentPath()+"/database.db");

    dbOpen();
    QSqlQuery query("CREATE TABLE ACCOUNT(\
                    NAME             VARCHAR(50) PRIMARY KEY NOT NULL,\
                    LOGIN            VARCHAR(50),\
                    PASSWORD         VARCHAR(50),\
                    DETAILS          VARCHAR(200),\
                    SECURITY_LVL     VARCHAR(1));", _db);
    dbClose();
}

Database::~Database(){
    _db.removeDatabase(QSqlDatabase::defaultConnection);
}

bool Database::dbOpen()
{
    _db.open();
    return _db.isOpen();
}

bool Database::dbClose()
{
    if(_db.isOpen())
        _db.close();

    return !_db.isOpen();
}

int Database::create(const QStringList& iData){
    if(dbOpen())
    {
        QString queryStr("INSERT INTO ACCOUNT \
                         ( NAME, LOGIN, PASSWORD, DETAILS, SECURITY_LVL) \
                         VALUES \
                         ('" + iData[0].toLocal8Bit() +"',\
                          '" + iData[1].toLocal8Bit() +"',\
                          '" + iData[2].toLocal8Bit() +"',\
                          '" + iData[3].toLocal8Bit() +"',\
                          '" + iData[4] +"');");

                QSqlQuery query(queryStr, _db);

        if(!dbClose())
            return Utility::ERROR::db_failed_to_close;

        if (query.lastError().isValid())
            return Utility::ERROR::db_unique_key_already_exist;

        return Utility::ERROR::no_error ;
    }
    return Utility::ERROR::db_not_open;
}

int Database::retrieve()
{
    if(dbOpen())
    {
        QSqlQuery query("SELECT * FROM ACCOUNT", _db);

        if (query.lastError().isValid())
            return Utility::ERROR::db_failed_to_get_data;

        while(query.next()) {
            _facAccount.create(query.value(0).toString(),
                               query.value(1).toString(),
                               query.value(2).toString(),
                               query.value(3).toString(),
                               query.value(4).toInt());

        }

        if(!dbClose())
            return Utility::ERROR::db_failed_to_close;

        return  Utility::ERROR::no_error;
    }
    return Utility::ERROR::db_not_open;
}

int Database::remove(const QString& iPrimaryKey)
{
    if(dbOpen())
    {
        QString queryStr("DELETE FROM ACCOUNT WHERE NAME='" + iPrimaryKey + "';");
        QSqlQuery query(queryStr, _db);

        if(!dbClose())
            return Utility::ERROR::db_failed_to_close;

        if (query.lastError().isValid())
            return Utility::ERROR::db_failed_to_remove;

        return  Utility::ERROR::no_error;
    }
    return Utility::ERROR::db_not_open;
}

int Database::modify(const QStringList& iData)
{
    if(dbOpen())
    {
        QString queryStr("UPDATE ACCOUNT SET \
                         LOGIN='"+ iData[1] +"',\
                         PASSWORD='"+ iData[2] +"',\
                         DETAILS='"+ iData[3] +"',\
                         SECURITY_LVL='"+ iData[4] +"'\
                WHERE NAME='"+ iData[0] +"';");

                QSqlQuery query(queryStr, _db);

        if(!dbClose())
            return Utility::ERROR::db_failed_to_close;

        if (query.lastError().isValid())
            return Utility::ERROR::db_failed_to_modify;

        return  Utility::ERROR::no_error;
    }
    return Utility::ERROR::db_not_open;
}
