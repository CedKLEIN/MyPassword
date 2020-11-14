#pragma once

#include "Account.h"
#include "Interface/IListener.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>

#include <memory>

class IEncryption;
class IPasswordSecurity;
class SecurityLevelWindow;
class IDatabase;
class ILog;
class FacDisplayAccountWindow;

class AccountWindow : public QWidget
{
    Q_OBJECT

    friend FacDisplayAccountWindow;

public:
    void addListener(IListener* iListener){
        _listeners.push_back(iListener);
    }

    void fireEventClose(){
        for(const auto& listener : _listeners){
            listener->onEventClose();
        }
    }

    QString getAccountName() const;

public slots:
    void showSecurityLvlWindow();
    void checkPasswordSecurity(const QString&);
    void itemChangedLogin(const QString&);
    void itemChangedDetails(const QString&);
    bool saveModifLogin();
    bool saveModifDetails();
    bool saveModifPassword();
    void deleteAccounts();
    void checkPassword();
    void enableCheckPassword();
    void enableChangePassword();
    void viewPassword();
    void viewTestPwd();
    void showEvent(QShowEvent*) override final;

private:
    AccountWindow(const QString&,
                  FacAccount&,
                  IEncryption&,
                  IPasswordSecurity&,
                  SecurityLevelWindow&,
                  IDatabase&,
                  ILog&);

    QString _accountName;
    FacAccount& _facAccount;
    IEncryption& _encryption;
    IPasswordSecurity& _passwordSecurity;
    SecurityLevelWindow& _securityLevelWindow;
    IDatabase& _db;
    ILog& _log;

    std::vector<IListener*> _listeners;

    QLabel _name;

    QLabel _loginLabel;
    QLineEdit _loginLineEdit;
    QPushButton _saveLoginButt;
    QHBoxLayout _LoginLayout;

    QLabel _detailsLabel;
    QLineEdit _detailsLineEdit;
    QPushButton _saveDetailsButt;
    QHBoxLayout _detailsLayout;

    QPushButton _deleteButt;
    QPushButton _modifyButt;

    QPushButton _testActivateButt;
    QLineEdit _testLineEdit;
    QPushButton _testButt;
    QPushButton _testViewButt;
    QHBoxLayout _testLayout;
    bool isTestVisible{false};
    bool isTestView{false};

    QPushButton _pwdActivateButt;
    QLineEdit _pwdLineEdit;
    QPushButton _pwdButt;
    QPushButton _pwdViewButt;
    QPushButton _pwdSecurityButt;
    QHBoxLayout _pwdLayout;
    bool isPasswordChangeVisible{false};
    bool isPassordView{false};
    int _pwdSecurityLvl{0};

    QVBoxLayout _mainLayout;
};

class FacDisplayAccountWindow{
public:
    ~FacDisplayAccountWindow(){
        clear();
    }
    void create(const QString& iName,
                FacAccount& iFacAccount,
                IEncryption& iEncryption,
                IPasswordSecurity& iPasswordSecurity,
                SecurityLevelWindow& iSecurityLevelWindow,
                IDatabase& iDatabase,
                ILog& iLog){
        _windowsDisplay.emplace_back(new AccountWindow(iName,
                                                       iFacAccount,
                                                       iEncryption,
                                                       iPasswordSecurity,
                                                       iSecurityLevelWindow,
                                                       iDatabase,iLog));
    }

    AccountWindow* getAccount(const QString& iName)const{
        for(const auto& window: _windowsDisplay){
            if(window->getAccountName() == iName){
                return window;
            }
        }
        return nullptr;
    }

    std::vector<AccountWindow*> getWindowsDisplay()const{
        return _windowsDisplay;
    }

    void clear(){
        for(const auto& window : _windowsDisplay){
            delete window;
        }
    }

private:
    std::vector<AccountWindow*> _windowsDisplay;
};
