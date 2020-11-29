#pragma once

#include "Interface/IUpdateAccountListener.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QString>

class IEncryption;
class IPasswordSecurity;
class SecurityLevelWindow;
class IDatabase;
class ILog;

class CreateAccountTab final : public QWidget
{
    Q_OBJECT
public:
    CreateAccountTab(IEncryption&, IPasswordSecurity&, IDatabase&, ILog&);
    CreateAccountTab(CreateAccountTab const&)=delete;
    CreateAccountTab& operator=(CreateAccountTab const&)=delete;
    void onTabSelected();

    void addListener(IUpdateAccountListener* iListener){
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
            listener->onEventUpdateAccount();
        }
    }

    IEncryption& _encryption;
    IPasswordSecurity& _passwordSecurity;
    IDatabase& _db;
    ILog& _log;

    std::vector<IUpdateAccountListener*> _listeners;

    QLabel _titleLabel{tr("New account")};

    QLabel _nameLabel{tr("Name:*   ")};
    QLabel _nameErrorLabel{tr("The name is mandatory.")};
    QLabel _nameLengthLabel{QStringLiteral("0/50")};
    QLineEdit _nameLineEdit;
    QHBoxLayout _nameLayout;

    QLabel _loginLabel{tr("Login:     ")};
    QLabel _loginLengthLabel{QStringLiteral("0/50")};
    QLineEdit _loginLineEdit;
    QHBoxLayout _loginLayout;

    QLabel _passwordLabel{tr("Password:")};
    QLabel _passwordLengthLabel{QStringLiteral("0/50")};
    QLineEdit _passwordLineEdit;
    QPushButton _passwordViewButt;
    QPushButton _passwordSecurityButt;
    QHBoxLayout _passwordLayout;
    bool isPassordView{false};
    int _pwdSecurityLvl{0};

    QLabel _detailsLabel{tr("Details:    ")};
    QVBoxLayout _detailsLabelLayout;
    QLabel _detailsLengthLabel{QStringLiteral("0/200")};
    QVBoxLayout _detailsLengthLabelLayout;
    QTextEdit _detailsTextEdit;
    QHBoxLayout _detailsLayout;

    QPushButton _validateButt{tr("Create account")};
    QLabel _validationLabel{tr("New account created!")};
    QPushButton _validationIcon;
    QHBoxLayout _validationLayout;

    QVBoxLayout _mainLayout;
};
