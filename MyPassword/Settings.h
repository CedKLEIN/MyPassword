#pragma once

#include "Interface/ISettings.h"

#include <QSettings>

class Settings : public ISettings
{
public:
    Settings();
    Settings(Settings const&)=delete;
    Settings& operator=(Settings const&)=delete;

    QString getLanguage()const override final;
    void setLanguage(const QString&)override final;

    bool isSecurityIconShow()const override final;
    void setIsSecurityIconShow(bool)override final;

    QString getSecurityIconThemes()const override final;
    void setSecurityIconThemes(const QString&)override final;

private:
    QSettings _settings{"CK", "MyPassword"};
    QString _language;
    bool _isSecurityIconShow;
    QString _securityIconThemes;
};
