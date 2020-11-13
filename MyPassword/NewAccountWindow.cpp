#include "NewAccountWindow.h"
#include "Interface/IDatabase.h"
#include "Interface/IEncryption.h"
#include "Interface/ILog.h"
#include "Utility.h"
#include "PasswordSecurity.h"

#include <QFrame>
#include <QDebug>
#include <QMessageBox>

NewAccountWindow::NewAccountWindow(IEncryption& iEncryption,
                                   PasswordSecurity& iPasswordSecurity,
                                   IDatabase& iDb,
                                   ILog& iLog):
    _encryption(iEncryption),
    _passwordSecurity(iPasswordSecurity),
    _db(iDb),
    _log(iLog)
{
    setFixedWidth(SIZE_WINDOW_HORIZONTAL);
    move(0,SIZE_WINDOW_HORIZONTAL+50);
    setWindowTitle(" ");
    setStyleSheet(Utility::GET_STYLE_WIDGET()+
                  Utility::GET_STYLE_QLINEEDIT()+
                  Utility::GET_STYLE_QPUSHBUTTON()+
                  Utility::GET_STYLE_QLABEL());

    _labelTitle.setText("NEW ACCOUNT");
    _labelTitle.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    _labelTitle.setStyleSheet(Utility::SET_TEXT_SIZE(35,BOLD)+
                              Utility::SET_TEXT_COLOR(COLOR_LIGHT));

    _validateButton.setText("Submit");
    _validateButton.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                                  Utility::SET_HEIGHT(50));
    _cancelButton.setText("Cancel");
    _cancelButton.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                                Utility::SET_HEIGHT(50));

    _nameLabel.setText("Name:");
    _nameLayout.addWidget(&_nameLabel);
    _nameLayout.addWidget(&_nameLineEdit);

    _loginLabel.setText("Login:");
    _loginLayout.addWidget(&_loginLabel);
    _loginLayout.addWidget(&_loginLineEdit);

    _passwordLabel.setText("Password:");
    _passwordLineEdit.setEchoMode(QLineEdit::Password);
    _passwordViewButt.setIcon(QIcon(":/hide"));
    _passwordViewButt.setIconSize(ICON_SIZE);
    _passwordSecurityButt.setIconSize(ICON_SIZE);
    _passwordSecurityButt.hide();
    _passwordLayout.addWidget(&_passwordLabel);
    _passwordLayout.addWidget(&_passwordLineEdit);
    _passwordLayout.addWidget(&_passwordViewButt);
    _passwordLayout.addWidget(&_passwordSecurityButt);

    _detailsLabel.setText("Details:");
    _detailsLayout.addWidget(&_detailsLabel);
    _detailsLayout.addWidget(&_detailsLineEdit);

    _layoutButton.addWidget(&_validateButton);
    _layoutButton.addWidget(&_cancelButton);

    _layoutMainV.addSpacing(20);
    _layoutMainV.addWidget(&_labelTitle);
    _layoutMainV.addSpacing(20);
    _layoutMainV.addLayout(&_nameLayout);
    _layoutMainV.addSpacing(10);
    _layoutMainV.addLayout(&_loginLayout);
    _layoutMainV.addSpacing(10);
    _layoutMainV.addLayout(&_passwordLayout);
    _layoutMainV.addSpacing(10);
    _layoutMainV.addLayout(&_detailsLayout);
    _layoutMainV.addSpacing(20);
    _layoutMainV.addLayout(&_layoutButton);
    setLayout(&_layoutMainV);

    QObject::connect(&_passwordViewButt,&QPushButton::clicked,this,&NewAccountWindow::viewPassword);
    QObject::connect(&_passwordLineEdit,&QLineEdit::textChanged,this,&NewAccountWindow::checkPasswordSecurity);
    QObject::connect(&_cancelButton,&QPushButton::clicked,this,&NewAccountWindow::close);
    QObject::connect(&_validateButton,&QPushButton::clicked,this,&NewAccountWindow::validateForm);
}

void NewAccountWindow::cleanWindow(){
    _nameLineEdit.clear();
    _nameLineEdit.setStyleSheet(Utility::SET_BORDER_SIZE(0)+
                                Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,BOLD));
    _loginLineEdit.clear();
    _passwordLineEdit.clear();
    _detailsLineEdit.clear();
}

void NewAccountWindow::checkPasswordSecurity(const QString& iPwd){
    if(iPwd.isEmpty()){
        _passwordSecurityButt.hide();
        return;
    }

    _pwdSecurityLvl = _passwordSecurity.getSecurityLevel(iPwd);

    switch(_pwdSecurityLvl){
    case PasswordSecurity::VERY_LOW:
        _passwordSecurityButt.setIcon(QIcon(":/low"));
        _passwordSecurityButt.setToolTip(tr("Your password is not safe at all!"));
        break;
    case PasswordSecurity::LOW:
        _passwordSecurityButt.setIcon(QIcon(":/medium"));
        _passwordSecurityButt.setToolTip(tr("Your password can be cracked easily!"));
        break;
    case PasswordSecurity::MEDIUM:
        _passwordSecurityButt.setIcon(QIcon(":/medium"));
        _passwordSecurityButt.setToolTip(tr("Your password is at the minimum safety!"));
        break;
    case PasswordSecurity::HIGH:
        _passwordSecurityButt.setIcon(QIcon(":/high"));
        _passwordSecurityButt.setToolTip(tr("Your password is safe!"));
        break;
    case PasswordSecurity::VERY_HIGH:
        _passwordSecurityButt.setIcon(QIcon(":/very_high"));
        _passwordSecurityButt.setToolTip(tr("More than 50 years is necessary to cracked your password!"));
        break;
    default:
        _passwordSecurityButt.hide();
        return;
    }
    _passwordSecurityButt.show();
}

void NewAccountWindow::viewPassword(){
    if(isPassordView){
        isPassordView = false;
        _passwordLineEdit.setEchoMode(QLineEdit::Password);
        _passwordViewButt.setIcon(QIcon(":/hide"));

    }else{
        isPassordView = true;
        _passwordLineEdit.setEchoMode(QLineEdit::Normal);
        _passwordViewButt.setIcon(QIcon(":/view"));
    }
}

void NewAccountWindow::validateForm() {
    if (_nameLineEdit.text().isEmpty()){
        _nameLineEdit.setStyleSheet(Utility::SET_BORDER_SIZE(0)+
                                    Utility::SET_BACKGROUND_COLOR(COLOR_RED));
        return;
    }

    int error{_db.create(QStringList()
                         <<_nameLineEdit.text()
                         <<_loginLineEdit.text()
                         <<_encryption.encrypt(_passwordLineEdit.text())
                         <<_detailsLineEdit.text()
                         << QString::number(_pwdSecurityLvl))};

    if(error != Utility::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(Utility::getMsgError(error).c_str()));
        return;
    }

    _log.LOG_INFO("Account created : "+_nameLineEdit.text().toStdString());

    fireEventClose();
    close();
}

