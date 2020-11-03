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
class IDatabase;
class Error;
class ILog;

class WindowNewAccount final : public QWidget
{
    Q_OBJECT
public:
    WindowNewAccount(IEncryption&, IDatabase&, Error&, ILog&);
    WindowNewAccount(WindowNewAccount const&)=delete;
    WindowNewAccount& operator=(WindowNewAccount const&)=delete;
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
    void validateForm();

private:
    IEncryption& _encryption;
    IDatabase& _db;
    Error& _error;
    ILog& _log;

    std::vector<IListener*> _listeners;
    QFormLayout _layoutForm;
    QVBoxLayout _layoutMainV;
    QHBoxLayout _layoutButton;

    QLineEdit _name;
    QLineEdit _login;
    QLineEdit _password;
    QLineEdit _details;
    QPushButton _validateButton;
    QPushButton _cancelButton;
    QLabel _labelTitle;
};
