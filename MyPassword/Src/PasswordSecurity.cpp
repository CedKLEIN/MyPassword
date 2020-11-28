#include "PasswordSecurity.h"
#include "Interface/ISettings.h"
#include "Utility.h"

#include <QRegExp>
#include <QString>

PasswordSecurity::PasswordSecurity(ISettings& iISettings):
    _settings(iISettings){}

int PasswordSecurity::getSecurityLevel(const QString& iPwd)const{
        if(iPwd.size()<9)
            return VERY_LOW;

        if(iPwd.size()>19)
            return VERY_HIGH;

    if(isOnlyNumbers(iPwd)){
        if(iPwd.size()<18)
            return VERY_LOW;

        if(iPwd.size()==18)
            return LOW;

        if(iPwd.size()>18)
            return MEDIUM;
    }

    if(isOnlyLettersLower(iPwd) || isOnlyLettersUpper(iPwd)){
        if(iPwd.size()<13)
            return VERY_LOW;

        if(iPwd.size()==13)
            return LOW;

        if(iPwd.size()>13)
            return VERY_HIGH;
    }

    if(isOnlyOthers(iPwd)){
        if(iPwd.size()<14)
            return VERY_LOW;

        if(iPwd.size()==14)
            return LOW;

        if(iPwd.size()==15)
            return HIGH;

        if(iPwd.size()>15)
            return VERY_HIGH;
    }

    if(hasOnlyNumberAndLower(iPwd) || hasOnlyNumberAndUpper(iPwd)){
        if(iPwd.size()<12)
            return VERY_LOW;

        if(iPwd.size()==12)
            return LOW;

        if(iPwd.size()>12)
            return VERY_HIGH;
    }

    if(hasOnlyNumberAndOthers(iPwd)){
        if(iPwd.size()<12)
            return VERY_LOW;

        if(iPwd.size()==12)
            return LOW;

        if(iPwd.size()==13)
            return MEDIUM;

        if(iPwd.size()>13)
            return VERY_HIGH;
    }

    if(hasOnlyLowerAndUpper(iPwd)
            || hasOnlyLowerAndOthers(iPwd)
            || hasOnlyUpperAndOthers(iPwd)){

        if(iPwd.size()<11)
            return VERY_LOW;

        if(iPwd.size()==11)
            return LOW;

        if(iPwd.size()>11)
            return VERY_HIGH;
    }

    if(hasOnlyNumberAndLowerAndUpper(iPwd)
            || hasOnlyNumberAndLowerAndOthers(iPwd)
            || hasOnlyNumberAndUpperAndOthers(iPwd)){

        if(iPwd.size()<10)
            return VERY_LOW;

        if(iPwd.size()==10)
            return LOW;

        if(iPwd.size()==11)
            return HIGH;

        if(iPwd.size()>11)
            return VERY_HIGH;
    }

    if(hasOnlyLowerAndUpperAndOthers(iPwd)
            || hasAll(iPwd)){

        if(iPwd.size()<10)
            return VERY_LOW;

        if(iPwd.size()==10)
            return MEDIUM;

        if(iPwd.size()>10)
            return VERY_HIGH;
    }

    return NONE;
}

QString PasswordSecurity::getIconSeverityLvl(const int iSeverityLvl)const{
    if(_settings.getSecurityIconThemes()==SecurityIconThemes2)
        return getIconTheme2(iSeverityLvl);
    else if(_settings.getSecurityIconThemes()==SecurityIconThemes3)
        return getIconTheme3(iSeverityLvl);
    else {
        return getIconTheme1(iSeverityLvl);
    }
}

QString PasswordSecurity::getIconTheme1(const int iSeverityLvl)const{
    switch(iSeverityLvl){
    case PasswordSecurity::VERY_LOW:
        return QStringLiteral(":/very_low");
    case PasswordSecurity::LOW:
        return QStringLiteral(":/low");
    case PasswordSecurity::MEDIUM:
        return QStringLiteral(":/medium");
    case PasswordSecurity::HIGH:
        return QStringLiteral(":/high");
    case PasswordSecurity::VERY_HIGH:
        return QStringLiteral(":/very_high");
    default:
        return "";
    }
}

QString PasswordSecurity::getIconTheme2(const int iSeverityLvl)const{
    switch(iSeverityLvl){
    case PasswordSecurity::VERY_LOW:
        return QStringLiteral(":/very_low_theme2");
    case PasswordSecurity::LOW:
        return QStringLiteral(":/low_theme2");
    case PasswordSecurity::MEDIUM:
        return QStringLiteral(":/medium_theme2");
    case PasswordSecurity::HIGH:
        return QStringLiteral(":/high_theme2");
    case PasswordSecurity::VERY_HIGH:
        return QStringLiteral(":/very_high_theme2");
    default:
        return "";
    }
}

