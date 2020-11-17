#include "MainWindow.h"

#include "AccountTab.h"
#include "CreateAccountTab.h"
#include "GenerateFileTab.h"
#include "SettingsTab.h"

#include "Utility.h"

#include <QIcon>

MainWindow::MainWindow(AccountTab& iAccountTab,
                       CreateAccountTab& iCreateAccountTab,
                       GenerateFileTab& iGenerateFileTab,
                       SettingsTab& iSettingsTab):
    _accountTab(iAccountTab),
    _createAccountTab(iCreateAccountTab),
    _generateFileTab(iGenerateFileTab),
    _settingsTab(iSettingsTab)
{
    setMinimumHeight(SIZE_WINDOW_VERTICAL);
    setWindowIcon(QIcon(":/security"));
    move(0,0);
    setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_1)+
                  Utility::SET_TEXT_COLOR(COLOR_LIGHT));

    _tabAccountButt.setIcon(QIcon(":/house"));
    _tabAccountButt.setIconSize(QSize(40,40));
    _tabAccountButt.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_2)+
                                  Utility::SET_BORDER_SIZE(0));

    _tabCreateAccountButt.setIcon(QIcon(":/add_grey"));
    _tabCreateAccountButt.setIconSize(QSize(40,40));
    _tabCreateAccountButt.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_2)+
                                        Utility::SET_BORDER_SIZE(0));

    _tabGenerateFileButt.setIcon(QIcon(":/paper_grey"));
    _tabGenerateFileButt.setIconSize(QSize(40,40));
    _tabGenerateFileButt.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_2)+
                                        Utility::SET_BORDER_SIZE(0));

    _tabSettingsButt.setIcon(QIcon(":/settings_grey"));
    _tabSettingsButt.setIconSize(QSize(40,40));
    _tabSettingsButt.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_2)+
                                        Utility::SET_BORDER_SIZE(0));

    _createAccountTab.setVisible(false);
    _generateFileTab.setVisible(false);
    _settingsTab.setVisible(false);

    _menuLayout.setAlignment(Qt::AlignTop);
    _menuLayout.addSpacing(30);
    _menuLayout.addWidget(&_tabAccountButt);
    _menuLayout.addSpacing(30);
    _menuLayout.addWidget(&_tabCreateAccountButt);
    _menuLayout.addSpacing(30);
    _menuLayout.addWidget(&_tabGenerateFileButt);
    _menuLayout.addSpacing(30);
    _menuLayout.addWidget(&_tabSettingsButt);
    _menuLayout.addSpacing(30);

    _menu.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_2));
    _menu.setLayout(&_menuLayout);

    _mainLayout.setContentsMargins(0,0,0,0);
    _mainLayout.addWidget(&_menu);
    _mainLayout.addWidget(&_accountTab);
    _mainLayout.addWidget(&_createAccountTab);
    _mainLayout.addWidget(&_generateFileTab);
    _mainLayout.addWidget(&_settingsTab);

    setLayout(&_mainLayout);

    QObject::connect(&_tabAccountButt,&QPushButton::clicked,this,&MainWindow::showTabAccounts);
    QObject::connect(&_tabCreateAccountButt,&QPushButton::clicked,this,&MainWindow::showTabCreateAccount);
    QObject::connect(&_tabGenerateFileButt,&QPushButton::clicked,this,&MainWindow::showTabGenerateFile);
    QObject::connect(&_tabSettingsButt,&QPushButton::clicked,this,&MainWindow::showTabSettings);
}

void MainWindow::showTabAccounts(){
    _createAccountTab.setVisible(false);
    _generateFileTab.setVisible(false);
    _settingsTab.setVisible(false);
    _accountTab.setVisible(true);
    _tabAccountButt.setIcon(QIcon(":/house"));
    _tabCreateAccountButt.setIcon(QIcon(":/add_grey"));
    _tabGenerateFileButt.setIcon(QIcon(":/paper_grey"));
    _tabSettingsButt.setIcon(QIcon(":/settings_grey"));
}
void MainWindow::showTabCreateAccount(){
    _accountTab.setVisible(false);
    _generateFileTab.setVisible(false);
    _settingsTab.setVisible(false);
    _createAccountTab.setVisible(true);
    _createAccountTab.onTabSelected();
    _tabAccountButt.setIcon(QIcon(":/house_grey"));
    _tabCreateAccountButt.setIcon(QIcon(":/add"));
    _tabGenerateFileButt.setIcon(QIcon(":/paper_grey"));
    _tabSettingsButt.setIcon(QIcon(":/settings_grey"));
}

void MainWindow::showTabGenerateFile(){
    _accountTab.setVisible(false);
    _createAccountTab.setVisible(false);
    _settingsTab.setVisible(false);
    _generateFileTab.setVisible(true);
    _generateFileTab.onTabSelected();
    _tabAccountButt.setIcon(QIcon(":/house_grey"));
    _tabCreateAccountButt.setIcon(QIcon(":/add_grey"));
    _tabGenerateFileButt.setIcon(QIcon(":/paper"));
    _tabSettingsButt.setIcon(QIcon(":/settings_grey"));
}

void MainWindow::showTabSettings(){
    _accountTab.setVisible(false);
    _createAccountTab.setVisible(false);
    _generateFileTab.setVisible(false);
    _settingsTab.setVisible(true);
    _tabAccountButt.setIcon(QIcon(":/house_grey"));
    _tabCreateAccountButt.setIcon(QIcon(":/add_grey"));
    _tabGenerateFileButt.setIcon(QIcon(":/paper_grey"));
    _tabSettingsButt.setIcon(QIcon(":/settings"));
}
