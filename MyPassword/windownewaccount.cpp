#include "windownewaccount.h"
#include "Interface/IDatabase.h"
#include "Interface/IEncryption.h"
#include "Interface/ILog.h"
#include "Error.h"

#include <QFrame>
#include <QDebug>
#include <QMessageBox>

WindowNewAccount::WindowNewAccount(IEncryption& encryption,
                                   IDatabase& iDb,
                                   Error& iError,
                                   ILog& iLog):
    _encryption(encryption),
    _db(iDb),
    _error(iError),
    _log(iLog)
{
    setFixedWidth(500);

    _labelTitle.setFrameStyle(QFrame::Panel | QFrame::Sunken);
    _labelTitle.setText("Nouveau compte !");
    _labelTitle.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    _validateButton.setText("Valider");
    _cancelButton.setText("Annuler");

    //Fill the form
    _layoutForm.addRow("&Name:", &_name);
    _layoutForm.addRow("&Login:", &_login);
    _layoutForm.addRow("&Password:", &_password);
    _layoutForm.addRow("&Details:", &_details);

    //Button
    _layoutButton.addWidget(&_validateButton);
    _layoutButton.addWidget(&_cancelButton);

    _layoutMainV.addWidget(&_labelTitle);
    _layoutMainV.addLayout(&_layoutForm);
    _layoutMainV.addLayout(&_layoutButton);
    setLayout(&_layoutMainV);

    QObject::connect(&_cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(&_validateButton, SIGNAL(clicked()), this, SLOT(validateForm()));
}

void WindowNewAccount::cleanWindow(){
    _name.clear();
    _login.clear();
    _password.clear();
    _details.clear();
}

void WindowNewAccount::validateForm() {
    int error{_db.create(QStringList()
                   <<_name.text()
                   <<_login.text()
                   <<_encryption.encrypt(_password.text())
                   <<_details.text())};

    if(error != Error::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(_error.getMsgError(error).c_str()));
        return;
    }

    _log.LOG_INFO("Account created : "+_name.text().toStdString());

    fireEventClose();
    close();
}

