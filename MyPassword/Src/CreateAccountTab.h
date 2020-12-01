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

    QLabel* _titleLabel{new QLabel{tr("New account")}};

    QLabel* _nameLabel{new QLabel{tr("Name:*   ")}};
    QLabel* _nameErrorLabel{new QLabel{tr("The name is mandatory.")}};
    QLabel* _nameLengthLabel{new QLabel{QStringLiteral("0/50")}};
    QLineEdit* _nameLineEdit{new QLineEdit};
    QHBoxLayout* _nameLayout{new QHBoxLayout};

    QLabel* _loginLabel{new QLabel{tr("Login:     ")}};
    QLabel* _loginLengthLabel{new QLabel{QStringLiteral("0/50")}};
    QLineEdit* _loginLineEdit{new QLineEdit};
    QHBoxLayout* _loginLayout{new QHBoxLayout};

    QLabel* _passwordLabel{new QLabel{tr("Password:")}};
    QLabel* _passwordLengthLabel{new QLabel{QStringLiteral("0/50")}};
    QLineEdit* _passwordLineEdit{new QLineEdit};
    QPushButton* _passwordViewButt{new QPushButton};
    QPushButton* _passwordSecurityButt{new QPushButton};
    QHBoxLayout* _passwordLayout{new QHBoxLayout};
    bool isPassordView{false};
    int _pwdSecurityLvl{0};

    QLabel* _detailsLabel{new QLabel{tr("Details:    ")}};
    QVBoxLayout* _detailsLabelLayout{new QVBoxLayout};
    QLabel* _detailsLengthLabel{new QLabel{QStringLiteral("0/200")}};
    QVBoxLayout* _detailsLengthLabelLayout{new QVBoxLayout};
    QTextEdit* _detailsTextEdit{new QTextEdit};
    QHBoxLayout* _detailsLayout{new QHBoxLayout};

    QPushButton* _validateButt{new QPushButton{tr("Create account")}};
    QLabel* _validationLabel{new QLabel{tr("New account created!")}};
    QPushButton* _validationIcon{new QPushButton};
    QHBoxLayout* _validationLayout{new QHBoxLayout};

    QVBoxLayout* _mainLayout{new QVBoxLayout};
};
