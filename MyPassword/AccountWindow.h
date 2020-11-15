#pragma once

#include "Account.h"
#include "Interface/IListener.h"

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <memory>

class IEncryption;
class IPasswordSecurity;
class SecurityLevelWindow;
class IDatabase;
class ILog;

class AccountWindow : public QWidget
{
    Q_OBJECT

public:
    AccountWindow(FacAccount&,
                  IEncryption&,
                  IPasswordSecurity&,
                  SecurityLevelWindow&,
                  IDatabase&,
                  ILog&);
    AccountWindow(AccountWindow const&)=delete;
    AccountWindow& operator=(AccountWindow const&)=delete;

    void addListener(IListener* iListener){
        _listeners.push_back(iListener);
    }

    QString getAccountName() const;
    void showWindow(const QString&);

private slots:
    void checkPasswordSecurity(const QString&);
    void itemChangedLogin(const QString&);
    void itemChangedDetails(const QString&);
    bool saveModifLogin();
    bool saveModifDetails();
    bool saveModifPassword();
    void checkPassword();
    void viewPassword();
    void viewTestPwd();

private:
    void fireRefreshAccounts(){
        for(const auto& listener : _listeners){
            listener->onEventClose();
        }
    }

    FacAccount& _facAccount;
    IEncryption& _encryption;
    IPasswordSecurity& _passwordSecurity;
    SecurityLevelWindow& _securityLevelWindow;
    IDatabase& _db;
    ILog& _log;

    std::vector<IListener*> _listeners;

    QLabel _nameLabel{""};

    QLabel _loginLabel{"Login : "};
    QLineEdit _loginLineEdit{""};
    QPushButton _loginButt;
    QHBoxLayout _loginLayout;

    QLabel _detailsLabel{"Details : "};
    QLineEdit _detailsLineEdit;
    QPushButton _detailsButt;
    QHBoxLayout _detailsLayout;

    QLabel _testLabel{" Test your password :"};
    QLineEdit _testLineEdit;
    QPushButton _testButt{"Check"};
    QPushButton _testViewButt;
    QHBoxLayout _testLayout;
    bool isTestView{false};

    QLabel _pwdLabel{" Change your password :"};
    QLineEdit _pwdLineEdit;
    QPushButton _pwdButt{"Change password"};
    QPushButton _pwdViewButt;
    QPushButton _pwdSecurityButt;
    QHBoxLayout _pwdLayout;
    bool isPassordView{false};
    int _pwdSecurityLvl{0};

    QVBoxLayout _mainLayout;
};
