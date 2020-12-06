#include "AccountWindow.h"

#include "Interface/IEncryption.h"
#include "Interface/IPasswordSecurity.h"
#include "Interface/IDatabase.h"
#include "Utility.h"
#include "Interface/ILog.h"

#include <QMessageBox>
#include <QScrollBar>
#include <QString>

AccountWindow::AccountWindow(FacAccount &iFacAccount,
                             IEncryption& iEncryption,
                             IPasswordSecurity& iPasswordSecurity,
                             IDatabase& iDb,
                             ILog& iLog) :
    _facAccount(iFacAccount),
    _encryption(iEncryption),
    _passwordSecurity(iPasswordSecurity),
    _db(iDb),
    _log(iLog)
{
    setMinimumWidth(SIZE_WINDOW_HORIZONTAL/2);

    setStyleSheet(Utility::GET_STYLE_QLINEEDIT()+
                  Utility::GET_STYLE_QTOOLTYPE()+
                  Utility::GET_STYLE_QTEXTEDIT()+
                  Utility::GET_STYLE_QPUSHBUTTON()+
                  QLatin1String("QPushButton{")+
                  Utility::SET_BACKGROUND_COLOR(COLOR_DARK_0)+QLatin1String("}"));

    _closeButt->setIcon(QIcon(QStringLiteral(":/close")));
    _closeButt->setIconSize(ICON_SIZE);
    _closeLayout->setAlignment(Qt::AlignRight);
    _closeLayout->addWidget(_closeButt);

    _nameLabel->setAlignment(Qt::AlignCenter);
    _nameLabel->setStyleSheet(Utility::SET_HEIGHT(30)+
                             Utility::SET_BORDER_SIZE(0)+
                             Utility::SET_BACKGROUND_COLOR(COLOR_DARK_0)+
                             Utility::SET_TEXT_SIZE(40,BOLD)+
                             Utility::SET_TEXT_COLOR(COLOR_LIGHT));

    _loginLabel->setStyleSheet(Utility::SET_TEXT_COLOR(COLOR_LIGHT));
    _loginSavedButt->setIcon(QIcon(QStringLiteral(":/checked")));
    _loginSavedButt->setIconSize(QSize{17,17});
    _loginSavedButt->setStyleSheet(Utility::SET_TEXT_COLOR(COLOR_GREEN)+
                                  Utility::SET_TEXT_SIZE(17,ITALIC));
    _loginSavedButt->setVisible(false);
    _loginLabelsLayout->setAlignment(Qt::AlignLeft);
    _loginLabelsLayout->addWidget(_loginLabel);
    _loginLabelsLayout->addWidget(_loginSavedButt);

    _loginButt->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                             Utility::SET_HEIGHT(35));
    _loginLineEdit->setMaxLength(TEXT_LOGIN_LENGTH);
    _loginLineEdit->setPlaceholderText(QStringLiteral("..."));

    _detailsLabel->setStyleSheet(Utility::SET_TEXT_COLOR(COLOR_LIGHT));
    _detailsSavedButt->setIcon(QIcon(QStringLiteral(":/checked")));
    _detailsSavedButt->setIconSize(QSize{17,17});
    _detailsSavedButt->setStyleSheet(Utility::SET_TEXT_COLOR(COLOR_GREEN)+
                                    Utility::SET_TEXT_SIZE(17,ITALIC));
    _detailsSavedButt->setVisible(false);
    _detailsLabelsLayout->setAlignment(Qt::AlignLeft);
    _detailsLabelsLayout->addWidget(_detailsLabel);
    _detailsLabelsLayout->addWidget(_detailsSavedButt);
    _detailsButt->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                               Utility::SET_HEIGHT(35));
    _detailsTextEdit->verticalScrollBar()->setStyleSheet(QStringLiteral("QScrollBar:vertical {width: 2px;}"));
    _detailsTextEdit->setPlaceholderText(QStringLiteral("..."));

    _pwdLabel->setStyleSheet(Utility::SET_TEXT_COLOR(COLOR_LIGHT));
    _pwdSavedButt->setIcon(QIcon(QStringLiteral(":/checked")));
    _pwdSavedButt->setIconSize(QSize{17,17});
    _pwdSavedButt->setStyleSheet(Utility::SET_TEXT_COLOR(COLOR_GREEN)+
                                Utility::SET_TEXT_SIZE(17,ITALIC));
    _pwdSavedButt->setVisible(false);
    _pwdLabelsLayout->setAlignment(Qt::AlignLeft);
    _pwdLabelsLayout->addWidget(_pwdLabel);
    _pwdLabelsLayout->addWidget(_pwdSavedButt);
    _pwdSecurityButt->setIconSize(ICON_SIZE);
    _pwdSecurityButt->hide();
    _pwdLineEdit->setPlaceholderText(tr("Password"));
    _pwdLineEdit->setEchoMode(QLineEdit::Password);
    _pwdLineEdit->setMaxLength(TEXT_PASSWORD_LENGTH);
    _pwdButt->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                           Utility::SET_HEIGHT(35));
    _pwdViewButt->setIcon(QIcon(QStringLiteral(":/hide")));
    _pwdViewButt->setIconSize(ICON_SIZE);
    _pwdLayout->addWidget(_pwdLineEdit);
    _pwdLayout->addWidget(_pwdViewButt);
    _pwdLayout->addWidget(_pwdSecurityButt);

    _testLabel->setStyleSheet(Utility::SET_TEXT_COLOR(COLOR_LIGHT));
    _testLineEdit->setEchoMode(QLineEdit::Password);
    _testLineEdit->setPlaceholderText(tr("Test here..."));
    _testLineEdit->setMaxLength(TEXT_PASSWORD_LENGTH);
    _testButt->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                            Utility::SET_HEIGHT(35));
    _testViewButt->setIcon(QIcon(QStringLiteral(":/hide")));
    _testViewButt->setIconSize(ICON_SIZE);
    _testLayout->addWidget(_testLineEdit);
    _testLayout->addWidget(_testViewButt);

    _deleteAccountButt->setIcon(QIcon(QStringLiteral(":/delete")));
    _deleteAccountButt->setIconSize(QSize(20,20));
    _deleteAccountButt->setStyleSheet(QLatin1String("QPushButton:hover{")+
                                     Utility::SET_BACKGROUND_COLOR(COLOR_DARK_1)+
                                     Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,BOLD)+
                                     QLatin1String("}"));

    _mainLayout->setAlignment(Qt::AlignTop);
    _mainLayout->setContentsMargins(0,0,0,0);

    _mainLayout->addLayout(_closeLayout);
    _mainLayout->addSpacing(20);

    _mainLayout->addWidget(_nameLabel);
    _mainLayout->addSpacing(25);

    _mainLayout->addLayout(_loginLabelsLayout);
    _mainLayout->addWidget(_loginLineEdit);
    _mainLayout->addWidget(_loginButt);
    _mainLayout->addSpacing(25);

    _mainLayout->addLayout(_detailsLabelsLayout);
    _mainLayout->addWidget(_detailsTextEdit);
    _mainLayout->addWidget(_detailsButt);
    _mainLayout->addSpacing(25);

    _mainLayout->addLayout(_pwdLabelsLayout);
    _mainLayout->addLayout(_pwdLayout);
    _mainLayout->addWidget(_pwdButt);
    _mainLayout->addSpacing(20);

    _mainLayout->addWidget(_testLabel);
    _mainLayout->addLayout(_testLayout);
    _mainLayout->addWidget(_testButt);
    _mainLayout->addSpacing(10);

    _mainLayout->addWidget(_deleteAccountButt);
    _mainLayout->addSpacing(10);

    setLayout(_mainLayout);

    QObject::connect(_closeButt,&QPushButton::clicked,this,&AccountWindow::hide);
    QObject::connect(_pwdLineEdit,&QLineEdit::textChanged,this,&AccountWindow::checkPasswordSecurity);
    QObject::connect(_pwdViewButt,&QPushButton::clicked,this,&AccountWindow::viewPassword);
    QObject::connect(_testViewButt,&QPushButton::clicked,this,&AccountWindow::viewTestPwd);
    QObject::connect(_detailsTextEdit,&QTextEdit::textChanged,this,&AccountWindow::itemChangedDetails);
    QObject::connect(_testButt,&QPushButton::clicked,this,&AccountWindow::checkPassword);
    QObject::connect(_loginButt,&QPushButton::clicked,this,&AccountWindow::saveModifLogin);
    QObject::connect(_detailsButt,&QPushButton::clicked,this,&AccountWindow::saveModifDetails);
    QObject::connect(_pwdButt,&QPushButton::clicked,this,&AccountWindow::saveModifPassword);
    QObject::connect(_deleteAccountButt,&QPushButton::clicked,this,&AccountWindow::deleteAccount);
}

