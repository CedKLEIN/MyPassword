#pragma once

#include "Interface/IListener.h"

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>

class FacAccount;
class IDatabase;
class ISettings;

class SettingsTab final : public QWidget
{
    Q_OBJECT
public:
    SettingsTab(FacAccount&, IDatabase&, ISettings&);

    void addListener(IListener* iListener){
        _listeners.push_back(iListener);
    }

private slots:
    void reset();
    void languageChange(int);
    void securityIconShowChange(int);

private:
    void setComboBoxLanguage();

    void fireRefreshAccounts(){
        for(const auto& listener : _listeners){
            listener->onEventClose();
        }
    }

    FacAccount& _facAccount;
    IDatabase& _database;
    ISettings& _settings;

    QLabel _titleLabel{tr("Settings")};
    QHBoxLayout _titleLayout;

    std::vector<IListener*> _listeners;

    QLabel _languageLabel{tr("Language:")};
    QComboBox _languageComboBox;

    QLabel _securityLabel{tr("Password security:")};
    QCheckBox _securityIconShowCheckBox{tr("Display icon security level in account view")};

    QLabel _resetLabel{tr("Reset:")};
    QPushButton _resetButt{tr("Delete all accounts")};

    QVBoxLayout _mainLayout;
};
