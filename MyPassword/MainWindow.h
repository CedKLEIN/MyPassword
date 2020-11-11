#pragma once

#include "Account.h"

#include "AccountWindow.h"

#include <QStringList>
#include <QStringListModel>
#include <QListView>
#include <QList>
#include <QAbstractItemView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSqlDatabase>
#include <QWidget>

class IEncryption;
class NewAccountWindow;
class IDatabase;
class ILog;
class IGenerateFile;

class MainWindow final : public QWidget, public IListener
{
    Q_OBJECT
public:
    MainWindow(FacAccount&,
                      FacWindowDisplayAccount& iFacWindowDisplayAccount,
                      NewAccountWindow&,
                      IEncryption&,
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
    void openWindowNewAccount();
    void displayWindowAccount(const QModelIndex&);
    void generateFile();

private:
    FacAccount& _facAccount;
    FacWindowDisplayAccount& _facWindowDisplayAccount;
    NewAccountWindow& _windowNewAccount;
    IEncryption& _encryption;
    IDatabase& _db;
    ILog& _log;
    IGenerateFile& _generateFile;

    QHBoxLayout _layoutH;
    QLineEdit _filter;
    QListView _listAccountsView;
    QStringListModel _listAccountsModel;
    QStringList _accountsData;
    QStringList _accountsDataFilter;
    QVBoxLayout _layoutV;
    QPushButton _newAccountButton;
    QPushButton _generateFileButton;
};
