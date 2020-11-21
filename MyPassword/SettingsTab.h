#pragma once

#include "Interface/IListener.h"

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>

class FacAccount;
class IDatabase;

class SettingsTab final : public QWidget
{
    Q_OBJECT
public:
    SettingsTab(FacAccount&,IDatabase&);

    void addListener(IListener* iListener){
        _listeners.push_back(iListener);
    }

private slots:
    void reset();

private:
    void fireRefreshAccounts(){
        for(const auto& listener : _listeners){
            listener->onEventClose();
        }
    }

    FacAccount& _facAccount;
    IDatabase& _database;
    QLabel _titleLabel{tr("Settings")};
    QHBoxLayout _titleLayout;

    std::vector<IListener*> _listeners;

    QLabel _languageLabel{tr("Language:")};
    QComboBox _languageComboBox;

    QLabel _resetLabel{tr("Reset:")};
    QPushButton _resetButt{tr("Delete all accounts")};

    QVBoxLayout _mainLayout;
};
