#pragma once

#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>

class IPasswordSecurity;

class InfoTab: public QWidget
{
    Q_OBJECT
public:
    InfoTab(IPasswordSecurity&);

private:
    void setSecurityButt(QPushButton&);

    IPasswordSecurity& _passwordSecurity;

    QWidget _scrollBarWidget;
    QScrollArea _scrollArea;
    QVBoxLayout _scrollBarLayout;

    QLabel _titleLabel{QStringLiteral("MyPassword")};
    QPushButton _iconTitle{QIcon{QStringLiteral(":/security")},""};
    QHBoxLayout _titleLayout;

    QLabel _aboutAppLabel{tr("About MyPassword:")};
    QLineEdit _aboutAppLineEdit{tr("MyPassword deployed the /11/2020 by Cédric KLEIN.")};

    QLabel _webSiteLabel{tr("Download and help:")};
    QLineEdit _webSiteLineEdit{tr("https://github.com/CedKLEIN/PasswordHandler")};

    QLabel _securityLabel{tr("Password Security level:")};
    QWidget _securityWidget;
    QPushButton _veryHighButt{tr("VERY HIGH:\nPerfect password, almost impossible to crack!")};
    QPushButton _highButt{tr("HIGH:\nYour password is hack resistant!")};
    QPushButton _mediumButt{tr("MEDIUM:\nThis is the minimum safety level you should use.")};
    QPushButton _lowButt{tr("LOW:\nStill not enough, nerver use this password with sensible account.")};
    QPushButton _veryLowButt{tr("VERY LOW:\nIt is high time to change your password, this password is too short.")};
    QVBoxLayout _securityLayout;

    QVBoxLayout _mainLayout;
};
