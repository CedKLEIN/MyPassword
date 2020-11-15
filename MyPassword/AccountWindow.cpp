#include "AccountWindow.h"

#include "SecurityLevelWindow.h"
#include "Interface/IEncryption.h"
#include "Interface/IPasswordSecurity.h"
#include "Interface/IDatabase.h"
#include "Utility.h"
#include "Interface/ILog.h"

#include <QDebug>
#include <QMessageBox>

AccountWindow::AccountWindow(FacAccount &iFacAccount,
                             IEncryption& iEncryption,
                             IPasswordSecurity& iPasswordSecurity,
                             SecurityLevelWindow& iSecurityLevelWindow,
                             IDatabase& iDb,
                             ILog& iLog) :
    _facAccount(iFacAccount),
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

    _nameLabel.setAlignment(Qt::AlignCenter);
    _nameLabel.setStyleSheet(Utility::SET_TEXT_SIZE(40,BOLD)+
                        Utility::SET_TEXT_COLOR(COLOR_LIGHT));

    _loginLineEdit.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_1)+
                                 Utility::SET_TEXT_COLOR(COLOR_BLUE_LIGHT)+
                                 Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,BOLD));
    _loginButt.setIconSize(ICON_SIZE);
    _loginButt.setToolTip("Save change");
    _loginLineEdit.setMaxLength(TEXT_LOGIN_LENGTH);
    _loginLayout.addWidget(&_loginLabel);
    _loginLayout.addWidget(&_loginLineEdit);
    _loginLayout.addWidget(&_loginButt);

    _detailsLineEdit.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_1)+
                                   Utility::SET_TEXT_COLOR(COLOR_BLUE_LIGHT)+
                                   Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,BOLD));
    _detailsButt.setIconSize(ICON_SIZE);
    _detailsButt.setToolTip("Save change");
    _detailsLineEdit.setMaxLength(TEXT_DETAILS_LENGTH);
    _detailsLayout.addWidget(&_detailsLabel);
    _detailsLayout.addWidget(&_detailsLineEdit);
    _detailsLayout.addWidget(&_detailsButt);

    _testLabel.setStyleSheet(Utility::SET_TEXT_COLOR(COLOR_LIGHT));
    _testLineEdit.setEchoMode(QLineEdit::Password);
    _testLineEdit.setPlaceholderText("Test here...");
    _testLineEdit.setMaxLength(TEXT_PASSWORD_LENGTH);
    _testButt.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                            Utility::SET_HEIGHT(35));
    _testViewButt.setIcon(QIcon(":/hide"));
    _testViewButt.setIconSize(ICON_SIZE);
    _testLayout.addWidget(&_testLineEdit);
    _testLayout.addWidget(&_testViewButt);

    _pwdLabel.setStyleSheet(Utility::SET_TEXT_COLOR(COLOR_LIGHT));
    _pwdSecurityButt.setIconSize(ICON_SIZE);
    _pwdSecurityButt.hide();
    _pwdLineEdit.setPlaceholderText("Password");
    _pwdLineEdit.setEchoMode(QLineEdit::Password);
    _pwdLineEdit.setMaxLength(TEXT_PASSWORD_LENGTH);
    _pwdButt.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                           Utility::SET_HEIGHT(35));
    _pwdViewButt.setIcon(QIcon(":/hide"));
    _pwdViewButt.setIconSize(ICON_SIZE);
    _pwdLayout.addWidget(&_pwdLineEdit);
    _pwdLayout.addWidget(&_pwdViewButt);
    _pwdLayout.addWidget(&_pwdSecurityButt);

    _mainLayout.setAlignment(Qt::AlignTop);

    _mainLayout.addSpacing(20);
    _mainLayout.addWidget(&_nameLabel);
    _mainLayout.addSpacing(25);
    _mainLayout.addLayout(&_loginLayout);
    _mainLayout.addLayout(&_detailsLayout);
    _mainLayout.addSpacing(25);

    _mainLayout.addWidget(&_testLabel);
    _mainLayout.addLayout(&_testLayout);
    _mainLayout.addWidget(&_testButt);

    _mainLayout.addSpacing(20);
    _mainLayout.addWidget(&_pwdLabel);
    _mainLayout.addLayout(&_pwdLayout);
    _mainLayout.addWidget(&_pwdButt);
    _mainLayout.addSpacing(10);

    setLayout(&_mainLayout);

    QObject::connect(&_pwdSecurityButt,&QPushButton::clicked,&_securityLevelWindow,&SecurityLevelWindow::show);
    QObject::connect(&_pwdLineEdit,&QLineEdit::textChanged,this,&AccountWindow::checkPasswordSecurity);
    QObject::connect(&_pwdViewButt,&QPushButton::clicked,this,&AccountWindow::viewPassword);
    QObject::connect(&_testViewButt,&QPushButton::clicked,this,&AccountWindow::viewTestPwd);
    QObject::connect(&_loginLineEdit,&QLineEdit::textChanged,this,&AccountWindow::itemChangedLogin);
    QObject::connect(&_detailsLineEdit,&QLineEdit::textChanged,this,&AccountWindow::itemChangedDetails);
    QObject::connect(&_testButt,&QPushButton::clicked,this,&AccountWindow::checkPassword);
    QObject::connect(&_loginButt,&QPushButton::clicked,this,&AccountWindow::saveModifLogin);
    QObject::connect(&_detailsButt,&QPushButton::clicked,this,&AccountWindow::saveModifDetails);
    QObject::connect(&_pwdButt,&QPushButton::clicked,this,&AccountWindow::saveModifPassword);
}

