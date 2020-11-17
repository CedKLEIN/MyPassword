#pragma once

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class IPasswordSecurity;

class SecurityLevelWindow final : public QWidget
{
        Q_OBJECT
public:
    SecurityLevelWindow(IPasswordSecurity &);
    SecurityLevelWindow(SecurityLevelWindow const&)=delete;
    SecurityLevelWindow& operator=(SecurityLevelWindow const&)=delete;

private:
    IPasswordSecurity& _passwordSecurity;

    QVBoxLayout _mainLyt;
    QLabel _titleLabel{tr("Password Security Level")};
    QPushButton _veryHighButt{tr("Your password is uncrackedable, more than 50 years are necessary to unblock it !")};
    QPushButton _highButt{tr("Your password is safe!")};
    QPushButton _mediumButt{tr("This level of password should be the minimum to use, between 1 year and 10 year to cracked it.")};
    QPushButton _lowButt{tr("The password can be cracked in less than 1 year, don't use for social network or site with credit card account.")};
    QPushButton _veryLowButt{tr("The password is really not safe. Less than 1 month is necessary to get it. This should not be used on any way.")};
};