QString PasswordSecurity::getIconTheme3(const int iSeverityLvl)const{
    switch(iSeverityLvl){
    case PasswordSecurity::VERY_LOW:
        return QStringLiteral(":/very_low_theme3");
    case PasswordSecurity::LOW:
        return QStringLiteral(":/low_theme3");
    case PasswordSecurity::MEDIUM:
        return QStringLiteral(":/medium_theme3");
    case PasswordSecurity::HIGH:
        return QStringLiteral(":/high_theme3");
    case PasswordSecurity::VERY_HIGH:
        return QStringLiteral(":/very_high_theme3");
    default:
        return "";
    }
}

bool PasswordSecurity::hasAll(const QString& iPwd)const{
    return hasOneNumbers(iPwd)
            && hasOneLetterLower(iPwd)
            && hasOneLetterUpper(iPwd)
            && hasOneOthers(iPwd);
}

bool PasswordSecurity::hasOnlyNumberAndLowerAndUpper(const QString& iPwd)const{
    return hasOneNumbers(iPwd)
            && hasOneLetterLower(iPwd)
            && hasOneLetterUpper(iPwd)
            && !hasOneOthers(iPwd);
}

bool PasswordSecurity::hasOnlyNumberAndLowerAndOthers(const QString& iPwd)const{
    return hasOneNumbers(iPwd)
            && hasOneLetterLower(iPwd)
            && !hasOneLetterUpper(iPwd)
            && hasOneOthers(iPwd);
}

bool PasswordSecurity::hasOnlyNumberAndUpperAndOthers(const QString& iPwd)const{
    return hasOneNumbers(iPwd)
            && !hasOneLetterLower(iPwd)
            && hasOneLetterUpper(iPwd)
            && hasOneOthers(iPwd);
}

bool PasswordSecurity::hasOnlyLowerAndUpperAndOthers(const QString& iPwd)const{
    return !hasOneNumbers(iPwd)
            && hasOneLetterLower(iPwd)
            && hasOneLetterUpper(iPwd)
            && hasOneOthers(iPwd);
}

bool PasswordSecurity::hasOnlyNumberAndLower(const QString& iPwd)const{
    return hasOneNumbers(iPwd)
            && hasOneLetterLower(iPwd)
            && !hasOneLetterUpper(iPwd)
            && !hasOneOthers(iPwd);
}

bool PasswordSecurity::hasOnlyNumberAndUpper(const QString& iPwd)const{
    return hasOneNumbers(iPwd)
            && !hasOneLetterLower(iPwd)
            && hasOneLetterUpper(iPwd)
            && !hasOneOthers(iPwd);
}

bool PasswordSecurity::hasOnlyNumberAndOthers(const QString& iPwd)const{
    return hasOneNumbers(iPwd)
            && !hasOneLetterLower(iPwd)
            && !hasOneLetterUpper(iPwd)
            && hasOneOthers(iPwd);
}

bool PasswordSecurity::hasOnlyLowerAndUpper(const QString& iPwd)const{
    return !hasOneNumbers(iPwd)
            && hasOneLetterLower(iPwd)
            && hasOneLetterUpper(iPwd)
            && !hasOneOthers(iPwd);
}

bool PasswordSecurity::hasOnlyLowerAndOthers(const QString& iPwd)const{
    return !hasOneNumbers(iPwd)
            && hasOneLetterLower(iPwd)
            && !hasOneLetterUpper(iPwd)
            && hasOneOthers(iPwd);
}

bool PasswordSecurity::hasOnlyUpperAndOthers(const QString& iPwd)const{
    return !hasOneNumbers(iPwd)
            && !hasOneLetterLower(iPwd)
            && hasOneLetterUpper(iPwd)
            && hasOneOthers(iPwd);
}

bool PasswordSecurity::hasOneNumbers(const QString &iPwd)const{
    for(const auto& aChar : iPwd){
        if(QChar(aChar).isNumber())
            return true;
    }
    return false;
}

bool PasswordSecurity::hasOneLetterLower(const QString &iPwd)const{
    for(const auto& aChar : iPwd){
        if(QChar(aChar).isLower())
            return true;
    }
    return false;
}

bool PasswordSecurity::hasOneLetterUpper(const QString &iPwd)const{
    for(const auto& aChar : iPwd){
        if(QChar(aChar).isUpper())
            return true;
    }
    return false;
}

bool PasswordSecurity::hasOneOthers(const QString &iPwd)const{

    for(const auto& aChar : iPwd){
        if(!QChar(aChar).isUpper() && !QChar(aChar).isLetter() && !QChar(aChar).isNumber())
            return true;
    }
    return false;
}

bool PasswordSecurity::isOnlyNumbers(const QString &iPwd)const{
    return QRegExp(QStringLiteral("[0-9]*")).exactMatch(iPwd);
}

bool PasswordSecurity::isOnlyLettersLower(const QString &iPwd)const{
    return QRegExp(QStringLiteral("[a-z]*")).exactMatch(iPwd);
}

bool PasswordSecurity::isOnlyLettersUpper(const QString &iPwd)const{
    return QRegExp(QStringLiteral("[A-Z]*")).exactMatch(iPwd);
}

bool PasswordSecurity::isOnlyOthers(const QString &iPwd)const{
    return !(hasOneNumbers(iPwd) || hasOneLetterLower(iPwd) || hasOneLetterUpper(iPwd));
}
