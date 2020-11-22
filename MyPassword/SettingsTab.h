#pragma once

#include "Interface/IListener.h"

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
class ISettings;

class SettingsTab final : public QWidget
{
    Q_OBJECT
public:
    SettingsTab(FacAccount&, IDatabase&, ISettings&);

    void addListener(IListener* iListener){
        _listeners.push_back(iListener);
    }

private slots:
    void reset();
    void languageChange(int);
    void securityIconShowChange(int);
    void setSecurityThemeSettings(bool);

private:
    void getSecurityThemeSettings();
    void setComboBoxLanguage();

    void fireRefreshAccounts(){
        for(const auto& listener : _listeners){
            listener->onEventClose();
        }
    }

    FacAccount& _facAccount;
    IDatabase& _database;
    ISettings& _settings;

    QLabel _titleLabel{tr("Settings")};
    QHBoxLayout _titleLayout;

    std::vector<IListener*> _listeners;

    QLabel _languageLabel{tr("Language:")};
    QComboBox _languageComboBox;

    QLabel _securityLabel{tr("Password security:")};
    QCheckBox _securityIconShowCheckBox{tr("Display icon security level in account view")};

    QLabel _securityIconLabel{tr("Theme icon security level:")};

    QRadioButton _securityIconTheme1RadioButton;
    QPushButton _veryHighTheme1Butt{QIcon{QStringLiteral(":/very_high")},""};
    QPushButton _highTheme1Butt{QIcon{QStringLiteral(":/high")},""};
    QPushButton _mediumTheme1Butt{QIcon{QStringLiteral(":/medium")},""};
    QPushButton _lowTheme1Butt{QIcon{QStringLiteral(":/low")},""};
    QPushButton _veryLowTheme1Butt{QIcon{QStringLiteral(":/very_low")},""};
    QHBoxLayout _securityIconTheme1Layout;

    QRadioButton _securityIconTheme2RadioButton;
    QPushButton _veryHighTheme2Butt{QIcon{QStringLiteral(":/very_high_theme2")},""};
    QPushButton _highTheme2Butt{QIcon{QStringLiteral(":/high_theme2")},""};
    QPushButton _mediumTheme2Butt{QIcon{QStringLiteral(":/medium_theme2")},""};
    QPushButton _lowTheme2Butt{QIcon{QStringLiteral(":/low_theme2")},""};
    QPushButton _veryLowTheme2Butt{QIcon{QStringLiteral(":/very_low_theme2")},""};
    QHBoxLayout _securityIconTheme2Layout;

    QRadioButton _securityIconTheme3RadioButton;
    QPushButton _veryHighTheme3Butt{QIcon{QStringLiteral(":/very_high_theme3")},""};
    QPushButton _highTheme3Butt{QIcon{QStringLiteral(":/high_theme3")},""};
    QPushButton _mediumTheme3Butt{QIcon{QStringLiteral(":/medium_theme3")},""};
    QPushButton _lowTheme3Butt{QIcon{QStringLiteral(":/low_theme3")},""};
    QPushButton _veryLowTheme3Butt{QIcon{QStringLiteral(":/very_low_theme3")},""};
    QHBoxLayout _securityIconTheme3Layout;

    QVBoxLayout _securityIconLayout;
    QWidget _securityIconQWidget;

    QLabel _resetLabel{tr("Reset:")};
    QPushButton _resetButt{tr("Delete all accounts")};

    QVBoxLayout _mainLayout;
};
