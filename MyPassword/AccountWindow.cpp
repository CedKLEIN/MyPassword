#include "AccountWindow.h"

#include "SecurityLevelWindow.h"
#include "Interface/IEncryption.h"
#include "Interface/IPasswordSecurity.h"
#include "Interface/IDatabase.h"
#include "Utility.h"
#include "Interface/ILog.h"

#include <QDebug>
#include <QMessageBox>

AccountWindow::AccountWindow(const QString& iAccountName,
                             FacAccount &iFacAccount,
                             IEncryption& iEncryption,
                             IPasswordSecurity& iPasswordSecurity,
                             SecurityLevelWindow& iSecurityLevelWindow,
                             IDatabase& iDb,
                             ILog& iLog) :
    _accountName(iAccountName),
    _facAccount(iFacAccount),
    _encryption(iEncryption),
    _passwordSecurity(iPasswordSecurity),
    _securityLevelWindow(iSecurityLevelWindow),
    _db(iDb),
    _log(iLog)
{
    setFixedWidth(SIZE_WINDOW_HORIZONTAL);
    move(SIZE_WINDOW_HORIZONTAL,0);
    setWindowTitle(" ");
    adjustSize();

    setStyleSheet(Utility::GET_STYLE_WIDGET()+
                  Utility::GET_STYLE_QLINEEDIT()+
                  Utility::GET_STYLE_QPUSHBUTTON()+
                  Utility::GET_STYLE_QLABEL());

    _name.setText(_facAccount.get(_accountName)->getName());
    _name.setAlignment(Qt::AlignCenter);
    _name.setStyleSheet(Utility::SET_TEXT_SIZE(40,BOLD)+
                        Utility::SET_TEXT_COLOR(COLOR_LIGHT));

    _loginLabel.setText("Login : ");
    _loginLineEdit.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_1)+
                                 Utility::SET_TEXT_COLOR(COLOR_BLUE_LIGHT)+
                                 Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,BOLD));
    _saveLoginButt.setIconSize(ICON_SIZE);
    _saveLoginButt.setToolTip("Save change");
    _LoginLayout.addWidget(&_loginLabel);
    _LoginLayout.addWidget(&_loginLineEdit);
    _LoginLayout.addWidget(&_saveLoginButt);

    _detailsLabel.setText("Details : ");
    _detailsLineEdit.setText(_facAccount.get(_accountName)->getDetails());
    _detailsLineEdit.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_1)+
                                   Utility::SET_TEXT_COLOR(COLOR_BLUE_LIGHT)+
                                   Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,BOLD));
    _saveDetailsButt.setIconSize(ICON_SIZE);
    _saveDetailsButt.setToolTip("Save change");
    _detailsLayout.addWidget(&_detailsLabel);
    _detailsLayout.addWidget(&_detailsLineEdit);
    _detailsLayout.addWidget(&_saveDetailsButt);

    _testActivateButt.setText(" Test your password");
    _testActivateButt.setIcon(QIcon(":/arrow-right"));
    _testActivateButt.setIconSize(ICON_SIZE);
    _testActivateButt.setStyleSheet(Utility::SET_TEXT_COLOR(COLOR_YELLOW));
    _testButt.setVisible(isTestVisible);
    _testLineEdit.setEchoMode(QLineEdit::Password);
    _testLineEdit.setPlaceholderText("Test here...");
    _testLineEdit.setVisible(isTestVisible);
    _testButt.setText("Check");
    _testButt.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                            Utility::SET_HEIGHT(35));
    _testViewButt.setIcon(QIcon(":/hide"));
    _testViewButt.setIconSize(ICON_SIZE);
    _testViewButt.setVisible(isTestVisible);
    _testLayout.addWidget(&_testLineEdit);
    _testLayout.addWidget(&_testViewButt);

    _pwdActivateButt.setText(" Change your password");
    _pwdActivateButt.setIcon(QIcon(":/arrow-right"));
    _pwdActivateButt.setIconSize(ICON_SIZE);
    _pwdActivateButt.setStyleSheet(Utility::SET_TEXT_COLOR(COLOR_YELLOW));
    _pwdSecurityButt.setIconSize(ICON_SIZE);
    _pwdSecurityButt.hide();
    _pwdLineEdit.setPlaceholderText("Password");
    _pwdLineEdit.setEchoMode(QLineEdit::Password);
    _pwdLineEdit.setVisible(isTestVisible);
    _pwdButt.setText("Change password");
    _pwdButt.setVisible(isTestVisible);
    _pwdButt.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                            Utility::SET_HEIGHT(35));
    _pwdViewButt.setIcon(QIcon(":/hide"));
    _pwdViewButt.setIconSize(ICON_SIZE);
    _pwdViewButt.setVisible(isTestVisible);
    _pwdLayout.addWidget(&_pwdLineEdit);
    _pwdLayout.addWidget(&_pwdViewButt);
    _pwdLayout.addWidget(&_pwdSecurityButt);

    _deleteButt.setText(" Delete account");
    _deleteButt.setStyleSheet(Utility::SET_TEXT_COLOR(COLOR_RED));
    _deleteButt.setIcon(QIcon(":/delete"));
    _deleteButt.setIconSize(ICON_SIZE);

    _mainLayout.addSpacing(20);
    _mainLayout.addWidget(&_name);
    _mainLayout.addSpacing(25);
    _mainLayout.addLayout(&_LoginLayout);
    _mainLayout.addLayout(&_detailsLayout);
    _mainLayout.addSpacing(25);

    _mainLayout.addWidget(&_testActivateButt);
    _mainLayout.addLayout(&_testLayout);
    _mainLayout.addWidget(&_testButt);

    _mainLayout.addWidget(&_pwdActivateButt);
    _mainLayout.addLayout(&_pwdLayout);
    _mainLayout.addWidget(&_pwdButt);
    _mainLayout.addWidget(&_deleteButt);

    setLayout(&_mainLayout);

    QObject::connect(&_pwdSecurityButt,&QPushButton::clicked,this,&AccountWindow::showSecurityLvlWindow);
    QObject::connect(&_pwdLineEdit,&QLineEdit::textChanged,this,&AccountWindow::checkPasswordSecurity);
    QObject::connect(&_pwdViewButt,&QPushButton::clicked,this,&AccountWindow::viewPassword);
    QObject::connect(&_testViewButt,&QPushButton::clicked,this,&AccountWindow::viewTestPwd);
    QObject::connect(&_loginLineEdit,&QLineEdit::textChanged,this,&AccountWindow::itemChangedLogin);
    QObject::connect(&_detailsLineEdit,&QLineEdit::textChanged,this,&AccountWindow::itemChangedDetails);
    QObject::connect(&_deleteButt,&QPushButton::clicked,this,&AccountWindow::deleteAccounts);
    QObject::connect(&_testActivateButt,&QPushButton::clicked,this,&AccountWindow::enableCheckPassword);
    QObject::connect(&_testButt,&QPushButton::clicked,this,&AccountWindow::checkPassword);
    QObject::connect(&_saveLoginButt,&QPushButton::clicked,this,&AccountWindow::saveModifLogin);
    QObject::connect(&_saveDetailsButt,&QPushButton::clicked,this,&AccountWindow::saveModifDetails);
    QObject::connect(&_pwdActivateButt,&QPushButton::clicked,this,&AccountWindow::enableChangePassword);
    QObject::connect(&_pwdButt,&QPushButton::clicked,this,&AccountWindow::saveModifPassword);
}

