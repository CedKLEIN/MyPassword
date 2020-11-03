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
class Error;
class ILog;

class WindowDisplayAccount : public QWidget
{
    Q_OBJECT

public:
    WindowDisplayAccount(const QString&,
                         FacAccount&,
                         IEncryption&,
                         IDatabase&,
                         Error&,
                         ILog&);
    void addListener(IListener* iListener){
        _listeners.push_back(iListener);
    }

    void fireEventClose(){
        for(const auto& listener : _listeners){
            listener->onEventClose();
        }
    }

    QString getAccount() const;

    bool isModifing{false};

public slots:
    bool saveModification();
    bool saveModifPassword();
    int isPasswordValid();
    void deleteAccounts();
    void checkPassword();
    void enableModification();
    void closeEvent(QCloseEvent*) final;

private:
    void disableWidgets();
    void enableWidgets();

    QString _accountName;
    FacAccount& _facAccount;
    IEncryption& _encryption;
    IDatabase& _db;
    Error& _error;
    ILog& _log;

    std::vector<IListener*> _listeners;

    QLabel _name;
    QLineEdit _login;
    QLineEdit _details;

    QPushButton _deleteButt;
    QPushButton _modifyButt;
    QPushButton _saveButt;

    QFormLayout _formLayout;
    QHBoxLayout _buttLayout;
    QVBoxLayout _mainLayout;

    QLabel _testLabel;
    QLineEdit _testLineEdit;
    QPushButton _testButt;

    QLabel _passwordLabel;
    QLineEdit _password;
    QLineEdit _passwordConfirm;
    QPushButton _passwordButt;

};
