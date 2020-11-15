#pragma once

#include "Account.h"

#include "Interface/IListener.h"

#include <QStringList>
#include <QListView>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class AccountWindow;
class IPasswordSecurity;
class CreateAccountTab;
class IDatabase;
class ILog;

class AccountTab final : public QWidget, public IListener
{
    Q_OBJECT
public:
    AccountTab(FacAccount&,
               AccountWindow&,
               CreateAccountTab&,
               IPasswordSecurity&,
               IDatabase&,
               ILog&);
    AccountTab(AccountTab const&)=delete;
    AccountTab& operator=(AccountTab const&)=delete;
    ~AccountTab();
    void onEventClose() override;

private slots:
    void filterChanged(const QString&);
    void retrieveAccounts();
    void setModelFromDataList(const QStringList&);
    void displayWindowAccount(const QItemSelection&, const QItemSelection&);

private:
    FacAccount& _facAccount;
    AccountWindow& _accountWindow;
    CreateAccountTab& _createAccountTab;
    IPasswordSecurity& _passwordSecurity;
    IDatabase& _db;
    ILog& _log;

    QWidget _accountWindowWidget;
    QVBoxLayout _accountWindowLayout;

    QLineEdit _filterLineEdit;
    QListView _accountView;
    QHBoxLayout _viewAndDisplayAccountLayout;
    QStandardItemModel _accountModel;
    QStringList _accountsData;
    QStringList _accountsDataFilter;
    QVBoxLayout _mainLayout;
};
