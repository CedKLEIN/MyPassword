#pragma once

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

class AccountTab;
class CreateAccountTab;
class GenerateFileTab;

class MainWindow final : public QWidget
{
    Q_OBJECT
public:
    MainWindow(AccountTab&,CreateAccountTab&,GenerateFileTab&);
    MainWindow(MainWindow const&)=delete;
    MainWindow operator=(MainWindow const&)=delete;

private slots:
    void showTabAccounts();
    void showTabCreateAccount();
    void showTabGenerateFile();

private:
    AccountTab& _accountTab;
    CreateAccountTab& _createAccountTab;
    GenerateFileTab& _generateFileTab;

    QWidget _menu;
    QPushButton _tabAccountButt;
    QPushButton _tabCreateAccountButt;
    QPushButton _tabGenerateFileButt;

    QVBoxLayout _menuLayout;
    QHBoxLayout _mainLayout;
};