void AccountWindow::checkPasswordSecurity(const QString& iPwd){
    if(iPwd.isEmpty()){
        _pwdSecurityButt->hide();
        return;
    }

    _pwdSecurityLvl = _passwordSecurity.getSecurityLevel(iPwd);

    _pwdSecurityButt->setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(_pwdSecurityLvl)));

    switch(_pwdSecurityLvl){
    case IPasswordSecurity::VERY_LOW:
        _pwdSecurityButt->setToolTip(tr("Safety: VERY LOW"));
        break;
    case IPasswordSecurity::LOW:
        _pwdSecurityButt->setToolTip(tr("Safety: LOW"));
        break;
    case IPasswordSecurity::MEDIUM:
        _pwdSecurityButt->setToolTip(tr("Safety: MEDIUM"));
        break;
    case IPasswordSecurity::HIGH:
        _pwdSecurityButt->setToolTip(tr("Safety: HIGH"));
        break;
    case IPasswordSecurity::VERY_HIGH:
        _pwdSecurityButt->setToolTip(tr("Safety: VERY HIGH"));
        break;
    default:
        _pwdSecurityButt->hide();
        return;
    }
    _pwdSecurityButt->show();
}

void AccountWindow::itemChangedDetails(){
    while(_detailsTextEdit->toPlainText().length()>TEXT_DETAILS_LENGTH){
        _detailsTextEdit->textCursor().deletePreviousChar();
    }
}

