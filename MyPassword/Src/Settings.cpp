#include "Settings.h"

static const QString settings_language{QStringLiteral("Language")};
static const QString settings_isSecurityIconShow{QStringLiteral("isSecurityIconShow")};
static const QString settings_SecurityIconThemes{QStringLiteral("SecurityIconThemes")};

Settings::Settings():
    _language{_settings.value(settings_language,QStringLiteral("english")).toString()},
    _isSecurityIconShow{_settings.value(settings_isSecurityIconShow,true).toBool()},
    _securityIconThemes{_settings.value(settings_SecurityIconThemes,QStringLiteral("theme1")).toString()}
{}

QString Settings::getLanguage()const{
    return _language;
}

void Settings::setLanguage(const QString& iLanguage){
    _settings.setValue(settings_language,iLanguage);
    _language=iLanguage;
}

bool Settings::isSecurityIconShow()const{
    return _isSecurityIconShow;
}

void Settings::setIsSecurityIconShow(bool iIsSecurityIconShow){
    _settings.setValue(settings_isSecurityIconShow,iIsSecurityIconShow);
    _isSecurityIconShow=iIsSecurityIconShow;
}

QString Settings::getSecurityIconThemes()const{
    return _securityIconThemes;
}

void Settings::setSecurityIconThemes(const QString& iSecurityIconThemes){
    _settings.setValue(settings_SecurityIconThemes,iSecurityIconThemes);
    _securityIconThemes=iSecurityIconThemes;
}
