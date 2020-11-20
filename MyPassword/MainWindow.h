#pragma once

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

class AccountTab;
class CreateAccountTab;
class GenerateFileTab;
class SettingsTab;

class MainWindow final : public QWidget
{
    Q_OBJECT
public:
    MainWindow(AccountTab&,CreateAccountTab&,GenerateFileTab&,SettingsTab&);
    MainWindow(MainWindow const&)=delete;
    MainWindow operator=(MainWindow const&)=delete;

private slots:
    void showTabAccounts();
    void showTabCreateAccount();
    void showTabGenerateFile();
    void showTabSettings();

private:
    void setButtNotSelected(QPushButton&);
    void setButtSelected(QPushButton&);
    void reset();
    void hideTabs();
    void makeIconGrey();

    AccountTab& _accountTab;
    CreateAccountTab& _createAccountTab;
    GenerateFileTab& _generateFileTab;
    SettingsTab& _settingsTab;

    QWidget _menu;
    QPushButton _tabAccountButt;
    QPushButton _tabCreateAccountButt;
    QPushButton _tabGenerateFileButt;
    QPushButton _tabSettingsButt;

    QVBoxLayout _menuLayout;
    QHBoxLayout _mainLayout;
};
