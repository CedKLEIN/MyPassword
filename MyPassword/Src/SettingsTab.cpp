#include "SettingsTab.h"
#include "Account.h"
#include "Interface/IDatabase.h"
#include "Interface/ISettings.h"
#include "Interface/ILog.h"
#include "Utility.h"

#include <QMessageBox>
#include <QApplication>
#include <QProcess>

static const QString settingsTab_english{QObject::tr("  English")};
static const QString settingsTab_french{QObject::tr("  French")};
static const QString settingsTab_spanish{QObject::tr("  Spanish")};

SettingsTab::SettingsTab(FacAccount& iFacAccount,
                         IDatabase& iDatabase,
                         ILog& iLog,
                         ISettings& iSettings,
                         QApplication& iApp):
    _facAccount{iFacAccount},
    _database{iDatabase},
    _log{iLog},
    _settings{iSettings},
    _app{iApp}
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
    _securityIconShowCheckBox.setFocusPolicy(Qt::NoFocus);

    _veryHighTheme1Butt.setFocusPolicy(Qt::NoFocus);
    _highTheme1Butt.setFocusPolicy(Qt::NoFocus);
    _mediumTheme1Butt.setFocusPolicy(Qt::NoFocus);
    _lowTheme1Butt.setFocusPolicy(Qt::NoFocus);
    _veryLowTheme1Butt.setFocusPolicy(Qt::NoFocus);
    _securityIconTheme1Layout.setAlignment(Qt::AlignLeft);
    _securityIconTheme1Layout.addWidget(&_securityIconTheme1RadioButton);
    _securityIconTheme1Layout.addWidget(&_veryHighTheme1Butt);
    _securityIconTheme1Layout.addWidget(&_highTheme1Butt);
    _securityIconTheme1Layout.addWidget(&_mediumTheme1Butt);
    _securityIconTheme1Layout.addWidget(&_lowTheme1Butt);
    _securityIconTheme1Layout.addWidget(&_veryLowTheme1Butt);

    _veryHighTheme2Butt.setFocusPolicy(Qt::NoFocus);
    _highTheme2Butt.setFocusPolicy(Qt::NoFocus);
    _mediumTheme2Butt.setFocusPolicy(Qt::NoFocus);
    _lowTheme2Butt.setFocusPolicy(Qt::NoFocus);
    _veryLowTheme2Butt.setFocusPolicy(Qt::NoFocus);
    _securityIconTheme2Layout.setAlignment(Qt::AlignLeft);
    _securityIconTheme2Layout.addWidget(&_securityIconTheme2RadioButton);
    _securityIconTheme2Layout.addWidget(&_veryHighTheme2Butt);
    _securityIconTheme2Layout.addWidget(&_highTheme2Butt);
    _securityIconTheme2Layout.addWidget(&_mediumTheme2Butt);
    _securityIconTheme2Layout.addWidget(&_lowTheme2Butt);
    _securityIconTheme2Layout.addWidget(&_veryLowTheme2Butt);

    _veryHighTheme3Butt.setFocusPolicy(Qt::NoFocus);
    _highTheme3Butt.setFocusPolicy(Qt::NoFocus);
    _mediumTheme3Butt.setFocusPolicy(Qt::NoFocus);
    _lowTheme3Butt.setFocusPolicy(Qt::NoFocus);
    _veryLowTheme3Butt.setFocusPolicy(Qt::NoFocus);
    _securityIconTheme3Layout.setAlignment(Qt::AlignLeft);
    _securityIconTheme3Layout.addWidget(&_securityIconTheme3RadioButton);
    _securityIconTheme3Layout.addWidget(&_veryHighTheme3Butt);
    _securityIconTheme3Layout.addWidget(&_highTheme3Butt);
    _securityIconTheme3Layout.addWidget(&_mediumTheme3Butt);
    _securityIconTheme3Layout.addWidget(&_lowTheme3Butt);
    _securityIconTheme3Layout.addWidget(&_veryLowTheme3Butt);

    _securityIconLayout.addLayout(&_securityIconTheme1Layout);
    _securityIconLayout.addLayout(&_securityIconTheme2Layout);
    _securityIconLayout.addLayout(&_securityIconTheme3Layout);
    _securityIconQWidget.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_2));
    _securityIconQWidget.setLayout(&_securityIconLayout);

    getSecurityThemeSettings();

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
    _mainLayout.addSpacing(10);
    _mainLayout.addWidget(&_securityIconLabel);
    _mainLayout.addWidget(&_securityIconQWidget);
    _mainLayout.addSpacing(20);
    _mainLayout.addWidget(&_resetLabel);
    _mainLayout.addWidget(&_resetButt);
    setLayout(&_mainLayout);

    QObject::connect(&_languageComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&SettingsTab::languageChange);
    QObject::connect(&_securityIconShowCheckBox,&QCheckBox::stateChanged,this,&SettingsTab::securityIconShowChange);
    QObject::connect(&_securityIconTheme1RadioButton,&QRadioButton::toggled,this,&SettingsTab::setSecurityThemeSettings);
    QObject::connect(&_securityIconTheme2RadioButton,&QRadioButton::toggled,this,&SettingsTab::setSecurityThemeSettings);
    QObject::connect(&_securityIconTheme3RadioButton,&QRadioButton::toggled,this,&SettingsTab::setSecurityThemeSettings);
    QObject::connect(&_resetButt,&QPushButton::clicked,this,&SettingsTab::reset);
}

void SettingsTab::getSecurityThemeSettings(){
    if(_settings.getSecurityIconThemes() == SecurityIconThemes1)
        _securityIconTheme1RadioButton.setChecked(true);
    else if(_settings.getSecurityIconThemes() == SecurityIconThemes2)
        _securityIconTheme2RadioButton.setChecked(true);
    else if(_settings.getSecurityIconThemes() == SecurityIconThemes3)
        _securityIconTheme3RadioButton.setChecked(true);
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
    _log.LOG_CRITICAL("Deletion of all account");
    fireRefreshAccounts();
}

void SettingsTab::languageChange(int iIndex){
    const QString& iNewLanguage{_languageComboBox.itemText(iIndex)};

    if(iNewLanguage == settingsTab_english){
        _settings.setLanguage(ENGLISH);
    }
    else if(iNewLanguage == settingsTab_french){
        _settings.setLanguage(FRENCH);
    }
    else if(iNewLanguage == settingsTab_spanish){
        _settings.setLanguage(SPANISH);
    }

    int answer{QMessageBox::warning(this, tr("Change language"),
                         tr("Restart the application to apply the new language?"),
                         QMessageBox::Yes | QMessageBox::No)};

    if(answer == QMessageBox::Yes){
        _app.quit();
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    }
}

void SettingsTab::securityIconShowChange(int){
    _settings.setIsSecurityIconShow(_securityIconShowCheckBox.isChecked());
    fireRefreshAccounts();
}

void SettingsTab::setSecurityThemeSettings(bool){
    if(_securityIconTheme1RadioButton.isChecked())
        _settings.setSecurityIconThemes(SecurityIconThemes1);
    else if(_securityIconTheme2RadioButton.isChecked())
        _settings.setSecurityIconThemes(SecurityIconThemes2);
    else if(_securityIconTheme3RadioButton.isChecked())
        _settings.setSecurityIconThemes(SecurityIconThemes3);

    fireRefreshAccounts();
}
