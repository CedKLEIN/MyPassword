#include "MainWindow.h"

#include "AccountWindow.h"
#include "NewAccountWindow.h"
#include "Interface/IEncryption.h"
#include "PasswordSecurity.h"
#include "Interface/IDatabase.h"
#include "Utility.h"
#include "Interface/ILog.h"
#include "Interface/IGenerateFile.h"

#include <QDebug>
#include <QObject>

#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QScrollBar>

MainWindow::MainWindow(FacAccount& iFacAccount,
                       FacDisplayAccountWindow& iFacWindowDisplayAccount,
                       NewAccountWindow& iWindowNewAccount,
                       IEncryption& iEncryption,
                       PasswordSecurity& iPasswordSecurity,
                       IDatabase& iDb,
                       ILog& iLog,
                       IGenerateFile& iGenerateFile):
    _facAccount(iFacAccount),
    _facWindowDisplayAccount(iFacWindowDisplayAccount),
    _windowNewAccount(iWindowNewAccount),
    _encryption(iEncryption),
    _passwordSecurity(iPasswordSecurity),
    _db(iDb),
    _log(iLog),
    _generateFile(iGenerateFile)
{
    setFixedSize(SIZE_WINDOW_HORIZONTAL,SIZE_WINDOW_HORIZONTAL);
    move(0,0);
    setStyleSheet(Utility::GET_STYLE_WIDGET()+
                  Utility::GET_STYLE_QLINEEDIT()+
                  Utility::GET_STYLE_QPUSHBUTTON()+
                  Utility::GET_STYLE_QLISTVIEW());

    _windowNewAccount.addListener(this);

    retrieveAccounts();

    _filter.setPlaceholderText("Search...");
    _listAccountsView.setModel(&_listAccountsModel);
    _listAccountsView.verticalScrollBar()->setStyleSheet("QScrollBar:vertical {width: 2px;}");
    _listAccountsView.setEditTriggers(QAbstractItemView::NoEditTriggers);

    _newAccountButton.setIcon(QIcon(":/add"));
    _newAccountButton.setIconSize(QSize(30,30));
    _newAccountButton.setToolTip("Add new account");

    _generateFileButton.setIcon(QIcon(":/paper"));
    _generateFileButton.setIconSize(QSize(30,30));
    _generateFileButton.setToolTip("Generate accounts in text file");

    _layoutH.addWidget(&_newAccountButton);
    _layoutH.addWidget(&_generateFileButton);

    _layoutV.addWidget(&_filter);
    _layoutV.addWidget(&_listAccountsView);
    _layoutV.addLayout(&_layoutH);

    setLayout(&_layoutV);

    QObject::connect(&_filter,&QLineEdit::textChanged,this,&MainWindow::filterChanged);
    QObject::connect(&_newAccountButton,&QPushButton::clicked,this,&MainWindow::openWindowNewAccount);
    QObject::connect(&_generateFileButton,&QPushButton::clicked,this,&MainWindow::generateFile);
    QObject::connect(&_listAccountsView, &QListView::doubleClicked, this,&MainWindow::displayWindowAccount);
}

void MainWindow::onEventClose(){
    retrieveAccounts();
    _windowNewAccount.cleanWindow();
}

void MainWindow::filterChanged(const QString& iText){
    _accountsDataFilter.clear();

    bool opti{false};

    QString textLower{iText.toLower()};
    for(const auto& account: _accountsData){

        QString accountLower{account.toLower()};
        bool match{true};

        if(accountLower.size()>=textLower.size()){
            for(int j{0};j<textLower.size();++j){
                if(accountLower[j] != textLower[j]){
                    match = false;
                    break;
                }
            }
            if(match){
                _accountsDataFilter.push_back(account);
                opti = true;
            }
            if(!match && opti)
                break;
        }
    }
    _listAccountsModel.setStringList(_accountsDataFilter);
}

void MainWindow::retrieveAccounts(){
    _accountsData.clear();
    _facAccount.clear();

    int error{_db.retrieve()};

    if(error != Utility::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(Utility::getMsgError(error).c_str()));
        return;
    }

    for(const auto& account: _facAccount.getAll()){
        _accountsData << account->getName();
    }

    _accountsData.sort(Qt::CaseInsensitive);
    _listAccountsModel.setStringList(_accountsData);
}

void MainWindow::openWindowNewAccount(){
    _windowNewAccount.show();
}

void MainWindow::displayWindowAccount(const QModelIndex& itemSlected)
{
    QString accountName{_listAccountsModel.data(itemSlected).toString()};
    std::shared_ptr<Account> account{_facAccount.get(accountName)};
    AccountWindow* window{_facWindowDisplayAccount.getAccount(account->getName())};
    if(window){
        window->show();
        return;
    }
    _facWindowDisplayAccount.create(account->getName(),
                                    _facAccount,
                                    _encryption,
                                    _passwordSecurity,
                                    _db,
                                    _log);

    window = _facWindowDisplayAccount.getAccount(account->getName());
    window->addListener(this);
    window->show();

    _log.LOG_INFO("Account display : "+account->getName().toStdString());
}

void MainWindow::generateFile(){
    QString pathFile = QFileDialog::getSaveFileName(this,
                                                    tr("Save password file"), "./", tr("Text Files (*.txt)"));

    int error{_generateFile.generate(pathFile.toStdString())};

    if(error != Utility::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(Utility::getMsgError(error).c_str()));
        return;
    }
}

void MainWindow::closeEvent(QCloseEvent*){
    for(const auto& window : _facWindowDisplayAccount.getWindowsDisplay()){
        window->close();
    }

    _windowNewAccount.close();
    QApplication::quit();
}
