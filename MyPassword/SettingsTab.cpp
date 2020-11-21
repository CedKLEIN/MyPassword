#include "SettingsTab.h"
#include "Account.h"
#include "Interface/IDatabase.h"
#include "Interface/ISettings.h"
#include "Utility.h"

#include <QMessageBox>
#include <QDebug>

static const QString settingsTab_english{QObject::tr("  English")};
static const QString settingsTab_french{QObject::tr("  French")};
static const QString settingsTab_spanish{QObject::tr("  Spanish")};

SettingsTab::SettingsTab(FacAccount& iFacAccount,IDatabase& iDatabase,ISettings& iSettings):
    _facAccount{iFacAccount},
    _database{iDatabase},
    _settings{iSettings}
{
    setFixedWidth(SIZE_WINDOW_HORIZONTAL);
    setStyleSheet(Utility::GET_STYLE_WIDGET()+
                  Utility::GET_STYLE_QLABEL()+
                  Utility::GET_STYLE_QPUSHBUTTON()+
                  Utility::GET_STYLE_QCHECKBOX());

    _titleLabel.setStyleSheet(Utility::SET_TEXT_SIZE(40)+
                              Utility::SET_TEXT_COLOR(COLOR_LIGHT));
    _titleLayout.setAlignment(Qt::AlignCenter);
    _titleLayout.addWidget(&_titleLabel);

    _languageComboBox.setStyleSheet(Utility::SET_HEIGHT(40)+
                                    Utility::SET_BORDER_SIZE(0)+
                                    Utility::SET_BACKGROUND_COLOR(COLOR_DARK_2)+
                                    Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,BOLD));
    setComboBoxLanguage();

    _securityIconShowCheckBox.setChecked(_settings.isSecurityIconShow());

    _resetButt.setStyleSheet(Utility::SET_HEIGHT(40)+
                             Utility::SET_BACKGROUND_COLOR(COLOR_BLUE));

    _mainLayout.setAlignment(Qt::AlignTop);
    _mainLayout.addSpacing(20);
    _mainLayout.addLayout(&_titleLayout);
    _mainLayout.addSpacing(20);
    _mainLayout.addWidget(&_languageLabel);
    _mainLayout.addWidget(&_languageComboBox);
    _mainLayout.addSpacing(20);
    _mainLayout.addWidget(&_securityLabel);
    _mainLayout.addWidget(&_securityIconShowCheckBox);
    _mainLayout.addSpacing(20);
    _mainLayout.addWidget(&_resetLabel);
    _mainLayout.addWidget(&_resetButt);
    setLayout(&_mainLayout);

    QObject::connect(&_languageComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&SettingsTab::languageChange);
    QObject::connect(&_securityIconShowCheckBox,&QCheckBox::stateChanged,this,&SettingsTab::securityIconShowChange);
    QObject::connect(&_resetButt,&QPushButton::clicked,this,&SettingsTab::reset);
}

void SettingsTab::setComboBoxLanguage(){
    if(_settings.getLanguage() == ENGLISH){
        _languageComboBox.addItem(QIcon(QStringLiteral(":/english")),settingsTab_english);
        _languageComboBox.addItem(QIcon(QStringLiteral(":/france")),settingsTab_french);
        _languageComboBox.addItem(QIcon(QStringLiteral(":/spanish")),settingsTab_spanish);
    } else if(_settings.getLanguage() == FRENCH) {
        _languageComboBox.addItem(QIcon(QStringLiteral(":/france")),settingsTab_french);
        _languageComboBox.addItem(QIcon(QStringLiteral(":/english")),settingsTab_english);
        _languageComboBox.addItem(QIcon(QStringLiteral(":/spanish")),settingsTab_spanish);
    } else if(_settings.getLanguage() == SPANISH) {
        _languageComboBox.addItem(QIcon(QStringLiteral(":/spanish")),settingsTab_spanish);
        _languageComboBox.addItem(QIcon(QStringLiteral(":/english")),settingsTab_english);
        _languageComboBox.addItem(QIcon(QStringLiteral(":/france")),settingsTab_french);
    }
}

void SettingsTab::reset(){
    int answer{QMessageBox::warning(this, tr("Reset"),
                                    tr("Do you really want to delete all your accounts ?"),
                                    QMessageBox::Yes | QMessageBox::No)};

    if(answer != QMessageBox::Yes)
        return;

    _database.removeAll();
    fireRefreshAccounts();
}

void SettingsTab::languageChange(int iIndex){
    const QString& iNewLanguage{_languageComboBox.itemText(iIndex)};

    if(iNewLanguage == settingsTab_english)
        _settings.setLanguage(ENGLISH);
    else if(iNewLanguage == settingsTab_french)
        _settings.setLanguage(FRENCH);
    else if(iNewLanguage == settingsTab_spanish)
        _settings.setLanguage(SPANISH);
}

void SettingsTab::securityIconShowChange(int){
    _settings.setIsSecurityIconShow(_securityIconShowCheckBox.isChecked());
    fireRefreshAccounts();
}
