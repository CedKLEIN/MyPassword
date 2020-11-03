#include "windowdisplayaccount.h"

#include "Interface/IEncryption.h"
#include "Interface/IDatabase.h"
#include "Error.h"
#include "Interface/ILog.h"

#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>

WindowDisplayAccount::WindowDisplayAccount(const QString& iAccountName,
                                           FacAccount &iFacAccount,
                                           IEncryption& iEncryption,
                                           IDatabase& iDb,
                                           Error& iError,
                                           ILog& iLog) :
    _accountName(iAccountName),
    _facAccount(iFacAccount),
    _encryption(iEncryption),
    _db(iDb),
    _error(iError),
    _log(iLog)
{
    setFixedWidth(500);
    setWindowTitle(" ");

    _name.setText(_facAccount.get(_accountName)->getName());
    _login.setText(_facAccount.get(_accountName)->getLogin());
    _details.setText(_facAccount.get(_accountName)->getDetails());

    _name.setAlignment(Qt::AlignCenter);
    _name.setStyleSheet("font: bold 30px;");

    _deleteButt.setText("Delete");
    _modifyButt.setText("Modify");
    _saveButt.setText("Save");
    _testLabel.setText("Test your password :");
    _testButt.setText("Check");

    _passwordLabel.setText("Change your password :");
    _password.setEchoMode(QLineEdit::Password);
    _password.setPlaceholderText("Password");
    _passwordConfirm.setEchoMode(QLineEdit::Password);
    _passwordConfirm.setPlaceholderText("Confirm password");
    _passwordButt.setText("Change password");

    _mainLayout.addWidget(&_name);
    _formLayout.addRow("&Login:", &_login);
    _formLayout.addRow("&Details:", &_details);

    _buttLayout.addWidget(&_modifyButt);
    _buttLayout.addWidget(&_saveButt);

    _mainLayout.addLayout(&_formLayout);
    _mainLayout.addWidget(&_deleteButt);
    _mainLayout.addLayout(&_buttLayout);

    _password.setEchoMode(QLineEdit::Password);
    _testLineEdit.setEchoMode(QLineEdit::Password);

    _mainLayout.addWidget(&_testLabel);
    _mainLayout.addWidget(&_testLineEdit);
    _mainLayout.addWidget(&_testButt);

    _mainLayout.addWidget(&_passwordLabel);
    _mainLayout.addWidget(&_password);
    _mainLayout.addWidget(&_passwordConfirm);
    _mainLayout.addWidget(&_passwordButt);

    disableWidgets();
    setLayout(&_mainLayout);

    QObject::connect(&_modifyButt, SIGNAL(clicked()), this, SLOT(enableModification()));
    QObject::connect(&_deleteButt, SIGNAL(clicked()), this, SLOT(deleteAccounts()));
    QObject::connect(&_testButt, SIGNAL(clicked()), this, SLOT(checkPassword()));
    QObject::connect(&_saveButt, SIGNAL(clicked()), this, SLOT(saveModification()));
    QObject::connect(&_passwordButt, SIGNAL(clicked()), this, SLOT(saveModifPassword()));
}

bool WindowDisplayAccount::saveModification()
{
    int error{_db.modify(QStringList()
                   <<_name.text()
                   <<_login.text()
                   <<_facAccount.get(_accountName)->getPassword()
                   <<_details.text())};

    if(error != Error::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(_error.getMsgError(error).c_str()));
        return false;
    }

    _log.LOG_INFO("Data changed modify from : "
        +_facAccount.get(_accountName)->getName().toStdString()+"/"
        +_facAccount.get(_accountName)->getLogin().toStdString()+"/"
        +_facAccount.get(_accountName)->getDetails().toStdString()+" to : "
        +_name.text().toStdString()+"/"
        +_login.text().toStdString()+"/"
        +_details.text().toStdString());

    disableWidgets();
    fireEventClose();
    this->close();

    return true;
}

bool WindowDisplayAccount::saveModifPassword(){
    int errorPasswordValid{isPasswordValid()};
    if(errorPasswordValid != Error::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(_error.getMsgError(errorPasswordValid).c_str()));
        return false;
    }

    int error{_db.modify(QStringList()
               <<_facAccount.get(_accountName)->getName()
               <<_facAccount.get(_accountName)->getLogin()
               <<_encryption.encrypt(_password.text())
               <<_facAccount.get(_accountName)->getDetails())};

    if(error != Error::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(_error.getMsgError(error).c_str()));
        return false;
    }

    _log.LOG_INFO("Password modify");

    fireEventClose();
    this->close();
    return true;
}

int WindowDisplayAccount::isPasswordValid(){
    if (_password.text().isEmpty() ||
            _passwordConfirm.text().isEmpty()){
        return Error::ERROR::password_empty;
    }

    if(_password.text() != _passwordConfirm.text()){
        return Error::ERROR::password_confimation_not_the_same;
    }

    return Error::ERROR::no_error;
}

void WindowDisplayAccount::deleteAccounts()
{
    int error{_db.remove(_name.text())};

    if(error != Error::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(_error.getMsgError(error).c_str()));
        return;
    }

    _log.LOG_INFO("Account deleted : "+_name.text().toStdString());

    disableWidgets();
    fireEventClose();
    this->close();
}

void WindowDisplayAccount::checkPassword(){
    QString newPassEncrypt = _encryption.encrypt(_testLineEdit.text());
    QString currentPassEncrypt = _facAccount.get(_accountName)->getPassword();

    if(currentPassEncrypt == newPassEncrypt){
        _testLineEdit.setStyleSheet("QLineEdit { background: rgb(76,175,80); color: rgb(255,255,255);}");
         _log.LOG_INFO("Try password : success");
    }else {
        _testLineEdit.setStyleSheet("QLineEdit { background: rgb(244,67,54); color: rgb(255,255,255);}");
        _log.LOG_INFO("Try password : failed");
    }
}

void WindowDisplayAccount::disableWidgets(){
    isModifing = false;

    _name.setEnabled(false);
    _login.setEnabled(false);
    _details.setEnabled(false);
    _deleteButt.setEnabled(false);
    _saveButt.setEnabled(false);
    _modifyButt.setText("Modify");
}

void WindowDisplayAccount::enableWidgets(){
    isModifing = true;

    _name.setEnabled(true);
    _login.setEnabled(true);
    _details.setEnabled(true);
    _deleteButt.setEnabled(true);
    _saveButt.setEnabled(true);
    _modifyButt.setText("Cancel");
}

QString WindowDisplayAccount::getAccount() const{
    return _accountName;
}

void WindowDisplayAccount::enableModification(){
    if (!isModifing){
        enableWidgets();
    } else {
        disableWidgets();
    }
}

void WindowDisplayAccount::closeEvent(QCloseEvent* event){
    _testLineEdit.clear();
    _testLineEdit.setStyleSheet("");
    _password.clear();
    _passwordConfirm.clear();

    if (isModifing){
        event->ignore();
        QMessageBox::warning(this, tr("Modification on-going"),
                                       tr("Please cancel modification before quit"));
    }
}
