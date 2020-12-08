#include "InfoTab.h"
#include "Interface/IPasswordSecurity.h"
#include "SettingsTab.h"

#include "Utility.h"

InfoTab::InfoTab(IPasswordSecurity& iPasswordSecurity,
                 SettingsTab& iSettingsTab):
    _passwordSecurity{iPasswordSecurity},
    _settingsTab{iSettingsTab}
{
    _settingsTab.addUpdateIconThemeListeners(this);
    setMinimumWidth(SIZE_WINDOW_HORIZONTAL);
    setStyleSheet(Utility::GET_STYLE_WIDGET()+
                  Utility::GET_STYLE_QPUSHBUTTON()+
                  Utility::GET_STYLE_QLABEL()+
                  Utility::GET_STYLE_QLINEEDIT());

    _titleLabel->setStyleSheet(Utility::SET_TEXT_SIZE(50)+
                               Utility::SET_TEXT_COLOR(COLOR_LIGHT));
    _titleLayout->setAlignment(Qt::AlignCenter);
    _iconTitle->setStyleSheet(Utility::SET_HEIGHT(50));
    _iconTitle->setIconSize(QSize{40,40});
    _iconTitle->setFocusPolicy(Qt::NoFocus);
    _titleLayout->addWidget(_iconTitle);
    _titleLayout->addWidget(_titleLabel);

    _aboutAppLineEdit->setStyleSheet(Utility::SET_TEXT_SIZE(19)+
                                     Utility::SET_HEIGHT(40));
    _webSiteLineEdit->setStyleSheet(Utility::SET_TEXT_SIZE(19)+
                                    Utility::SET_HEIGHT(40));

    setIcon();

    setSecurityButt(_veryHighButt);
    setSecurityButt(_highButt);
    setSecurityButt(_mediumButt);
    setSecurityButt(_lowButt);
    setSecurityButt(_veryLowButt);

    _securityLayout->addWidget(_veryHighButt);
    _securityLayout->addWidget(_highButt);
    _securityLayout->addWidget(_mediumButt);
    _securityLayout->addWidget(_lowButt);
    _securityLayout->addWidget(_veryLowButt);
    _securityWidget->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_2));
    _securityWidget->setLayout(_securityLayout);

    _attributionContentLabel->setStyleSheet(Utility::SET_TEXT_COLOR(COLOR_LIGHT));
    _attributionContentLabel->setText(tr("Icon made by SmashIcons from www.flaticon.com\n"
                                         "Icon made by FreePik from www.flaticon.com\n"
                                         "Icon made by Kinanshastry from www.flaticon.com\n"
                                         "Icon made by Chanut from www.flaticon.com\n"
                                         "Icon made by Roundicons from www.flaticon.com\n"
                                         "Icon made by srip from www.flaticon.com\n"
                                         "Icon made by Those Icons from www.flaticon.com\n"
                                         "Icon made by Pixel perfect from www.flaticon.com\n"
                                         "Icon made by prettycons from www.flaticon.com"));
    _attributionLayout->addWidget(_attributionContentLabel);
    _attributionWidget->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_2));
    _attributionWidget->setLayout(_attributionLayout);

    _scrollBarLayout->setAlignment(Qt::AlignTop);
    _scrollBarLayout->addWidget(_aboutAppLabel);
    _scrollBarLayout->addWidget(_aboutAppLineEdit);
    _scrollBarLayout->addSpacing(20);
    _scrollBarLayout->addWidget(_webSiteLabel);
    _scrollBarLayout->addWidget(_webSiteLineEdit);
    _scrollBarLayout->addSpacing(20);
    _scrollBarLayout->addWidget(_securityLabel);
    _scrollBarLayout->addWidget(_securityWidget);
    _scrollBarLayout->addSpacing(20);
    _scrollBarLayout->addWidget(_attributionLabel);
    _scrollBarLayout->addWidget(_attributionWidget);
    _scrollBarLayout->addSpacing(20);

    _scrollBarWidget->setLayout(_scrollBarLayout);
    _scrollBarWidget->setStyleSheet(Utility::SET_BORDER_SIZE(0));
    _scrollArea->setWidgetResizable(true);
    _scrollArea->setStyleSheet(QLatin1String("QScrollArea{")+Utility::SET_BORDER_SIZE(0)+
                               QLatin1String("}")+
                               QLatin1String("QScrollBar:vertical {width: 2px;}"));
    _scrollArea->setWidget(_scrollBarWidget);
    _mainLayout->setAlignment(Qt::AlignTop);
    _mainLayout->addSpacing(20);
    _mainLayout->addLayout(_titleLayout);
    _mainLayout->addSpacing(20);
    _mainLayout->addWidget(_scrollArea);
    setLayout(_mainLayout);
}

void InfoTab::setSecurityButt(QPushButton* iButt){
    iButt->setFocusPolicy(Qt::NoFocus);
    iButt->setIconSize(QSize(40,40));
    iButt->setStyleSheet(Utility::SET_TEXT_ALIGN(LEFT)+
                         Utility::SET_TEXT_SIZE(19)+
                         Utility::SET_HEIGHT(50));
}

void InfoTab::setIcon(){
    _veryHighButt->setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::VERY_HIGH)));
    _highButt->setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::HIGH)));
    _mediumButt->setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::MEDIUM)));
    _lowButt->setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::LOW)));
    _veryLowButt->setIcon(QIcon(_passwordSecurity.getIconSeverityLvl(IPasswordSecurity::VERY_LOW)));
}

void InfoTab::onEventUpdateIconTheme(){
    setIcon();
}

