#include "MainWindow.h"

#include "AccountTab.h"
#include "CreateAccountTab.h"

#include "Utility.h"

#include <QIcon>

MainWindow::MainWindow(AccountTab& iAccountTab,CreateAccountTab& iCreateAccountTab):
    _accountTab(iAccountTab),
    _createAccountTab(iCreateAccountTab)
{
    setMinimumHeight(600);
    setWindowIcon(QIcon(":/security"));
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

    _menu.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_2)+
                        Utility::SET_WIDTH(50));
    _menu.setLayout(&_menuLayout);

    _createAccountTab.setVisible(false);

    _mainLayout.setContentsMargins(0,0,0,0);

    _menuLayout.setAlignment(Qt::AlignTop);
    _menuLayout.addSpacing(30);
    _menuLayout.addWidget(&_tabAccountButt);
    _menuLayout.addSpacing(30);
    _menuLayout.addWidget(&_tabCreateAccountButt);
    _menuLayout.addSpacing(30);

    _mainLayout.addWidget(&_menu);
    _mainLayout.addWidget(&_accountTab);
    _mainLayout.addWidget(&_createAccountTab);


    setLayout(&_mainLayout);

    QObject::connect(&_tabAccountButt,&QPushButton::clicked,this,&MainWindow::showTabAccounts);
    QObject::connect(&_tabCreateAccountButt,&QPushButton::clicked,this,&MainWindow::showTabCreateAccount);

}

void MainWindow::showTabAccounts(){
    _createAccountTab.setVisible(false);
    _accountTab.setVisible(true);
    _tabAccountButt.setIcon(QIcon(":/house"));
    _tabCreateAccountButt.setIcon(QIcon(":/add_grey"));
}
void MainWindow::showTabCreateAccount(){
    _accountTab.setVisible(false);
    _createAccountTab.setVisible(true);
    _createAccountTab.onTabSelected();
    _tabAccountButt.setIcon(QIcon(":/house_grey"));
    _tabCreateAccountButt.setIcon(QIcon(":/add"));
}
