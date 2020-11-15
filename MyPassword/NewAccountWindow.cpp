#include "NewAccountWindow.h"
#include "Interface/IDatabase.h"
#include "Interface/IEncryption.h"
#include "Interface/IPasswordSecurity.h"
#include "Interface/ILog.h"
#include "Utility.h"
#include "SecurityLevelWindow.h"

#include <QDebug>
#include <QMessageBox>

NewAccountWindow::NewAccountWindow(IEncryption& iEncryption,
                                   IPasswordSecurity& iPasswordSecurity,
                                   SecurityLevelWindow& iSecurityLevelWindow,
                                   IDatabase& iDb,
                                   ILog& iLog):
    _encryption(iEncryption),
    _passwordSecurity(iPasswordSecurity),
    _securityLevelWindow(iSecurityLevelWindow),
    _db(iDb),
    _log(iLog)
{
    setFixedWidth(SIZE_WINDOW_HORIZONTAL/2);
    setStyleSheet(Utility::GET_STYLE_WIDGET()+
                  Utility::GET_STYLE_QLINEEDIT()+
                  Utility::GET_STYLE_QPUSHBUTTON()+
                  Utility::GET_STYLE_QLABEL());

    _titleLabel.setText("NEW ACCOUNT");
    _titleLabel.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    _titleLabel.setStyleSheet(Utility::SET_TEXT_SIZE(35,BOLD)+
                              Utility::SET_TEXT_COLOR(COLOR_LIGHT));

    _validateButt.setText("Submit");
    _validateButt.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                                  Utility::SET_HEIGHT(50));
    _cancelButt.setText("Cancel");
    _cancelButt.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
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

    _layoutButton.addWidget(&_validateButt);
    _layoutButton.addWidget(&_cancelButt);

    _mainLayout.addSpacing(20);
    _mainLayout.addWidget(&_titleLabel);
    _mainLayout.addSpacing(20);
    _mainLayout.addLayout(&_nameLayout);
    _mainLayout.addSpacing(10);
    _mainLayout.addLayout(&_loginLayout);
    _mainLayout.addSpacing(10);
    _mainLayout.addLayout(&_passwordLayout);
    _mainLayout.addSpacing(10);
    _mainLayout.addLayout(&_detailsLayout);
    _mainLayout.addSpacing(20);
    _mainLayout.addLayout(&_layoutButton);
    setLayout(&_mainLayout);

    QObject::connect(&_passwordSecurityButt,&QPushButton::clicked,&_securityLevelWindow,&SecurityLevelWindow::show);
    QObject::connect(&_passwordViewButt,&QPushButton::clicked,this,&NewAccountWindow::viewPassword);
    QObject::connect(&_passwordLineEdit,&QLineEdit::textChanged,this,&NewAccountWindow::checkPasswordSecurity);
    QObject::connect(&_cancelButt,&QPushButton::clicked,this,&NewAccountWindow::close);
    QObject::connect(&_validateButt,&QPushButton::clicked,this,&NewAccountWindow::validateForm);
}

void NewAccountWindow::clearWindow(){
    _nameLineEdit.clear();
    _loginLineEdit.clear();
    _passwordLineEdit.clear();
    _detailsLineEdit.clear();
    _nameLineEdit.setStyleSheet(Utility::SET_BORDER_SIZE(0)+
                                Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,BOLD));
}

void NewAccountWindow::checkPasswordSecurity(const QString& iPwd){
    if(iPwd.isEmpty()){
        _passwordSecurityButt.hide();
        return;
    }

    _pwdSecurityLvl = _passwordSecurity.getSecurityLevel(iPwd);

    _passwordSecurityButt.setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(_pwdSecurityLvl)));

    switch(_pwdSecurityLvl){
    case IPasswordSecurity::VERY_LOW:
        _passwordSecurityButt.setToolTip(tr("Your password is not safe at all!"));
        break;
    case IPasswordSecurity::LOW:
        _passwordSecurityButt.setToolTip(tr("Your password can be cracked easily!"));
        break;
    case IPasswordSecurity::MEDIUM:
        _passwordSecurityButt.setToolTip(tr("Your password is at the minimum safety!"));
        break;
    case IPasswordSecurity::HIGH:
        _passwordSecurityButt.setToolTip(tr("Your password is safe!"));
        break;
    case IPasswordSecurity::VERY_HIGH:
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

