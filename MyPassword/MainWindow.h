#pragma once

#include "Account.h"

#include "AccountWindow.h"

#include <QStringList>
#include <QStringListModel>
#include <QListView>
#include <QList>
#include <QAbstractItemView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSqlDatabase>
#include <QWidget>

class IEncryption;
class IPasswordSecurity;
class SecurityLevelWindow;
class NewAccountWindow;
class IDatabase;
class ILog;
class IGenerateFile;

class MainWindow final : public QWidget, public IListener
{
    Q_OBJECT
public:
    MainWindow(FacAccount&,
               FacDisplayAccountWindow& iFacWindowDisplayAccount,
               NewAccountWindow&,
               IEncryption&,
               IPasswordSecurity&,
               SecurityLevelWindow&,
               IDatabase&,
               ILog&,
               IGenerateFile&);
    MainWindow(MainWindow const&)=delete;
    MainWindow& operator=(MainWindow const&)=delete;
    void onEventClose() override;
    void closeEvent(QCloseEvent *) override;

public slots:
    void filterChanged(const QString&);
    void retrieveAccounts();
    void setModelFromDataList(const QStringList &);
    void openWindowNewAccount();
    void displayWindowAccount(const QModelIndex&);
    void generateFile();

private:
    FacAccount& _facAccount;
    FacDisplayAccountWindow& _facWindowDisplayAccount;
    NewAccountWindow& _windowNewAccount;
    IEncryption& _encryption;
    IPasswordSecurity& _passwordSecurity;
    SecurityLevelWindow& _securityLevelWindow;
    IDatabase& _db;
    ILog& _log;
    IGenerateFile& _generateFile;

    QHBoxLayout _layoutH;
    QLineEdit _filter;
    QListView _listAccountsView;
    QStandardItemModel _listAccountsModel;
    QStringList _accountsData;
    QStringList _accountsDataFilter;
    QVBoxLayout _layoutV;
    QPushButton _newAccountButton;
    QPushButton _generateFileButton;
};