void AccountWindow::showSecurityLvlWindow(){
    _securityLevelWindow.show();
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
    _saveLoginButt.setIcon(QIcon(":/save"));
    _saveLoginButt.setEnabled(true);
}

void AccountWindow::itemChangedDetails(const QString&){
    _saveDetailsButt.setIcon(QIcon(":/save"));
    _saveDetailsButt.setEnabled(true);
}

bool AccountWindow::saveModifLogin()
{
    int error{_db.modify(QStringList()
                         <<_name.text()
                         <<_loginLineEdit.text()
                         <<_facAccount.get(_accountName)->getPassword()
                         <<_facAccount.get(_accountName)->getDetails())};

    if(error != Utility::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(Utility::getMsgError(error).c_str()));
        return false;
    }

    _log.LOG_INFO("Login changed from : "
                  +_facAccount.get(_accountName)->getLogin().toStdString()
                  +" to : "
                  +_loginLineEdit.text().toStdString());

    fireEventClose();
    this->close();

    return true;
}

bool AccountWindow::saveModifDetails()
{
    int error{_db.modify(QStringList()
                         <<_name.text()
                         <<_facAccount.get(_accountName)->getLogin()
                         <<_facAccount.get(_accountName)->getPassword()
                         <<_detailsLineEdit.text())};

    if(error != Utility::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(Utility::getMsgError(error).c_str()));
        return false;
    }

    _log.LOG_INFO("Details changed from : "
                  +_facAccount.get(_accountName)->getDetails().toStdString()
                  +" to : "
                  +_detailsLineEdit.text().toStdString());

    fireEventClose();
    this->close();
    return true;
}

