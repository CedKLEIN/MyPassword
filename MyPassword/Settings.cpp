#include "Settings.h"

#include <QDebug>

static const QString settings_language{QStringLiteral("Language")};
static const QString settings_isSecurityIconShow{QStringLiteral("isSecurityIconShow")};

Settings::Settings():
    _language{_settings.value(settings_language,QStringLiteral("english")).toString()},
    _isSecurityIconShow{_settings.value(settings_isSecurityIconShow,true).toBool()}
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
