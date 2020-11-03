#include "windowlistaccount.h"
#include "windowdisplayaccount.h"
#include "windownewaccount.h"
#include "Interface/IEncryption.h"
#include "Interface/IDatabase.h"
#include "Error.h"
#include "Interface/ILog.h"
#include "Interface/IGenerateFile.h"

#include <QDebug>
#include <QObject>
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QScrollBar>

WindowListAccount::WindowListAccount(FacAccount& iFacAccount,
                                     WindowNewAccount& iWindowNewAccount,
                                     IEncryption& iEncryption,
                                     IDatabase& iDb,
                                     Error& iError,
                                     ILog& iLog,
                                     IGenerateFile& iGenerateFile):
    _facAccount(iFacAccount),
    _windowNewAccount(iWindowNewAccount),
    _encryption(iEncryption),
    _db(iDb),
    _error(iError),
    _log(iLog),
    _generateFile(iGenerateFile)
{
    setFixedSize(500,500);
    setStyleSheet("QWidget{background-color: #455A64;color: white;}"
                  "QLineEdit{background-color: #CFD8DC;color:#455A64;border:0px;height:30px}");
    _listAccountsView.verticalScrollBar()->setStyleSheet("QScrollBar:vertical {width: 2px;}");

    _windowNewAccount.addListener(this);

    retrieveAccounts();
    _listAccountsView.setModel(&_listAccountsModel);
    _listAccountsView.setEditTriggers(QAbstractItemView::NoEditTriggers);
    _listAccountsView.setStyleSheet("background-color: #455A64;font:bold;border:0px;color:white;");

    _newAccountButton.setStyleSheet("background-color: #CFD8DC;");
    _newAccountButton.setIcon(QIcon(":/add"));
    _newAccountButton.setIconSize(QSize(30,30));
    _newAccountButton.setToolTip("Add new account");

    _generateFileButton.setStyleSheet("background-color: #CFD8DC;");
    _generateFileButton.setIcon(QIcon(":/paper"));
    _generateFileButton.setIconSize(QSize(30,30));
    _generateFileButton.setToolTip("Generate accounts in text file");

    _layoutH.addWidget(&_newAccountButton);
    _layoutH.addWidget(&_generateFileButton);

    _filter.setPlaceholderText("Search...");

    _layoutV.addWidget(&_filter);
    _layoutV.addWidget(&_listAccountsView);
    _layoutV.addLayout(&_layoutH);

    setLayout(&_layoutV);

    QObject::connect(&_filter, SIGNAL(textChanged(const QString&)), this, SLOT(filterChanged(const QString&)));
    QObject::connect(&_newAccountButton, SIGNAL(clicked()), this, SLOT(openWindowNewAccount()));
    QObject::connect(&_generateFileButton, SIGNAL(clicked()), this, SLOT(generateFile()));
    QObject::connect(&_listAccountsView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(displayWindowAccount(const QModelIndex&)));
}

WindowListAccount::~WindowListAccount(){
    for(const auto& window : _windowDisplayAccount){
        delete window;
    }
}

void WindowListAccount::onEventClose(){
    retrieveAccounts();
}

void WindowListAccount::filterChanged(const QString& iText){
    _accountsDataFilter.clear();

    QString textLower{iText.toLower()};
    for(const auto& account: _accountsData){

        QString accountLower{account.toLower()};
        bool match{true};
        bool opti{false};

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
                return;
        }
    }
    _listAccountsModel.setStringList(_accountsDataFilter);
}

void WindowListAccount::retrieveAccounts(){
    _accountsData.clear();
    _facAccount.clear();

    int error{_db.retrieve()};

    if(error != Error::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(_error.getMsgError(error).c_str()));
        return;
    }

    for(const auto& account: _facAccount.getAll()){
        _accountsData << account->getName();
    }

    _accountsData.sort(Qt::CaseInsensitive);
    _listAccountsModel.setStringList(_accountsData);
}

void WindowListAccount::openWindowNewAccount(){
    _windowNewAccount.cleanWindow();
    _windowNewAccount.show();
}

void WindowListAccount::displayWindowAccount(const QModelIndex& itemSlected)
{
    QString accountName{_listAccountsModel.data(itemSlected).toString()};
    std::shared_ptr<Account> account{_facAccount.get(accountName)};

    for(const auto& window:_windowDisplayAccount){
        if(window->getAccount() == account->getName()){
            window->show();
            return;
        }
    }
    WindowDisplayAccount* newWindow = new WindowDisplayAccount(account->getName(),
                                                               _facAccount,
                                                               _encryption,
                                                               _db,
                                                               _error,
                                                               _log);
    _windowDisplayAccount.push_back(newWindow);
    newWindow->addListener(this);
    newWindow->show();

    _log.LOG_INFO("Account display : "+account->getName().toStdString());
}

void WindowListAccount::generateFile(){
    QString pathFile = QFileDialog::getSaveFileName(this,
        tr("Save password file"), "./", tr("Text Files (*.txt)"));

    int error{_generateFile.generate(pathFile.toStdString())};

    if(error != Error::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(_error.getMsgError(error).c_str()));
        return;
    }
}

void WindowListAccount::closeEvent(QCloseEvent* event){
    for(const auto& window : _windowDisplayAccount){
        if (window->isModifing){
            event->ignore();
            QString msg = "Please cancel modification of "+window->getAccount()+" before quit";
            QMessageBox::warning(this,
                                 tr("Modification on-going"),
                                 tr(msg.toStdString().c_str()));
            return;
        }
        window->close();
    }

    _windowNewAccount.close();
    QApplication::quit();
}
