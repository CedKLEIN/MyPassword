#include "AccountTab.h"

#include "AccountWindow.h"
#include "CreateAccountTab.h"
#include "Interface/IPasswordSecurity.h"
#include "Interface/IDatabase.h"
#include "Utility.h"
#include "Interface/ILog.h"
#include "Interface/IGenerateFile.h"

#include <QDebug>

#include <QMessageBox>
#include <QFileDialog>
#include <QScrollBar>

AccountTab::AccountTab(FacAccount& iFacAccount,
                       AccountWindow& iAccountWindow,
                       CreateAccountTab& iCreateAccountTab,
                       IPasswordSecurity& iPasswordSecurity,
                       IDatabase& iDb,
                       ILog& iLog,
                       IGenerateFile& iGenerateFile):
    _facAccount(iFacAccount),
    _accountWindow(iAccountWindow),
    _createAccountTab(iCreateAccountTab),
    _passwordSecurity(iPasswordSecurity),
    _db(iDb),
    _log(iLog),
    _generateFile(iGenerateFile)
{
    setFixedWidth(SIZE_WINDOW_HORIZONTAL);
    setStyleSheet(Utility::GET_STYLE_WIDGET()+
                  Utility::GET_STYLE_QLINEEDIT()+
                  Utility::GET_STYLE_QPUSHBUTTON()+
                  Utility::GET_STYLE_QLISTVIEW());

    _createAccountTab.addListener(this);
    _accountWindow.addListener(this);
    _accountWindow.hide();

    retrieveAccounts();

    _filterLineEdit.setPlaceholderText("Search...");
    _filterLineEdit.setMaxLength(TEXT_NAME_LENGTH);
    _accountView.setModel(&_accountModel);
    _accountView.verticalScrollBar()->setStyleSheet("QScrollBar:vertical {width: 2px;}");
    _accountView.setEditTriggers(QAbstractItemView::NoEditTriggers);

    _generateFileButt.setIcon(QIcon(":/paper"));
    _generateFileButt.setIconSize(QSize(30,30));
    _generateFileButt.setToolTip("Generate accounts in text file");

    _deleteAccountButt.setIcon(QIcon(":/delete"));
    _deleteAccountButt.setIconSize(QSize(30,30));
    _deleteAccountButt.setToolTip("Delete account selected");
    _deleteAccountButt.setEnabled(false);

    _buttLayout.addWidget(&_generateFileButt);
    _buttLayout.addWidget(&_deleteAccountButt);

    _viewAndDisplayAccountLayout.addWidget(&_accountView);
    _viewAndDisplayAccountLayout.addWidget(&_accountWindow);
    _mainLayout.addWidget(&_filterLineEdit);
    _mainLayout.addLayout(&_viewAndDisplayAccountLayout);
    _mainLayout.addLayout(&_buttLayout);

    setLayout(&_mainLayout);

    QObject::connect(&_filterLineEdit,&QLineEdit::textChanged,this,&AccountTab::filterChanged);
    QObject::connect(&_generateFileButt,&QPushButton::clicked,this,&AccountTab::generateFile);
    QObject::connect(&_deleteAccountButt,&QPushButton::clicked,this,&AccountTab::deleteAccount);
    QObject::connect(_accountView.selectionModel(), &QItemSelectionModel::selectionChanged, this,&AccountTab::displayWindowAccount);
}


AccountTab::~AccountTab(){
    _accountModel.clear();
}
void AccountTab::onEventClose(){
    retrieveAccounts();
}

void AccountTab::filterChanged(const QString& iText){
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

void AccountTab::retrieveAccounts(){
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

void AccountTab::setModelFromDataList(const QStringList& iDataList){
    _accountModel.clear();
    for(const auto& account: iDataList){
        QStandardItem *item = new QStandardItem(QIcon(_passwordSecurity.getIconSeverityLvl(_facAccount.get(account)->getSeverityLvl())),account);
        _accountModel.appendRow(item);
    }
}

void AccountTab::displayWindowAccount(const QItemSelection& iItemSelected, const QItemSelection&)
{
    _deleteAccountButt.setEnabled(true);
    QString accountName{_accountModel.itemData(iItemSelected.indexes().front()).value(0).toString()};
    _accountWindow.showWindow(accountName);
    _log.LOG_INFO("Account display : "+accountName.toStdString());
}

void AccountTab::generateFile(){
    QString pathFile{QFileDialog::getSaveFileName(this,
                                                  tr("Save password file"), "./", tr("Text Files (*.txt)"))};

    int error{_generateFile.generate(pathFile.toStdString())};

    if(error != Utility::ERROR::no_error){
        QMessageBox::warning(this,tr("Warning"),
                             tr(Utility::getMsgError(error).c_str()));
        return;
    }
}

void AccountTab::deleteAccount(){
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
