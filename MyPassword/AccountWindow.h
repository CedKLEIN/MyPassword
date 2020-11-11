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
class IDatabase;
class ILog;
class FacWindowDisplayAccount;

class AccountWindow : public QWidget
{
    Q_OBJECT

friend FacWindowDisplayAccount;

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
                         IDatabase&,
                         ILog&);

    QString _accountName;
    FacAccount& _facAccount;
    IEncryption& _encryption;
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
    QHBoxLayout _pwdLayout;
    bool isPasswordChangeVisible{false};
    bool isPassordView{false};

    QVBoxLayout _mainLayout;
};

class FacWindowDisplayAccount{
public:
    ~FacWindowDisplayAccount(){
        clear();
    }
    void create(const QString& iName,
                FacAccount& iFacAccount,
                IEncryption& iEncryption,
                IDatabase& iDatabase,
                ILog& iLog){
        _windowsDisplay.emplace_back(new AccountWindow(iName,iFacAccount,iEncryption,iDatabase,iLog));
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
