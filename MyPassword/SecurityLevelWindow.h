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
    QPushButton _veryHighButt{tr("Safety: VERY HIGH\nPerfect password, almost impossible to crack!")};
    QPushButton _highButt{tr("Safety: HIGH\nYour password is hack resistant!")};
    QPushButton _mediumButt{tr("Safety: MEDIUM\nThis is the minimum safety level you should use.")};
    QPushButton _lowButt{tr("Safety: LOW\nStill not enough, nerver use this password with sensible account, you will regret it.")};
    QPushButton _veryLowButt{tr("Safety: VERY LOW\nIt is high time to change your password, this password is too short. It can be cracked very quickly with a standard desktop computer.")};
};