bool AccountWindow::saveModifLogin()
{
    int error{_db.modify(QStringList()
                         <<_nameLabel->text()
                         <<_loginLineEdit->text()
                         <<_facAccount.get(_nameLabel->text())->getPassword()
                         <<_facAccount.get(_nameLabel->text())->getDetails()
                         <<QString::number(_facAccount.get(_nameLabel->text())->getSeverityLvl()))};

    if(error != Utility::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(Utility::getMsgError(error).c_str()));
        return false;
    }

    _log.LOG_INFO("Login changed from : "
                  +_facAccount.get(_nameLabel->text())->getLogin().toStdString()
                  +" to : "
                  +_loginLineEdit->text().toStdString());

    fireRefreshAccounts();
    _loginSavedButt->setVisible(true);
    return true;
}

bool AccountWindow::saveModifDetails()
{
    int error{_db.modify(QStringList()
                         <<_nameLabel->text()
                         <<_facAccount.get(_nameLabel->text())->getLogin()
                         <<_facAccount.get(_nameLabel->text())->getPassword()
                         <<_detailsTextEdit->toPlainText()
                         <<QString::number(_facAccount.get(_nameLabel->text())->getSeverityLvl()))};

    if(error != Utility::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(Utility::getMsgError(error).c_str()));
        return false;
    }

    _log.LOG_INFO("Details changed from : "
                  +_facAccount.get(_nameLabel->text())->getDetails().toStdString()
                  +" to : "
                  +_detailsTextEdit->toPlainText().toStdString());

    fireRefreshAccounts();
    _detailsSavedButt->setVisible(true);
    return true;
}

