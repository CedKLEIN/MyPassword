#pragma once

#include <QString>

#include <memory>

class Account final
{
friend class FacAccount;

public:
    QString getName() const;
    QString getLogin() const;
    QString getPassword() const;
    QString getDetails() const;
    int getSeverityLvl() const;

private:
    Account(const QString&,
            const QString&,
            const QString&,
            const QString&,
            const int);
    QString _name;
    QString _login;
    QString _password;
    QString _details;
    int _severityLvl;
};

class FacAccount{
public:
    FacAccount()=default;
    FacAccount(FacAccount const&)=delete;
    FacAccount& operator=(FacAccount const&)=delete;
    ~FacAccount(){
        clear();
    }

    void create(const QString& iName,
                const QString& iLogin,
                const QString& iPassword,
                const QString& iDetails,
                const int iSeverityLvl){
        _vectAccount.emplace_back(new Account(iName,iLogin,iPassword,iDetails,iSeverityLvl));
    }

    std::shared_ptr<Account> get(const QString& iName){
        for(const auto& account : _vectAccount){
            if (account->getName() == iName){
                return account;
            }
        }
        return nullptr;
    }

    std::vector<std::shared_ptr<Account>> getAll(){
        return _vectAccount;
    }

    void clear(){
        _vectAccount.clear();
    }
private:
    std::vector<std::shared_ptr<Account>> _vectAccount;
};
