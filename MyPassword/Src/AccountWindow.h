#pragma once

#include "Account.h"
#include "Interface/IUpdateAccountListener.h"

#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QIcon>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <memory>

class IEncryption;
class IPasswordSecurity;
class IDatabase;
class ILog;

class AccountWindow : public QWidget
{
    Q_OBJECT

public:
    AccountWindow(FacAccount&,
                  IEncryption&,
                  IPasswordSecurity&,
                  IDatabase&,
                  ILog&);
    AccountWindow(AccountWindow const&)=delete;
    AccountWindow& operator=(AccountWindow const&)=delete;

    void addListener(IUpdateAccountListener* iListener){
        _listeners.push_back(iListener);
    }

    QString getAccountName() const;
    void showWindow(const QString&);

private slots:
    void checkPasswordSecurity(const QString&);
    void itemChangedDetails();
    bool saveModifLogin();
    bool saveModifDetails();
    bool saveModifPassword();
    void checkPassword();
    void viewPassword();
    void viewTestPwd();
    void deleteAccount();

private:
    void fireRefreshAccounts(){
        for(const auto& listener : _listeners){
            listener->onEventUpdateAccount();
        }
    }

    FacAccount& _facAccount;
    IEncryption& _encryption;
    IPasswordSecurity& _passwordSecurity;
    IDatabase& _db;
    ILog& _log;

    std::vector<IUpdateAccountListener*> _listeners;

    QPushButton* _closeButt{new QPushButton};
    QHBoxLayout* _closeLayout{new QHBoxLayout};

    QLabel* _nameLabel{new QLabel};

    QLabel* _loginLabel{new QLabel{tr("Login : ")}};
    QPushButton* _loginSavedButt{new QPushButton{tr(" Modification saved")}};
    QHBoxLayout* _loginLabelsLayout{new QHBoxLayout};
    QLineEdit* _loginLineEdit{new QLineEdit};
    QPushButton* _loginButt{new QPushButton{tr("Change login")}};

    QLabel* _detailsLabel{new QLabel{tr("Details : ")}};
    QPushButton* _detailsSavedButt{new QPushButton{tr(" Modification saved")}};
    QHBoxLayout* _detailsLabelsLayout{new QHBoxLayout};
    QTextEdit* _detailsTextEdit{new QTextEdit};
    QPushButton* _detailsButt{new QPushButton{tr("Change details")}};

    QLabel* _testLabel{new QLabel{tr(" Test your password :")}};
    QLineEdit* _testLineEdit{new QLineEdit};
    QPushButton* _testButt{new QPushButton{tr("Check")}};
    QPushButton* _testViewButt{new QPushButton};
    QHBoxLayout* _testLayout{new QHBoxLayout};
    bool isTestView{false};

    QLabel* _pwdLabel{new QLabel{tr(" Change your password :")}};
    QPushButton* _pwdSavedButt{new QPushButton{tr(" Modification saved")}};
    QHBoxLayout* _pwdLabelsLayout{new QHBoxLayout};
    QLineEdit* _pwdLineEdit{new QLineEdit};
    QPushButton* _pwdButt{new QPushButton{tr("Change password")}};
    QPushButton* _pwdViewButt{new QPushButton};
    QPushButton* _pwdSecurityButt{new QPushButton};
    QHBoxLayout* _pwdLayout{new QHBoxLayout};
    bool isPassordView{false};
    int _pwdSecurityLvl{0};

    QPushButton* _deleteAccountButt{new QPushButton{tr(" Delete account")}};

    QVBoxLayout* _mainLayout{new QVBoxLayout};
};
