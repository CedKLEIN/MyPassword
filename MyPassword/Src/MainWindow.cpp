#include "MainWindow.h"

#include "AccountTab.h"
#include "CreateAccountTab.h"
#include "GenerateFileTab.h"
#include "SettingsTab.h"
#include "InfoTab.h"

#include "Utility.h"

#include <QIcon>

MainWindow::MainWindow(AccountTab& iAccountTab,
                       CreateAccountTab& iCreateAccountTab,
                       GenerateFileTab& iGenerateFileTab,
                       SettingsTab& iSettingsTab,
                       InfoTab& iInfoTab):
    _accountTab(iAccountTab),
    _createAccountTab(iCreateAccountTab),
    _generateFileTab(iGenerateFileTab),
    _settingsTab(iSettingsTab),
    _infoTab(iInfoTab)
{
    setWindowTitle("MyPassword");
    setMinimumHeight(SIZE_WINDOW_VERTICAL);
    setWindowIcon(QIcon(QStringLiteral(":/security")));
    move(0,0);
    setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_1)+
                  Utility::SET_TEXT_COLOR(COLOR_LIGHT));

    _tabAccountButt->setIcon(QIcon(QStringLiteral(":/house")));
    _tabAccountButt->setIconSize(QSize(40,40));
    _tabAccountButt->setFocusPolicy(Qt::NoFocus);
    setButtSelected(_tabAccountButt);

    _tabCreateAccountButt->setIcon(QIcon(QStringLiteral(":/add_grey")));
    _tabCreateAccountButt->setIconSize(QSize(40,40));
    _tabCreateAccountButt->setFocusPolicy(Qt::NoFocus);
    setButtNotSelected(_tabCreateAccountButt);

    _tabGenerateFileButt->setIcon(QIcon(QStringLiteral(":/paper_grey")));
    _tabGenerateFileButt->setIconSize(QSize(40,40));
    _tabGenerateFileButt->setFocusPolicy(Qt::NoFocus);
    setButtNotSelected(_tabGenerateFileButt);

    _tabSettingsButt->setIcon(QIcon(QStringLiteral(":/settings_grey")));
    _tabSettingsButt->setIconSize(QSize(40,40));
    _tabSettingsButt->setFocusPolicy(Qt::NoFocus);
    setButtNotSelected(_tabSettingsButt);

    _tabInfoButt->setIcon(QIcon(QStringLiteral(":/question_grey")));
    _tabInfoButt->setIconSize(QSize(40,40));
    _tabInfoButt->setFocusPolicy(Qt::NoFocus);
    setButtNotSelected(_tabInfoButt);

    _createAccountTab.setVisible(false);
    _generateFileTab.setVisible(false);
    _settingsTab.setVisible(false);
    _infoTab.setVisible(false);

    _menuLayout->setContentsMargins(0,0,0,0);
    _menuLayout->setAlignment(Qt::AlignTop);
    _menuLayout->addSpacing(10);
    _menuLayout->addWidget(_tabAccountButt);
    _menuLayout->addWidget(_tabCreateAccountButt);
    _menuLayout->addWidget(_tabGenerateFileButt);
    _menuLayout->addWidget(_tabSettingsButt);
    _menuLayout->addWidget(_tabInfoButt);

    _menu->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_2));
    _menu->setFixedWidth(80);
    _menu->setLayout(_menuLayout);

    _mainLayout->setContentsMargins(0,0,0,0);
    _mainLayout->setAlignment(Qt::AlignLeft);
    _mainLayout->addWidget(_menu);
    _mainLayout->addWidget(&_accountTab);
    _mainLayout->addWidget(&_createAccountTab);
    _mainLayout->addWidget(&_generateFileTab);
    _mainLayout->addWidget(&_settingsTab);
    _mainLayout->addWidget(&_infoTab);
    setLayout(_mainLayout);

    QObject::connect(_tabAccountButt,&QPushButton::clicked,this,&MainWindow::showTabAccounts);
    QObject::connect(_tabCreateAccountButt,&QPushButton::clicked,this,&MainWindow::showTabCreateAccount);
    QObject::connect(_tabGenerateFileButt,&QPushButton::clicked,this,&MainWindow::showTabGenerateFile);
    QObject::connect(_tabSettingsButt,&QPushButton::clicked,this,&MainWindow::showTabSettings);
    QObject::connect(_tabInfoButt,&QPushButton::clicked,this,&MainWindow::showTabInfo);
}

