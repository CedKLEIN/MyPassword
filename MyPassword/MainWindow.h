#pragma once

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

class AccountTab;
class CreateAccountTab;

class MainWindow final : public QWidget
{
    Q_OBJECT
public:
    MainWindow(AccountTab&, CreateAccountTab&);
    MainWindow(MainWindow const&)=delete;
    MainWindow operator=(MainWindow const&)=delete;

private slots:
    void showTabAccounts();
    void showTabCreateAccount();

private:
    AccountTab& _accountTab;
    CreateAccountTab& _createAccountTab;

    QWidget _menu;
    QPushButton _tabAccountButt;
    QPushButton _tabCreateAccountButt;

    QVBoxLayout _menuLayout;
    QHBoxLayout _mainLayout;
};