bool AccountWindow::saveModifPassword(){

    int answer{QMessageBox::warning(this, tr("Change password"),
                                    tr("Do you really want to change your password ?"),
                                    QMessageBox::Yes | QMessageBox::No)};

    if(answer != QMessageBox::Yes)
        return false;

    int error{_db.modify(QStringList()
                         <<_facAccount.get(_nameLabel->text())->getName()
                         <<_facAccount.get(_nameLabel->text())->getLogin()
                         <<_encryption.encrypt(_pwdLineEdit->text())
                         <<_facAccount.get(_nameLabel->text())->getDetails()
                         << QString::number(_pwdSecurityLvl))};

    if(error != Utility::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(Utility::getMsgError(error).c_str()));
        return false;
    }

    _log.LOG_INFO("Password modify");

    _pwdLineEdit->clear();
    fireRefreshAccounts();
    _pwdSavedButt->setVisible(true);
    return true;
}

void AccountWindow::checkPassword(){
    const QString& newPassEncrypt{_encryption.encrypt(_testLineEdit->text())};
    const QString& currentPassEncrypt{_facAccount.get(_nameLabel->text())->getPassword()};

    if(currentPassEncrypt == newPassEncrypt){
        _testLineEdit->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_GREEN));
        _log.LOG_INFO("Try password : success");
    }else {
        _testLineEdit->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_RED));
        _log.LOG_INFO("Try password : failed");
    }
}

QString AccountWindow::getAccountName() const{
    return _nameLabel->text();
}

void AccountWindow::viewPassword(){
    if(isPassordView){
        isPassordView = false;
        _pwdLineEdit->setEchoMode(QLineEdit::Password);
        _pwdViewButt->setIcon(QIcon(QStringLiteral(":/hide")));
    }else{
        isPassordView = true;
        _pwdLineEdit->setEchoMode(QLineEdit::Normal);
        _pwdViewButt->setIcon(QIcon(QStringLiteral(":/view")));
    }
}

void AccountWindow::viewTestPwd(){
    if(isTestView){
        isTestView = false;
        _testLineEdit->setEchoMode(QLineEdit::Password);
        _testViewButt->setIcon(QIcon(QStringLiteral(":/hide")));
    }else{
        isTestView = true;
        _testLineEdit->setEchoMode(QLineEdit::Normal);
        _testViewButt->setIcon(QIcon(QStringLiteral(":/view")));
    }
}

void AccountWindow::showWindow(const QString& iName){
    _nameLabel->clear();
    _loginLineEdit->clear();
    _detailsTextEdit->clear();
    _testLineEdit->clear();
    _pwdLineEdit->clear();
    _loginSavedButt->setVisible(false);
    _detailsSavedButt->setVisible(false);
    _pwdSavedButt->setVisible(false);

    _nameLabel->setText(iName);
    _loginLineEdit->setText(_facAccount.get(_nameLabel->text())->getLogin());
    _detailsTextEdit->setText(_facAccount.get(_nameLabel->text())->getDetails());

    _testLineEdit->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_2));
}

void AccountWindow::deleteAccount(){
    const QString& currentAccount{_nameLabel->text()};

    int answer{QMessageBox::warning(this, tr("Delete account"),
                                    tr("Do you really want to delete your account "+currentAccount.toLocal8Bit()+"?"),
                                    QMessageBox::Yes | QMessageBox::No)};

    if(answer != QMessageBox::Yes)
        return;

    int error{_db.remove(currentAccount)};

    if(error != Utility::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(Utility::getMsgError(error).c_str()));
        return;
    }

    _log.LOG_INFO("Account deleted : "+currentAccount.toStdString());

    fireRefreshAccounts();
    setVisible(false);
}