void AccountWindow::checkPasswordSecurity(const QString& iPwd){
    if(iPwd.isEmpty()){
        _pwdSecurityButt.hide();
        return;
    }

    _pwdSecurityLvl = _passwordSecurity.getSecurityLevel(iPwd);

    _pwdSecurityButt.setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(_pwdSecurityLvl)));

    switch(_pwdSecurityLvl){
    case IPasswordSecurity::VERY_LOW:
        _pwdSecurityButt.setToolTip(tr("Your password is not safe at all!"));
        break;
    case IPasswordSecurity::LOW:
        _pwdSecurityButt.setToolTip(tr("Your password can be cracked easily!"));
        break;
    case IPasswordSecurity::MEDIUM:
        _pwdSecurityButt.setToolTip(tr("Your password is at the minimum safety!"));
        break;
    case IPasswordSecurity::HIGH:
        _pwdSecurityButt.setToolTip(tr("Your password is safe!"));
        break;
    case IPasswordSecurity::VERY_HIGH:
        _pwdSecurityButt.setToolTip(tr("More than 50 years is necessary to cracked your password!"));
        break;
    default:
        _pwdSecurityButt.hide();
        return;
    }
    _pwdSecurityButt.show();
}

void AccountWindow::itemChangedLogin(const QString&){
    _loginButt.setIcon(QIcon(":/save"));
    _loginButt.setEnabled(true);
}

void AccountWindow::itemChangedDetails(const QString&){
    _detailsButt.setIcon(QIcon(":/save"));
    _detailsButt.setEnabled(true);
}

bool AccountWindow::saveModifLogin()
{
    int error{_db.modify(QStringList()
                         <<_nameLabel.text()
                         <<_loginLineEdit.text()
                         <<_facAccount.get(_nameLabel.text())->getPassword()
                         <<_facAccount.get(_nameLabel.text())->getDetails()
                         <<QString::number(_facAccount.get(_nameLabel.text())->getSeverityLvl()))};

    if(error != Utility::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(Utility::getMsgError(error).c_str()));
        return false;
    }

    _log.LOG_INFO("Login changed from : "
                  +_facAccount.get(_nameLabel.text())->getLogin().toStdString()
                  +" to : "
                  +_loginLineEdit.text().toStdString());

    fireRefreshAccounts();
    _loginButt.setIcon(QIcon(":/save-dark2"));
    _loginButt.setEnabled(false);
    return true;
}

