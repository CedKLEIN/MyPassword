#pragma once

#include "Interface/IListener.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

class IEncryption;
class IPasswordSecurity;
class SecurityLevelWindow;
class IDatabase;
class ILog;

class CreateAccountTab final : public QWidget
{
    Q_OBJECT
public:
    CreateAccountTab(IEncryption&,IPasswordSecurity&,SecurityLevelWindow&,IDatabase&,ILog&);
    CreateAccountTab(CreateAccountTab const&)=delete;
    CreateAccountTab& operator=(CreateAccountTab const&)=delete;
    void onTabSelected();

    void addListener(IListener* iListener){
        _listeners.push_back(iListener);
    }

private slots:
    void textChangedName(const QString&);
    void textChangedLogin(const QString&);
    void textChangedPassword(const QString&);
    void textChangedDetails();
    void checkPasswordSecurity(const QString&);
    void viewPassword();
    void validateForm();

private:
    void clearWindow();
    void fireEventUpdate(){
        for(const auto& listener : _listeners){
            listener->onEventClose();
        }
    }

    IEncryption& _encryption;
    IPasswordSecurity& _passwordSecurity;
    SecurityLevelWindow& _securityLevelWindow;
    IDatabase& _db;
    ILog& _log;

    std::vector<IListener*> _listeners;

    QLabel _titleLabel{"New account"};

    QLabel _nameLabel{"Name:*   "};
    QLabel _nameErrorLabel{"The name is mandatory."};
    QLabel _nameLengthLabel{"0/50"};
    QLineEdit _nameLineEdit;
    QHBoxLayout _nameLayout;

    QLabel _loginLabel{"Login:     "};
    QLabel _loginLengthLabel{"0/50"};
    QLineEdit _loginLineEdit;
    QHBoxLayout _loginLayout;

    QLabel _passwordLabel{"Password:"};
    QLabel _passwordLengthLabel{"0/50"};
    QLineEdit _passwordLineEdit;
    QPushButton _passwordViewButt;
    QPushButton _passwordSecurityButt;
    QHBoxLayout _passwordLayout;
    bool isPassordView{false};
    int _pwdSecurityLvl{0};

    QLabel _detailsLabel{"Details:    "};
    QVBoxLayout _detailsLabelLayout;
    QLabel _detailsLengthLabel{"0/200"};
    QVBoxLayout _detailsLengthLabelLayout;
    QTextEdit _detailsTextEdit;
    QHBoxLayout _detailsLayout;

    QPushButton _validateButt{"Create account"};
    QLabel _validationLabel{"New account created!"};
    QPushButton _validationIcon;
    QHBoxLayout _validationLayout;

    QVBoxLayout _mainLayout;
};
