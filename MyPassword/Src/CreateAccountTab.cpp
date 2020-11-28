#include "CreateAccountTab.h"
#include "Interface/IDatabase.h"
#include "Interface/IEncryption.h"
#include "Interface/IPasswordSecurity.h"
#include "Interface/ILog.h"
#include "Utility.h"

#include <QDebug>
#include <QMessageBox>
#include <QString>

CreateAccountTab::CreateAccountTab(IEncryption& iEncryption,
                                   IPasswordSecurity& iPasswordSecurity,
                                   IDatabase& iDb,
                                   ILog& iLog):
    _encryption(iEncryption),
    _passwordSecurity(iPasswordSecurity),
    _db(iDb),
    _log(iLog)
{
    setFixedWidth(SIZE_WINDOW_HORIZONTAL);
    setStyleSheet(Utility::GET_STYLE_WIDGET()+
                  Utility::GET_STYLE_QTOOLTYPE()+
                  Utility::GET_STYLE_QLINEEDIT()+
                  Utility::GET_STYLE_QTEXTEDIT()+
                  Utility::GET_STYLE_QPUSHBUTTON()+
                  Utility::GET_STYLE_QLABEL());

    _titleLabel.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    _titleLabel.setStyleSheet(Utility::SET_TEXT_SIZE(40)+
                              Utility::SET_TEXT_COLOR(COLOR_LIGHT));

    _nameErrorLabel.setVisible(false);
    _nameErrorLabel.setStyleSheet(Utility::SET_TEXT_COLOR(COLOR_RED));
    _nameLineEdit.setMaxLength(TEXT_NAME_LENGTH);
    _nameLengthLabel.setStyleSheet(Utility::SET_TEXT_COLOR(COLOR_GREY));
    _nameLayout.addWidget(&_nameLabel);
    _nameLayout.addWidget(&_nameLineEdit);
    _nameLayout.addWidget(&_nameLengthLabel);

    _loginLineEdit.setMaxLength(TEXT_LOGIN_LENGTH);
    _loginLengthLabel.setStyleSheet(Utility::SET_TEXT_COLOR(COLOR_GREY));
    _loginLayout.addWidget(&_loginLabel);
    _loginLayout.addWidget(&_loginLineEdit);
    _loginLayout.addWidget(&_loginLengthLabel);

    _passwordLineEdit.setEchoMode(QLineEdit::Password);
    _passwordLineEdit.setMaxLength(TEXT_PASSWORD_LENGTH);
    _passwordViewButt.setIcon(QIcon(QStringLiteral(":/hide")));
    _passwordViewButt.setIconSize(ICON_SIZE);
    _passwordViewButt.setFocusPolicy(Qt::NoFocus);
    _passwordSecurityButt.setIconSize(ICON_SIZE);
    _passwordSecurityButt.hide();
    _passwordSecurityButt.setFocusPolicy(Qt::NoFocus);
    _passwordLayout.addWidget(&_passwordLabel);
    _passwordLayout.addWidget(&_passwordLineEdit);
    _passwordLayout.addWidget(&_passwordViewButt);
    _passwordLayout.addWidget(&_passwordSecurityButt);
    _passwordLayout.addWidget(&_passwordLengthLabel);

    _detailsLabelLayout.setAlignment(Qt::AlignTop);
    _detailsLabelLayout.addWidget(&_detailsLabel);
    _detailsLengthLabelLayout.setAlignment(Qt::AlignTop);
    _detailsLengthLabelLayout.addWidget(&_detailsLengthLabel);
    _detailsTextEdit.setTabChangesFocus(true);
    _detailsLayout.addLayout(&_detailsLabelLayout);
    _detailsLayout.addWidget(&_detailsTextEdit);
    _detailsLayout.addLayout(&_detailsLengthLabelLayout);

    _validateButt.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                                Utility::SET_HEIGHT(50));
    _validationLabel.setStyleSheet(Utility::SET_TEXT_COLOR(COLOR_GREEN)+
                                   Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,ITALIC));
    _validationLabel.setVisible(false);
    _validationIcon.setVisible(false);
    _validationIcon.setIcon(QIcon(QStringLiteral(":/checked")));
    _validationIcon.setIconSize(ICON_SIZE);
    _validationLayout.setAlignment(Qt::AlignLeft);
    _validationLayout.addWidget(&_validationIcon);
    _validationLayout.addWidget(&_validationLabel);

    _mainLayout.setAlignment(Qt::AlignTop);
    _mainLayout.addSpacing(20);
    _mainLayout.addWidget(&_titleLabel);
    _mainLayout.addSpacing(20);
    _mainLayout.addLayout(&_nameLayout);
    _mainLayout.addWidget(&_nameErrorLabel);
    _mainLayout.addSpacing(10);
    _mainLayout.addLayout(&_loginLayout);
    _mainLayout.addSpacing(10);
    _mainLayout.addLayout(&_passwordLayout);
    _mainLayout.addSpacing(10);
    _mainLayout.addLayout(&_detailsLayout);
    _mainLayout.addSpacing(20);
    _mainLayout.addWidget(&_validateButt);
    _mainLayout.addLayout(&_validationLayout);
    _mainLayout.addSpacing(200);

    setLayout(&_mainLayout);

    QObject::connect(&_nameLineEdit,&QLineEdit::textChanged,this,&CreateAccountTab::textChangedName);
    QObject::connect(&_loginLineEdit,&QLineEdit::textChanged,this,&CreateAccountTab::textChangedLogin);
    QObject::connect(&_passwordLineEdit,&QLineEdit::textChanged,this,&CreateAccountTab::textChangedPassword);
    QObject::connect(&_detailsTextEdit,&QTextEdit::textChanged,this,&CreateAccountTab::textChangedDetails);
    QObject::connect(&_passwordViewButt,&QPushButton::clicked,this,&CreateAccountTab::viewPassword);
    QObject::connect(&_passwordLineEdit,&QLineEdit::textChanged,this,&CreateAccountTab::checkPasswordSecurity);
    QObject::connect(&_validateButt,&QPushButton::clicked,this,&CreateAccountTab::validateForm);
}

