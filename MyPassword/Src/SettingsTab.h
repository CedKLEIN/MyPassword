#pragma once

#include "Interface/IUpdateAccountListener.h"
#include "Interface/IUpdateIconThemeListener.h"

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QGroupBox>

class FacAccount;
class IDatabase;
class ILog;
class ISettings;
class QApplication;

class SettingsTab final : public QWidget
{
    Q_OBJECT
public:
    SettingsTab(FacAccount&,IDatabase&,ILog&,ISettings&,QApplication&);

    void addUpdateAccountListener(IUpdateAccountListener* iListener){
        _updateAccountListeners.push_back(iListener);
    }

    void addUpdateIconThemeListeners(IUpdateIconThemeListener* iListener){
        _updateIconThemeListeners.push_back(iListener);
    }

private slots:
    void reset();
    void languageChange(int);
    void securityIconShowChange(int);
    void setSecurityThemeSettings(bool);

private:
    void getSecurityThemeSettings();
    void setComboBoxLanguage();

    void fireEventRefreshAccounts(){
        for(const auto& listener : _updateAccountListeners){
            listener->onEventUpdateAccount();
        }
    }

    void fireEventIconTheme(){
        for(const auto& listener : _updateIconThemeListeners){
            listener->onEventUpdateIconTheme();
        }
    }

    FacAccount& _facAccount;
    IDatabase& _database;
    ILog& _log;
    ISettings& _settings;
    QApplication& _app;

    QLabel* _titleLabel{new QLabel{tr("Settings")}};
    QHBoxLayout* _titleLayout{new QHBoxLayout};

    std::vector<IUpdateAccountListener*> _updateAccountListeners;
    std::vector<IUpdateIconThemeListener*> _updateIconThemeListeners;

    QLabel* _languageLabel{new QLabel{tr("Language:")}};
    QComboBox* _languageComboBox{new QComboBox};

    QLabel* _securityLabel{new QLabel{tr("Password security:")}};
    QCheckBox* _securityIconShowCheckBox{new QCheckBox{tr("Display icon security level in account view")}};

    QLabel* _securityIconLabel{new QLabel{tr("Theme icon security level:")}};

    QRadioButton* _securityIconTheme1RadioButton{new QRadioButton};
    QPushButton* _veryHighTheme1Butt{new QPushButton{QIcon{QStringLiteral(":/very_high")},""}};
    QPushButton* _highTheme1Butt{new QPushButton{QIcon{QStringLiteral(":/high")},""}};
    QPushButton* _mediumTheme1Butt{new QPushButton{QIcon{QStringLiteral(":/medium")},""}};
    QPushButton* _lowTheme1Butt{new QPushButton{QIcon{QStringLiteral(":/low")},""}};
    QPushButton* _veryLowTheme1Butt{new QPushButton{QIcon{QStringLiteral(":/very_low")},""}};
    QHBoxLayout* _securityIconTheme1Layout{new QHBoxLayout};

    QRadioButton* _securityIconTheme2RadioButton{new QRadioButton};
    QPushButton* _veryHighTheme2Butt{new QPushButton{QIcon{QStringLiteral(":/very_high_theme2")},""}};
    QPushButton* _highTheme2Butt{new QPushButton{QIcon{QStringLiteral(":/high_theme2")},""}};
    QPushButton* _mediumTheme2Butt{new QPushButton{QIcon{QStringLiteral(":/medium_theme2")},""}};
    QPushButton* _lowTheme2Butt{new QPushButton{QIcon{QStringLiteral(":/low_theme2")},""}};
    QPushButton* _veryLowTheme2Butt{new QPushButton{QIcon{QStringLiteral(":/very_low_theme2")},""}};
    QHBoxLayout* _securityIconTheme2Layout{new QHBoxLayout};

    QRadioButton* _securityIconTheme3RadioButton{new QRadioButton};
    QPushButton* _veryHighTheme3Butt{new QPushButton{QIcon{QStringLiteral(":/very_high_theme3")},""}};
    QPushButton* _highTheme3Butt{new QPushButton{QIcon{QStringLiteral(":/high_theme3")},""}};
    QPushButton* _mediumTheme3Butt{new QPushButton{QIcon{QStringLiteral(":/medium_theme3")},""}};
    QPushButton* _lowTheme3Butt{new QPushButton{QIcon{QStringLiteral(":/low_theme3")},""}};
    QPushButton* _veryLowTheme3Butt{new QPushButton{QIcon{QStringLiteral(":/very_low_theme3")},""}};
    QHBoxLayout* _securityIconTheme3Layout{new QHBoxLayout};

    QVBoxLayout* _securityIconLayout{new QVBoxLayout};
    QWidget* _securityIconQWidget{new QWidget};

    QLabel* _resetLabel{new QLabel{tr("Reset:")}};
    QPushButton* _resetButt{new QPushButton{tr("Delete all accounts")}};

    QVBoxLayout* _mainLayout{new QVBoxLayout};
};
