#include "SecurityLevelWindow.h"
#include "Interface/IPasswordSecurity.h"
#include "Utility.h"

#include <QIcon>
#include <QString>

SecurityLevelWindow::SecurityLevelWindow(IPasswordSecurity& iPasswordSecurity):
    _passwordSecurity(iPasswordSecurity)
{
    setStyleSheet(Utility::GET_STYLE_WIDGET()+
                  QLatin1String("QPushButton{")+
                  Utility::SET_HEIGHT(70)+
                  Utility::SET_BACKGROUND_COLOR(COLOR_DARK_1)+
                  Utility::SET_TEXT_COLOR(COLOR_LIGHT)+
                  Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,BOLD)+
                  Utility::SET_BORDER_SIZE(0)+"}");
    _titleLabel.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    _titleLabel.setStyleSheet(Utility::SET_TEXT_SIZE(35,BOLD)+
                              Utility::SET_TEXT_COLOR(COLOR_LIGHT));
    _veryHighButt.setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::VERY_HIGH)));
    _highButt.setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::HIGH)));
    _mediumButt.setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::MEDIUM)));
    _lowButt.setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::LOW)));
    _veryLowButt.setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::VERY_LOW)));

    _veryHighButt.setIconSize(QSize(60,60));
    _highButt.setIconSize(QSize(60,60));
    _mediumButt.setIconSize(QSize(60,60));
    _lowButt.setIconSize(QSize(60,60));
    _veryLowButt.setIconSize(QSize(60,60));

    _veryHighButt.setStyleSheet(Utility::SET_TEXT_ALIGN(LEFT)+
                                Utility::SET_TEXT_SIZE(20));
    _highButt.setStyleSheet(Utility::SET_TEXT_ALIGN(LEFT)+
                            Utility::SET_TEXT_SIZE(20));
    _mediumButt.setStyleSheet(Utility::SET_TEXT_ALIGN(LEFT)+
                              Utility::SET_TEXT_SIZE(20));
    _lowButt.setStyleSheet(Utility::SET_TEXT_ALIGN(LEFT)+
                           Utility::SET_TEXT_SIZE(20));
    _veryLowButt.setStyleSheet(Utility::SET_TEXT_ALIGN(LEFT)+
                               Utility::SET_TEXT_SIZE(20));

    _mainLyt.addSpacing(20);
    _mainLyt.addWidget(&_titleLabel);
    _mainLyt.addSpacing(30);
    _mainLyt.addWidget(&_veryHighButt);
    _mainLyt.addSpacing(10);
    _mainLyt.addWidget(&_highButt);
    _mainLyt.addSpacing(10);
    _mainLyt.addWidget(&_mediumButt);
    _mainLyt.addSpacing(10);
    _mainLyt.addWidget(&_lowButt);
    _mainLyt.addSpacing(10);
    _mainLyt.addWidget(&_veryLowButt);
    _mainLyt.addSpacing(10);
    setLayout(&_mainLyt);
}
