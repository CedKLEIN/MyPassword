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
class ILog;

class NewAccountWindow final : public QWidget
{
    Q_OBJECT
public:
    NewAccountWindow(IEncryption&, IDatabase&,ILog&);
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
    void viewPassword();
    void validateForm();

private:
    IEncryption& _encryption;
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
    QHBoxLayout _passwordLayout;
    bool isPassordView{false};

    QLabel _detailsLabel;
    QLineEdit _detailsLineEdit;
    QHBoxLayout _detailsLayout;

    QPushButton _validateButton;
    QPushButton _cancelButton;
    QLabel _labelTitle;
};
