#pragma once

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

class AccountTab;
class CreateAccountTab;
class GenerateFileTab;
class SettingsTab;
class InfoTab;

class MainWindow final : public QWidget
{
    Q_OBJECT
public:
    MainWindow(AccountTab&,CreateAccountTab&,GenerateFileTab&,SettingsTab&,InfoTab&);
    MainWindow(MainWindow const&)=delete;
    MainWindow operator=(MainWindow const&)=delete;

private slots:
    void showTabAccounts();
    void showTabCreateAccount();
    void showTabGenerateFile();
    void showTabSettings();
    void showTabInfo();

private:
    void setButtNotSelected(QPushButton*);
    void setButtSelected(QPushButton*);
    void reset();
    void hideTabs();
    void makeIconGrey();

    AccountTab& _accountTab;
    CreateAccountTab& _createAccountTab;
    GenerateFileTab& _generateFileTab;
    SettingsTab& _settingsTab;
    InfoTab& _infoTab;

    QPushButton* _tabAccountButt{new QPushButton};
    QPushButton* _tabCreateAccountButt{new QPushButton};
    QPushButton* _tabGenerateFileButt{new QPushButton};
    QPushButton* _tabSettingsButt{new QPushButton};
    QPushButton* _tabInfoButt{new QPushButton};
    QWidget* _menu{new QWidget};
    QVBoxLayout* _menuLayout{new QVBoxLayout{_menu}};

    QHBoxLayout* _mainLayout{new QHBoxLayout};
};
