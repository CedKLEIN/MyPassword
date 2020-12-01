#pragma once

#include "Account.h"

#include "Interface/IUpdateAccountListener.h"

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
class SettingsTab;
class ISettings;

class AccountTab final : public QWidget, public IUpdateAccountListener
{
    Q_OBJECT
public:
    AccountTab(FacAccount&,
               AccountWindow&,
               CreateAccountTab&,
               IPasswordSecurity&,
               IDatabase&,
               ILog&,
               SettingsTab&,
               ISettings&);
    AccountTab(AccountTab const&)=delete;
    AccountTab& operator=(AccountTab const&)=delete;
    ~AccountTab();
    void onEventUpdateAccount() override;

private slots:
    void filterChanged(const QString&);
    void retrieveAccounts();
    void setModelFromDataList(const QStringList*);
    void displayWindowAccount(const QItemSelection&, const QItemSelection&);

private:
    FacAccount& _facAccount;
    AccountWindow& _accountWindow;
    CreateAccountTab& _createAccountTab;
    IPasswordSecurity& _passwordSecurity;
    IDatabase& _db;
    ILog& _log;
    SettingsTab& _settingsTab;
    ISettings& _settings;

    QWidget* _accountWindowWidget{new QWidget};
    QVBoxLayout* _accountWindowLayout{new QVBoxLayout};

    QLineEdit* _filterLineEdit{new QLineEdit};
    QListView* _accountView{new QListView};
    QHBoxLayout* _viewAndDisplayAccountLayout{new QHBoxLayout};
    QStandardItemModel* _accountModel{new QStandardItemModel};
    QStringList* _accountsData{new QStringList};
    QStringList* _accountsDataFilter{new QStringList};
    QVBoxLayout* _mainLayout{new QVBoxLayout};
};
