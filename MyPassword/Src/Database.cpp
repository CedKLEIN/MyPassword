#include "Database.h"

#include "Account.h"
#include "Utility.h"

#include <QDir>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QVariant>

#include <QDebug>

Database::Database(FacAccount& iFacAccount):
    _facAccount(iFacAccount)
{
    _db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"));
    _db.setDatabaseName(QDir::currentPath()+QLatin1String("/database.db"));

    dbOpen();
    QSqlQuery query(QStringLiteral("CREATE TABLE ACCOUNT(\
                                   NAME             VARCHAR(50) PRIMARY KEY NOT NULL,\
                                   LOGIN            VARCHAR(50),\
                                   PASSWORD         VARCHAR(50),\
                                   DETAILS          VARCHAR(200),\
                                   SECURITY_LVL     VARCHAR(1));"), _db);
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
        QString queryStr(QLatin1String("INSERT INTO ACCOUNT \
                                       ( NAME, LOGIN, PASSWORD, DETAILS, SECURITY_LVL) \
                                       VALUES \
                                       ('") + iData[0] +QLatin1String("',\
                                        '") + iData[1] +QLatin1String("',\
                                        '") + iData[2] +QLatin1String("',\
                                        '") + iData[3] +QLatin1String("',\
                                        '") + iData[4] +QLatin1String("');"));

                         QSqlQuery query(queryStr, _db);

                qDebug() << query.lastError().text();
        qDebug() << query.lastError().type();

        if(!dbClose())
            return Utility::ERROR::db_failed_to_close;

        if (query.lastError().isValid()){
            if(query.lastError().type()==1)
                return Utility::ERROR::db_name_already_exist;
            else if(query.lastError().type()==2)
                return Utility::ERROR::db_character_forbidden;
            return Utility::ERROR::db_failed_to_modify;
        }

        return Utility::ERROR::no_error ;
    }
    return Utility::ERROR::db_not_open;
}

int Database::retrieve()
{
    if(dbOpen())
    {
        QSqlQuery query(QStringLiteral("SELECT * FROM ACCOUNT"), _db);

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
        QString queryStr(QLatin1String("DELETE FROM ACCOUNT WHERE NAME='")+
                         iPrimaryKey+
                         QLatin1String("';"));
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
        QString queryStr(QLatin1String("UPDATE ACCOUNT SET LOGIN='")+
                         iData[1] +QLatin1String("',PASSWORD='")+
                iData[2]+QLatin1String("',DETAILS='")+
                iData[3]+QLatin1String("',SECURITY_LVL='")+
                iData[4]+QLatin1String("'WHERE NAME='")+
                iData[0]+QLatin1String("';"));

        QSqlQuery query(queryStr, _db);

        if(!dbClose())
            return Utility::ERROR::db_failed_to_close;

        if (query.lastError().isValid()){
            if(query.lastError().type()==1)
                return Utility::ERROR::db_name_already_exist;
            else if(query.lastError().type()==2)
                return Utility::ERROR::db_character_forbidden;
            return Utility::ERROR::db_failed_to_modify;
        }

        return  Utility::ERROR::no_error;
    }
    return Utility::ERROR::db_not_open;
}

int Database::removeAll()
{
    if(dbOpen())
    {
        QString queryStr(QStringLiteral("DELETE FROM ACCOUNT;"));
        QSqlQuery query(queryStr, _db);

        if(!dbClose())
            return Utility::ERROR::db_failed_to_close;

        if (query.lastError().isValid())
            return Utility::ERROR::db_failed_to_remove;

        return  Utility::ERROR::no_error;
    }
    return Utility::ERROR::db_not_open;
}