void CreateAccountTab::textChangedName(const QString&){
    _nameErrorLabel.setVisible(false);
    _validationLabel.setVisible(false);
    _validationIcon.setVisible(false);
    _nameLineEdit.setStyleSheet(QStringLiteral(""));
    _nameLengthLabel.setText(QString::number(_nameLineEdit.text().length())+"/"+
                             QString::number(TEXT_LOGIN_LENGTH));
}

void CreateAccountTab::textChangedLogin(const QString&){
    _loginLineEdit.setStyleSheet(QStringLiteral(""));
    _loginLengthLabel.setText(QString::number(_loginLineEdit.text().length())+"/"+
                              QString::number(TEXT_LOGIN_LENGTH));
}

void CreateAccountTab::textChangedPassword(const QString&){
    _passwordLineEdit.setStyleSheet(QStringLiteral(""));
    _passwordLengthLabel.setText(QString::number(_passwordLineEdit.text().length())+"/"+
                                 QString::number(TEXT_LOGIN_LENGTH));
}

void CreateAccountTab::textChangedDetails(){
    while(_detailsTextEdit.toPlainText().length()>TEXT_DETAILS_LENGTH){
        _detailsTextEdit.textCursor().deletePreviousChar();
    }
    _detailsTextEdit.setStyleSheet(QStringLiteral(""));
    _detailsLengthLabel.setText(QString::number(_detailsTextEdit.toPlainText().length())+"/"+
                                QString::number(TEXT_DETAILS_LENGTH));
}


void CreateAccountTab::clearWindow(){
    _nameLineEdit.clear();
    _loginLineEdit.clear();
    _passwordLineEdit.clear();
    _detailsTextEdit.clear();
    _nameLineEdit.setStyleSheet(Utility::SET_BORDER_SIZE(0)+
                                Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,BOLD));
}

void CreateAccountTab::checkPasswordSecurity(const QString& iPwd){
    if(iPwd.isEmpty()){
        _passwordSecurityButt.hide();
        return;
    }

    _pwdSecurityLvl = _passwordSecurity.getSecurityLevel(iPwd);

    _passwordSecurityButt.setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(_pwdSecurityLvl)));

    switch(_pwdSecurityLvl){
    case IPasswordSecurity::VERY_LOW:
        _passwordSecurityButt.setToolTip(tr("Safety: VERY LOW"));
        break;
    case IPasswordSecurity::LOW:
        _passwordSecurityButt.setToolTip(tr("Safety: LOW"));
        break;
    case IPasswordSecurity::MEDIUM:
        _passwordSecurityButt.setToolTip(tr("Safety: MEDIUM"));
        break;
    case IPasswordSecurity::HIGH:
        _passwordSecurityButt.setToolTip(tr("Safety: HIGH"));
        break;
    case IPasswordSecurity::VERY_HIGH:
        _passwordSecurityButt.setToolTip(tr("Safety: VERY HIGH"));
        break;
    default:
        _passwordSecurityButt.hide();
        return;
    }
    _passwordSecurityButt.show();
}

void CreateAccountTab::viewPassword(){
    if(isPassordView){
        isPassordView = false;
        _passwordLineEdit.setEchoMode(QLineEdit::Password);
        _passwordViewButt.setIcon(QIcon(QStringLiteral(":/hide")));

    }else{
        isPassordView = true;
        _passwordLineEdit.setEchoMode(QLineEdit::Normal);
        _passwordViewButt.setIcon(QIcon(QStringLiteral(":/view")));
    }
}

void CreateAccountTab::validateForm() {
    if (_nameLineEdit.text().isEmpty()){
        _nameErrorLabel.setVisible(true);
        _nameLineEdit.setStyleSheet(Utility::SET_BORDER_SIZE(1)+
                                    Utility::SET_BACKGROUND_COLOR(COLOR_RED));
        return;
    }

    int error{_db.create(QStringList()
                         <<_nameLineEdit.text()
                         <<_loginLineEdit.text()
                         <<_encryption.encrypt(_passwordLineEdit.text())
                         <<_detailsTextEdit.toPlainText()
                         << QString::number(_pwdSecurityLvl))};

    if(error != Utility::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(Utility::getMsgError(error).c_str()));
        return;
    }

    _log.LOG_INFO("Account created : "+_nameLineEdit.text().toStdString());

    fireEventUpdate();
    clearWindow();
    _validationLabel.setVisible(true);
    _validationIcon.setVisible(true);
    _nameLineEdit.setFocus();
}

void CreateAccountTab::onTabSelected(){
    _validationLabel.setVisible(false);
    _validationIcon.setVisible(false);
    _nameErrorLabel.setVisible(false);
    _nameLineEdit.setStyleSheet("");
    _nameLineEdit.setFocus();
}

