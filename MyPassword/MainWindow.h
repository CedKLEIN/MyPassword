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
               AccountWindow&,
               NewAccountWindow&,
               IEncryption&,
               IPasswordSecurity&,
               SecurityLevelWindow&,
               IDatabase&,
               ILog&,
               IGenerateFile&);
    MainWindow(MainWindow const&)=delete;
    MainWindow& operator=(MainWindow const&)=delete;
    ~MainWindow();
    void onEventClose() override;

private slots:
    void filterChanged(const QString&);
    void retrieveAccounts();
    void setModelFromDataList(const QStringList&);
    void displayWindowAccount(const QItemSelection&, const QItemSelection&);
    void generateFile();
    void deleteAccount();

private:
    void closeEvent(QCloseEvent *) override;

    FacAccount& _facAccount;
    AccountWindow& _accountWindow;
    NewAccountWindow& _windowNewAccount;
    IEncryption& _encryption;
    IPasswordSecurity& _passwordSecurity;
    SecurityLevelWindow& _securityLevelWindow;
    IDatabase& _db;
    ILog& _log;
    IGenerateFile& _generateFile;

    QLineEdit _filterLineEdit;
    QListView _accountView;
    QHBoxLayout _viewAndDisplayAccountLayout;
    QStandardItemModel _accountModel;
    QStringList _accountsData;
    QStringList _accountsDataFilter;
    QPushButton _newAccountButt{" New account"};
    QPushButton _generateFileButt{" Generate a text file"};
    QPushButton _deleteAccountButt{" Delete account"};
    QHBoxLayout _buttLayout;
    QVBoxLayout _mainLayout;
};
