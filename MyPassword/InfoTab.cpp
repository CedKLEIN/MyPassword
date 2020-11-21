#include "InfoTab.h"
#include "Interface/IPasswordSecurity.h"

#include "Utility.h"

InfoTab::InfoTab(IPasswordSecurity& iPasswordSecurity):
    _passwordSecurity{iPasswordSecurity}
{
    setFixedWidth(SIZE_WINDOW_HORIZONTAL);
    setStyleSheet(Utility::GET_STYLE_WIDGET()+
                  Utility::GET_STYLE_QPUSHBUTTON()+
                  Utility::GET_STYLE_QLABEL()+
                  Utility::GET_STYLE_QLINEEDIT());

    _titleLabel.setStyleSheet(Utility::SET_TEXT_SIZE(50)+
                              Utility::SET_TEXT_COLOR(COLOR_LIGHT));
    _titleLayout.setAlignment(Qt::AlignCenter);
    _iconTitle.setStyleSheet(Utility::SET_HEIGHT(50));
    _iconTitle.setIconSize(QSize{40,40});
    _titleLayout.addWidget(&_iconTitle);
    _titleLayout.addWidget(&_titleLabel);

    _aboutAppLineEdit.setStyleSheet(Utility::SET_TEXT_SIZE(19)+
                                    Utility::SET_HEIGHT(40));
    _webSiteLineEdit.setStyleSheet(Utility::SET_TEXT_SIZE(19)+
                                   Utility::SET_HEIGHT(40));

    _veryHighButt.setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::VERY_HIGH)));
    _highButt.setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::HIGH)));
    _mediumButt.setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::MEDIUM)));
    _lowButt.setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::LOW)));
    _veryLowButt.setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::VERY_LOW)));

    setSecurityButt(_veryHighButt);
    setSecurityButt(_highButt);
    setSecurityButt(_mediumButt);
    setSecurityButt(_lowButt);
    setSecurityButt(_veryLowButt);

    _securityLayout.addWidget(&_veryHighButt);
    _securityLayout.addWidget(&_highButt);
    _securityLayout.addWidget(&_mediumButt);
    _securityLayout.addWidget(&_lowButt);
    _securityLayout.addWidget(&_veryLowButt);
    _securityWidget.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_2));
    _securityWidget.setLayout(&_securityLayout);

    _mainLayout.setAlignment(Qt::AlignTop);
    _mainLayout.addSpacing(20);
    _mainLayout.addLayout(&_titleLayout);
    _mainLayout.addSpacing(20);
    _mainLayout.addWidget(&_aboutAppLabel);
    _mainLayout.addWidget(&_aboutAppLineEdit);
    _mainLayout.addSpacing(20);
    _mainLayout.addWidget(&_webSiteLabel);
    _mainLayout.addWidget(&_webSiteLineEdit);
    _mainLayout.addSpacing(20);
    _mainLayout.addWidget(&_securityLabel);
    _mainLayout.addWidget(&_securityWidget);

    setLayout(&_mainLayout);
}

void InfoTab::setSecurityButt(QPushButton& iButt){
    iButt.setIconSize(QSize(40,40));
    iButt.setStyleSheet(Utility::SET_TEXT_ALIGN(LEFT)+
                        Utility::SET_TEXT_SIZE(19)+
                        Utility::SET_HEIGHT(50));
}