#pragma once

#include "Account.h"
#include "windowdisplayaccount.h"

#include <QStringList>
#include <QStringListModel>
#include <QListView>
#include <QList>
#include <QAbstractItemView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSqlDatabase>
#include <QWidget>

class IEncryption;
class WindowNewAccount;
class IDatabase;
class Error;
class ILog;
class IGenerateFile;

class WindowListAccount final : public QWidget, public IListener
{
    Q_OBJECT
public:
    WindowListAccount(FacAccount&,
                      WindowNewAccount&,
                      IEncryption&,
                      IDatabase&,
                      Error&,
                      ILog&,
                      IGenerateFile&);
    ~WindowListAccount();
    WindowListAccount(WindowListAccount const&)=delete;
    WindowListAccount& operator=(WindowListAccount const&)=delete;
    void onEventClose() override;
    void closeEvent(QCloseEvent *) override;

public slots:
    void filterChanged(const QString&);
    void retrieveAccounts();
    void openWindowNewAccount();
    void displayWindowAccount(const QModelIndex&);
    void generateFile();

private:
    FacAccount& _facAccount;
    std::vector<WindowDisplayAccount*> _windowDisplayAccount;
    WindowNewAccount& _windowNewAccount;
    IEncryption& _encryption;
    IDatabase& _db;
    Error& _error;
    ILog& _log;
    IGenerateFile& _generateFile;

    QHBoxLayout _layoutH;
    QLineEdit _filter;
    QListView _listAccountsView;
    QStringListModel _listAccountsModel;
    QStringList _accountsData;
    QStringList _accountsDataFilter;
    QVBoxLayout _layoutV;
    QPushButton _newAccountButton;
    QPushButton _generateFileButton;
};