bool AccountWindow::saveModifPassword(){
    int error{_db.modify(QStringList()
                         <<_facAccount.get(_accountName)->getName()
                         <<_facAccount.get(_accountName)->getLogin()
                         <<_encryption.encrypt(_pwdLineEdit.text())
                         <<_facAccount.get(_accountName)->getDetails()
                         << QString::number(_pwdSecurityLvl))};

    if(error != Utility::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(Utility::getMsgError(error).c_str()));
        return false;
    }

    _log.LOG_INFO("Password modify");

    fireEventClose();
    this->close();
    return true;
}

void AccountWindow::deleteAccounts(){
    int answer{QMessageBox::warning(this, tr("Delete account"),
                                    tr("Do you really want to delete your account "+_name.text().toLocal8Bit()+"?"),
                                    QMessageBox::Yes | QMessageBox::No)};

    if(answer != QMessageBox::Yes)
        return;

    int error{_db.remove(_name.text())};

    if(error != Utility::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(Utility::getMsgError(error).c_str()));
        return;
    }

    _log.LOG_INFO("Account deleted : "+_name.text().toStdString());

    fireEventClose();
    this->close();
}

void AccountWindow::checkPassword(){
    QString newPassEncrypt = _encryption.encrypt(_testLineEdit.text());
    QString currentPassEncrypt = _facAccount.get(_accountName)->getPassword();

    if(currentPassEncrypt == newPassEncrypt){
        _testLineEdit.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_GREEN));
        _log.LOG_INFO("Try password : success");
    }else {
        _testLineEdit.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_RED));
        _log.LOG_INFO("Try password : failed");
    }
}

void AccountWindow::enableCheckPassword(){
    if(isTestVisible){
        isTestVisible = false;
        _testActivateButt.setIcon(QIcon(":/arrow-right"));
        _testLineEdit.setVisible(isTestVisible);
        _testViewButt.setVisible(isTestVisible);
        _testButt.setVisible(isTestVisible);
    } else {
        isTestVisible = true;
        _testActivateButt.setIcon(QIcon(":/arrow-down"));
        _testLineEdit.setVisible(isTestVisible);
        _testViewButt.setVisible(isTestVisible);
        _testButt.setVisible(isTestVisible);
    }
    adjustSize();
}

void AccountWindow::enableChangePassword(){
    if(isPasswordChangeVisible){
        isPasswordChangeVisible = false;
        _pwdActivateButt.setIcon(QIcon(":/arrow-right"));
        _pwdLineEdit.setVisible(isPasswordChangeVisible);
        _pwdViewButt.setVisible(isPasswordChangeVisible);
        _pwdButt.setVisible(isPasswordChangeVisible);
    } else {
        isPasswordChangeVisible = true;
        _pwdActivateButt.setIcon(QIcon(":/arrow-down"));
        _pwdLineEdit.setVisible(isPasswordChangeVisible);
        _pwdViewButt.setVisible(isPasswordChangeVisible);
        _pwdButt.setVisible(isPasswordChangeVisible);
    }
    adjustSize();
}

QString AccountWindow::getAccountName() const{
    return _accountName;
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

void AccountWindow::showEvent(QShowEvent*){
    _loginLineEdit.setText(_facAccount.get(_accountName)->getLogin());
    _saveLoginButt.setIcon(QIcon(":/save-dark2"));
    _saveLoginButt.setEnabled(false);
    _detailsLineEdit.setText(_facAccount.get(_accountName)->getDetails());
    _saveDetailsButt.setIcon(QIcon(":/save-dark2"));
    _saveDetailsButt.setEnabled(false);
    _testLineEdit.clear();
    _testLineEdit.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_2));
    _pwdLineEdit.clear();
}
