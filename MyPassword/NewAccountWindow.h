#pragma once

#include "Interface/IListener.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>

#include <memory>

class IEncryption;
class IPasswordSecurity;
class SecurityLevelWindow;
class IDatabase;
class ILog;

class NewAccountWindow final : public QWidget
{
    Q_OBJECT
public:
    NewAccountWindow(IEncryption&,IPasswordSecurity&,SecurityLevelWindow&,IDatabase&,ILog&);
    NewAccountWindow(NewAccountWindow const&)=delete;
    NewAccountWindow& operator=(NewAccountWindow const&)=delete;
    void cleanWindow();

    void addListener(IListener* iListener){
        _listeners.push_back(iListener);
    }

    void fireEventClose(){
        for(const auto& listener : _listeners){
            listener->onEventClose();
        }
    }

public slots:
    void showSecurityLvlWindow();
    void checkPasswordSecurity(const QString&);
    void viewPassword();
    void validateForm();

private:
    IEncryption& _encryption;
    IPasswordSecurity& _passwordSecurity;
    SecurityLevelWindow& _securityLevelWindow;
    IDatabase& _db;
    ILog& _log;

    std::vector<IListener*> _listeners;
    QVBoxLayout _layoutMainV;
    QHBoxLayout _layoutButton;

    QLabel _nameLabel;
    QLineEdit _nameLineEdit;
    QHBoxLayout _nameLayout;

    QLabel _loginLabel;
    QLineEdit _loginLineEdit;
    QHBoxLayout _loginLayout;

    QLabel _passwordLabel;
    QLineEdit _passwordLineEdit;
    QPushButton _passwordViewButt;
    QPushButton _passwordSecurityButt;
    QHBoxLayout _passwordLayout;
    bool isPassordView{false};
    int _pwdSecurityLvl{0};

    QLabel _detailsLabel;
    QLineEdit _detailsLineEdit;
    QHBoxLayout _detailsLayout;

    QPushButton _validateButton;
    QPushButton _cancelButton;
    QLabel _labelTitle;
};
