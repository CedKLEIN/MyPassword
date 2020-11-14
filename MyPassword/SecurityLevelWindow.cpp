#include "SecurityLevelWindow.h"
#include "Interface/IPasswordSecurity.h"
#include "Utility.h"

#include <QIcon>
#include <QDebug>

SecurityLevelWindow::SecurityLevelWindow(IPasswordSecurity& iPasswordSecurity):
    _passwordSecurity(iPasswordSecurity)
{
    setStyleSheet(Utility::GET_STYLE_WIDGET()+
                  Utility::GET_STYLE_QLABEL()+
                  Utility::GET_STYLE_QPUSHBUTTON()+
                  "QPushButton:hover{}"+
                  "QPushButton:pressed{"+Utility::SET_BACKGROUND_COLOR(COLOR_DARK_1)+
                  Utility::SET_TEXT_COLOR(COLOR_LIGHT)+"}");
    _titleLabel.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    _titleLabel.setStyleSheet(Utility::SET_TEXT_SIZE(35,BOLD)+
                              Utility::SET_TEXT_COLOR(COLOR_LIGHT));
    _veryHighButt.setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::VERY_HIGH)));
    _highButt.setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::HIGH)));
    _mediumButt.setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::MEDIUM)));
    _lowButt.setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::LOW)));
    _veryLowButt.setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::VERY_LOW)));

    qDebug() << _passwordSecurity.getIconSeverityLvl(IPasswordSecurity::MEDIUM);
    _veryHighButt.setIconSize(QSize(40,40));
    _highButt.setIconSize(QSize(40,40));
    _mediumButt.setIconSize(QSize(40,40));
    _lowButt.setIconSize(QSize(40,40));
    _veryLowButt.setIconSize(QSize(40,40));

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