void MainWindow::setButtNotSelected(QPushButton* iButt){
    iButt->setStyleSheet(Utility::SET_WIDTH(80)+
                        Utility::SET_HEIGHT(70)+
                        Utility::SET_BACKGROUND_COLOR(COLOR_DARK_2)+
                        Utility::SET_BORDER_SIZE(0));
}

void MainWindow::setButtSelected(QPushButton* iButt){
    iButt->setStyleSheet(Utility::SET_WIDTH(76)+
                        Utility::SET_HEIGHT(70)+
                        Utility::SET_BACKGROUND_COLOR(COLOR_DARK_2)+
                        Utility::SET_BORDER_SIZE(0)+
                        Utility::SET_BORDER_WIDTH(0,0,0,4)+
                        Utility::SET_BORDER_STYLE(OUTSET)+
                        Utility::SET_BORDER_COLOR(COLOR_LIGHT));
}

void MainWindow::showTabAccounts(){
    reset();
    _accountTab.setVisible(true);
    _tabAccountButt->setIcon(QIcon(QStringLiteral(":/house")));
    setButtSelected(_tabAccountButt);
}
void MainWindow::showTabCreateAccount(){
    reset();
    _createAccountTab.setVisible(true);
    _createAccountTab.onTabSelected();
    _tabCreateAccountButt->setIcon(QIcon(QStringLiteral(":/add")));
    setButtSelected(_tabCreateAccountButt);
}

void MainWindow::showTabGenerateFile(){
    reset();
    _generateFileTab.setVisible(true);
    _generateFileTab.onTabSelected();
    _tabGenerateFileButt->setIcon(QIcon(QStringLiteral(":/paper")));
    setButtSelected(_tabGenerateFileButt);
}

void MainWindow::showTabSettings(){
    reset();
    _settingsTab.setVisible(true);
    _tabSettingsButt->setIcon(QIcon(QStringLiteral(":/settings")));
    setButtSelected(_tabSettingsButt);
}

void MainWindow::showTabInfo(){
    reset();
    _infoTab.setVisible(true);
    _tabInfoButt->setIcon(QIcon(QStringLiteral(":/question")));
    setButtSelected(_tabInfoButt);
}

void MainWindow::reset(){
    hideTabs();
    makeIconGrey();
}

void MainWindow::hideTabs(){
    _accountTab.setVisible(false);
    _createAccountTab.setVisible(false);
    _generateFileTab.setVisible(false);
    _settingsTab.setVisible(false);
    _infoTab.setVisible(false);
}

void MainWindow::makeIconGrey(){
    _tabAccountButt->setIcon(QIcon(QStringLiteral(":/house_grey")));
    _tabCreateAccountButt->setIcon(QIcon(QStringLiteral(":/add_grey")));
    _tabGenerateFileButt->setIcon(QIcon(QStringLiteral(":/paper_grey")));
    _tabSettingsButt->setIcon(QIcon(QStringLiteral(":/settings_grey")));
    _tabInfoButt->setIcon(QIcon(QStringLiteral(":/question_grey")));

    setButtNotSelected(_tabAccountButt);
    setButtNotSelected(_tabCreateAccountButt);
    setButtNotSelected(_tabGenerateFileButt);
    setButtNotSelected(_tabSettingsButt);
    setButtNotSelected(_tabInfoButt);
}
