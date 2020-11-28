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

namespace Testable{
class Settings : public ISettings
{
public:
    Settings(){};
    Settings(Settings const&)=delete;
    Settings& operator=(Settings const&)=delete;

    QString getLanguage()const override final{return _language;}
    void setLanguage(const QString& in)override final{_language=in;}

    bool isSecurityIconShow()const override final{return _isSecurityIconShow;}
    void setIsSecurityIconShow(bool in)override final{_isSecurityIconShow=in;}

    QString getSecurityIconThemes()const override final{return _securityIconThemes;}
    void setSecurityIconThemes(const QString& in)override final{_securityIconThemes=in;}

private:
    QString _language;
    bool _isSecurityIconShow;
    QString _securityIconThemes;
};
}
