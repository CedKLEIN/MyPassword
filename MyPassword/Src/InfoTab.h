#pragma once

#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include "Interface/IUpdateIconThemeListener.h"

class IPasswordSecurity;
class SettingsTab;

class InfoTab: public QWidget, public IUpdateIconThemeListener
{
    Q_OBJECT
public:
    InfoTab(IPasswordSecurity&,SettingsTab&);

private:
    void setSecurityButt(QPushButton *);
    void setIcon();
    void onEventUpdateIconTheme() override final;

    IPasswordSecurity& _passwordSecurity;
    SettingsTab& _settingsTab;

    QWidget* _scrollBarWidget{new QWidget};
    QScrollArea* _scrollArea{new QScrollArea};
    QVBoxLayout* _scrollBarLayout{new QVBoxLayout};

    QLabel* _titleLabel{new QLabel{QStringLiteral("MyPassword")}};
    QPushButton* _iconTitle{new QPushButton{QIcon{QStringLiteral(":/security")},""}};
    QHBoxLayout* _titleLayout{new QHBoxLayout};

    QLabel* _aboutAppLabel{new QLabel{tr("About MyPassword:")}};
    QLineEdit* _aboutAppLineEdit{new QLineEdit{tr("MyPassword deployed the /11/2020 by Cédric KLEIN.")}};

    QLabel* _webSiteLabel{new QLabel{tr("Download and help:")}};
    QLineEdit* _webSiteLineEdit{new QLineEdit{"https://github.com/CedKLEIN/PasswordHandler"}};

    QLabel* _securityLabel{new QLabel{tr("Password Security level:")}};
    QWidget* _securityWidget{new QWidget};
    QPushButton* _veryHighButt{new QPushButton{tr("VERY HIGH:\nPerfect password, almost impossible to crack!")}};
    QPushButton* _highButt{new QPushButton{tr("HIGH:\nYour password is hack resistant!")}};
    QPushButton* _mediumButt{new QPushButton{tr("MEDIUM:\nThis is the minimum safety level you should use.")}};
    QPushButton* _lowButt{new QPushButton{tr("LOW:\nStill not enough, nerver use this password with sensible account.")}};
    QPushButton* _veryLowButt{new QPushButton{tr("VERY LOW:\nIt is high time to change your password, this password is too short.")}};
    QVBoxLayout* _securityLayout{new QVBoxLayout};

    QVBoxLayout* _mainLayout{new QVBoxLayout};
};