bool AccountWindow::saveModifDetails()
{
    int error{_db.modify(QStringList()
                         <<_nameLabel.text()
                         <<_facAccount.get(_nameLabel.text())->getLogin()
                         <<_facAccount.get(_nameLabel.text())->getPassword()
                         <<_detailsLineEdit.text()
                         <<QString::number(_facAccount.get(_nameLabel.text())->getSeverityLvl()))};

    if(error != Utility::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(Utility::getMsgError(error).c_str()));
        return false;
    }

    _log.LOG_INFO("Details changed from : "
                  +_facAccount.get(_nameLabel.text())->getDetails().toStdString()
                  +" to : "
                  +_detailsLineEdit.text().toStdString());

    fireRefreshAccounts();
    _detailsButt.setIcon(QIcon(":/save-dark2"));
    _detailsButt.setEnabled(false);
    return true;
}

bool AccountWindow::saveModifPassword(){
    int error{_db.modify(QStringList()
                         <<_facAccount.get(_nameLabel.text())->getName()
                         <<_facAccount.get(_nameLabel.text())->getLogin()
                         <<_encryption.encrypt(_pwdLineEdit.text())
                         <<_facAccount.get(_nameLabel.text())->getDetails()
                         << QString::number(_pwdSecurityLvl))};

    if(error != Utility::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(Utility::getMsgError(error).c_str()));
        return false;
    }

    _log.LOG_INFO("Password modify");

    _pwdLineEdit.clear();
    fireRefreshAccounts();
    return true;
}

void AccountWindow::checkPassword(){
    const QString& newPassEncrypt{_encryption.encrypt(_testLineEdit.text())};
    const QString& currentPassEncrypt{_facAccount.get(_nameLabel.text())->getPassword()};

    if(currentPassEncrypt == newPassEncrypt){
        _testLineEdit.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_GREEN));
        _log.LOG_INFO("Try password : success");
    }else {
        _testLineEdit.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_RED));
        _log.LOG_INFO("Try password : failed");
    }
}

QString AccountWindow::getAccountName() const{
    return _nameLabel.text();
}

void AccountWindow::viewPassword(){
    if(isPassordView){
        isPassordView = false;
        _pwdLineEdit.setEchoMode(QLineEdit::Password);
        _pwdViewButt.setIcon(QIcon(":/hide"));
    }else{
        isPassordView = true;
        _pwdLineEdit.setEchoMode(QLineEdit::Normal);
        _pwdViewButt.setIcon(QIcon(":/view"));
    }
}

void AccountWindow::viewTestPwd(){
    if(isTestView){
        isTestView = false;
        _testLineEdit.setEchoMode(QLineEdit::Password);
        _testViewButt.setIcon(QIcon(":/hide"));
    }else{
        isTestView = true;
        _testLineEdit.setEchoMode(QLineEdit::Normal);
        _testViewButt.setIcon(QIcon(":/view"));
    }
}

void AccountWindow::showWindow(const QString& iName){
    _nameLabel.clear();
    _loginLineEdit.clear();
    _detailsLineEdit.clear();
    _testLineEdit.clear();
    _pwdLineEdit.clear();

    _nameLabel.setText(iName);
    _loginLineEdit.setText(_facAccount.get(_nameLabel.text())->getLogin());
    _loginButt.setIcon(QIcon(":/save-dark2"));
    _loginButt.setEnabled(false);
    _detailsLineEdit.setText(_facAccount.get(_nameLabel.text())->getDetails());
    _detailsButt.setIcon(QIcon(":/save-dark2"));
    _detailsButt.setEnabled(false);

    _testLineEdit.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_2));
    show();
}
