#include "MainWindow.h"

#include "AccountWindow.h"
#include "NewAccountWindow.h"
#include "SecurityLevelWindow.h"
#include "Interface/IEncryption.h"
#include "Interface/IPasswordSecurity.h"
#include "Interface/IDatabase.h"
#include "Utility.h"
#include "Interface/ILog.h"
#include "Interface/IGenerateFile.h"

#include <QDebug>

#include <QMessageBox>
#include <QFileDialog>
#include <QScrollBar>

MainWindow::MainWindow(FacAccount& iFacAccount,
                       AccountWindow& iAccountWindow,
                       NewAccountWindow& iWindowNewAccount,
                       IEncryption& iEncryption,
                       IPasswordSecurity& iPasswordSecurity,
                       SecurityLevelWindow& iSecurityLevelWindow,
                       IDatabase& iDb,
                       ILog& iLog,
                       IGenerateFile& iGenerateFile):
    _facAccount(iFacAccount),
    _accountWindow(iAccountWindow),
    _windowNewAccount(iWindowNewAccount),
    _encryption(iEncryption),
    _passwordSecurity(iPasswordSecurity),
    _securityLevelWindow(iSecurityLevelWindow),
    _db(iDb),
    _log(iLog),
    _generateFile(iGenerateFile)
{
    setMinimumHeight(600);
    setFixedWidth(SIZE_WINDOW_HORIZONTAL);
    move(0,0);
    setWindowIcon(QIcon(":/security"));
    setStyleSheet(Utility::GET_STYLE_WIDGET()+
                  Utility::GET_STYLE_QLINEEDIT()+
                  Utility::GET_STYLE_QPUSHBUTTON()+
                  Utility::GET_STYLE_QLISTVIEW());

    _windowNewAccount.addListener(this);
    _accountWindow.addListener(this);
    _accountWindow.hide();

    retrieveAccounts();

    _filterLineEdit.setPlaceholderText("Search...");
    _accountView.setModel(&_accountModel);
    _accountView.verticalScrollBar()->setStyleSheet("QScrollBar:vertical {width: 2px;}");
    _accountView.setEditTriggers(QAbstractItemView::NoEditTriggers);

    _newAccountButt.setIcon(QIcon(":/add"));
    _newAccountButt.setIconSize(QSize(30,30));
    _newAccountButt.setToolTip("Add new account");

    _generateFileButt.setIcon(QIcon(":/paper"));
    _generateFileButt.setIconSize(QSize(30,30));
    _generateFileButt.setToolTip("Generate accounts in text file");

    _deleteAccountButt.setIcon(QIcon(":/delete"));
    _deleteAccountButt.setIconSize(QSize(30,30));
    _deleteAccountButt.setToolTip("Delete account selected");
    _deleteAccountButt.setEnabled(false);

    _buttLayout.addWidget(&_newAccountButt);
    _buttLayout.addWidget(&_generateFileButt);
    _buttLayout.addWidget(&_deleteAccountButt);

    _mainLayout.addWidget(&_filterLineEdit);
    _viewAndDisplayAccountLayout.addWidget(&_accountView);
    _viewAndDisplayAccountLayout.addWidget(&_accountWindow);
    _mainLayout.addLayout(&_viewAndDisplayAccountLayout);
    _mainLayout.addLayout(&_buttLayout);

    setLayout(&_mainLayout);

    QObject::connect(&_filterLineEdit,&QLineEdit::textChanged,this,&MainWindow::filterChanged);
    QObject::connect(&_newAccountButt,&QPushButton::clicked,&_windowNewAccount,&NewAccountWindow::show);
    QObject::connect(&_generateFileButt,&QPushButton::clicked,this,&MainWindow::generateFile);
    QObject::connect(&_deleteAccountButt,&QPushButton::clicked,this,&MainWindow::deleteAccount);
    QObject::connect(_accountView.selectionModel(), &QItemSelectionModel::selectionChanged, this,&MainWindow::displayWindowAccount);
}


MainWindow::~MainWindow(){
    _accountModel.clear();
}
void MainWindow::onEventClose(){
    retrieveAccounts();
    _windowNewAccount.clearWindow();
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
    setModelFromDataList(_accountsDataFilter);
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

    setModelFromDataList(_accountsData);
}

void MainWindow::setModelFromDataList(const QStringList& iDataList){
    _accountModel.clear();
    for(const auto& account: iDataList){
        QStandardItem *item = new QStandardItem(QIcon(_passwordSecurity.getIconSeverityLvl(_facAccount.get(account)->getSeverityLvl())),account);
        _accountModel.appendRow(item);
    }
}

void MainWindow::displayWindowAccount(const QItemSelection& iItemSelected, const QItemSelection&)
{
    _deleteAccountButt.setEnabled(true);
    QString accountName{_accountModel.itemData(iItemSelected.indexes().front()).value(0).toString()};
    _accountWindow.showWindow(accountName);
    _log.LOG_INFO("Account display : "+accountName.toStdString());
}

void MainWindow::generateFile(){
    QString pathFile{QFileDialog::getSaveFileName(this,
                                                  tr("Save password file"), "./", tr("Text Files (*.txt)"))};

    int error{_generateFile.generate(pathFile.toStdString())};

    if(error != Utility::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(Utility::getMsgError(error).c_str()));
        return;
    }
}

void MainWindow::deleteAccount(){
    const QString& currentAccount{_accountModel.itemData(_accountView.selectionModel()->currentIndex()).value(0).toString()};

    int answer{QMessageBox::warning(this, tr("Delete account"),
                                    tr("Do you really want to delete your account "+currentAccount.toLocal8Bit()+"?"),
                                    QMessageBox::Yes | QMessageBox::No)};

    if(answer != QMessageBox::Yes)
        return;

    int error{_db.remove(currentAccount)};

    if(error != Utility::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(Utility::getMsgError(error).c_str()));
        return;
    }

    _log.LOG_INFO("Account deleted : "+currentAccount.toStdString());

    retrieveAccounts();
}

void MainWindow::closeEvent(QCloseEvent*){
    _windowNewAccount.close();
    _accountWindow.close();
}
