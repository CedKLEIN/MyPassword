#include "AccountTab.h"

#include "AccountWindow.h"
#include "CreateAccountTab.h"
#include "SettingsTab.h"
#include "Interface/IPasswordSecurity.h"
#include "Interface/IDatabase.h"
#include "Interface/ILog.h"
#include "Interface/ISettings.h"
#include "Utility.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QScrollBar>

AccountTab::AccountTab(FacAccount& iFacAccount,
                       AccountWindow& iAccountWindow,
                       CreateAccountTab& iCreateAccountTab,
                       IPasswordSecurity& iPasswordSecurity,
                       IDatabase& iDb,
                       ILog& iLog,
                       SettingsTab& iSettingsTab,
                       ISettings& iISettings):
    _facAccount(iFacAccount),
    _accountWindow(iAccountWindow),
    _createAccountTab(iCreateAccountTab),
    _passwordSecurity(iPasswordSecurity),
    _db(iDb),
    _log(iLog),
    _settingsTab(iSettingsTab),
    _settings(iISettings)
{
    setMinimumWidth(SIZE_WINDOW_HORIZONTAL);
    setStyleSheet(Utility::GET_STYLE_WIDGET()+
                  Utility::GET_STYLE_QLINEEDIT()+
                  Utility::GET_STYLE_QPUSHBUTTON()+
                  Utility::GET_STYLE_QLISTVIEW());

    _createAccountTab.addListener(this);
    _accountWindow.addListener(this);
    _settingsTab.addUpdateAccountListener(this);
    _accountWindowLayout.addWidget(&_accountWindow);
    _accountWindowWidget.setLayout(&_accountWindowLayout);
    _accountWindowWidget.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_DARK_0));
    _accountWindowWidget.hide();

    retrieveAccounts();

    _filterLineEdit.setPlaceholderText(tr("Search..."));
    _filterLineEdit.setMaxLength(TEXT_NAME_LENGTH);
    _accountView.setModel(&_accountModel);
    _accountView.verticalScrollBar()->setStyleSheet(QStringLiteral("QScrollBar:vertical {width: 2px;}"));
    _accountView.setEditTriggers(QAbstractItemView::NoEditTriggers);

    _viewAndDisplayAccountLayout.addWidget(&_accountView);
    _viewAndDisplayAccountLayout.addWidget(&_accountWindowWidget);
    _mainLayout.addWidget(&_filterLineEdit);
    _mainLayout.addLayout(&_viewAndDisplayAccountLayout);

    setLayout(&_mainLayout);

    QObject::connect(&_filterLineEdit,&QLineEdit::textChanged,this,&AccountTab::filterChanged);
    QObject::connect(_accountView.selectionModel(), &QItemSelectionModel::selectionChanged, this,&AccountTab::displayWindowAccount);
}

void AccountTab::onEventUpdateAccount(){
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
    _accountWindow.hide();

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
    if(_settings.isSecurityIconShow()){
        for(const auto& account: iDataList){
            QStandardItem *item = new QStandardItem(QIcon(_passwordSecurity.getIconSeverityLvl(_facAccount.get(account)->getSeverityLvl())),account);
            _accountModel.appendRow(item);
        }
    }else {
        for(const auto& account: iDataList){
            QStandardItem *item = new QStandardItem(account);
            _accountModel.appendRow(item);
        }
    }
}

void AccountTab::displayWindowAccount(const QItemSelection& iItemSelected, const QItemSelection&)
{
    QString accountName{_accountModel.itemData(iItemSelected.indexes().front()).value(0).toString()};
    _accountWindow.showWindow(accountName);
    _accountWindow.setVisible(true);
    _accountWindowWidget.setVisible(true);
    _log.LOG_INFO("Account display : "+accountName.toStdString());
}
