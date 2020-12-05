#pragma once

#include <string>
#include <QString>
#include <QSize>

static const QString COLOR_WHITE{QStringLiteral("#FFFFFF")};
static const QString COLOR_RED{QStringLiteral("#D32F2F")};
static const QString COLOR_ORANGE{QStringLiteral("#FF9800")};
static const QString COLOR_GREEN{QStringLiteral("#388E3C")};
static const QString COLOR_GREEN_LIGHT{QStringLiteral("#8BC34A")};
static const QString COLOR_BLUE{QStringLiteral("#1177BB")};
static const QString COLOR_BLUE_LIGHT{QStringLiteral("#7BDCFE")};
static const QString COLOR_YELLOW{QStringLiteral("#FFEB3B")};
static const QString COLOR_YELLOW_DARK{QStringLiteral("#DCDC9D")};
static const QString COLOR_PINK{QStringLiteral("#C586C0")};
static const QString COLOR_GREY{QStringLiteral("#9E9E9E")};
static const QString COLOR_DARK_0{QStringLiteral("#1E1E1E")};
static const QString COLOR_DARK_1{QStringLiteral("#252526")};
static const QString COLOR_DARK_2{QStringLiteral("#333333")};
static const QString COLOR_LIGHT{QStringLiteral("#E0E0E0")};
static const QString ITALIC{QStringLiteral("italic")};
static const QString BOLD{QStringLiteral("bold")};
static const QString LEFT{QStringLiteral("left")};
static const QString RIGHT{QStringLiteral("right")};
static const QString OUTSET{QStringLiteral("outset")};
static const QString ENGLISH{QStringLiteral("english")};
static const QString FRENCH{QStringLiteral("french")};
static const QString SPANISH{QStringLiteral("spanish")};
static const QString SecurityIconThemes1{QStringLiteral("theme1")};
static const QString SecurityIconThemes2{QStringLiteral("theme2")};
static const QString SecurityIconThemes3{QStringLiteral("theme3")};
static const int TEXT_NAME_LENGTH{50};
static const int TEXT_LOGIN_LENGTH{50};
static const int TEXT_PASSWORD_LENGTH{50};
static const int TEXT_DETAILS_LENGTH{200};
static const int TEXT_STANDARD_SIZE{18};
static const QSize ICON_SIZE{18,18};
static const uint SIZE_WINDOW_HORIZONTAL{1200};
static const uint SIZE_WINDOW_VERTICAL{850};

class Utility{
public:
    Utility()=delete;
    Utility(Utility const&)=delete;
    Utility& operator=(Utility const&)=delete;

    static QString GET_STYLE_WIDGET(){
        return QLatin1String("QWidget{")+SET_BACKGROUND_COLOR(COLOR_DARK_1)+
                SET_TEXT_COLOR(COLOR_LIGHT)+"}";
    }

    static QString GET_STYLE_QLABEL(){
        return QLatin1String("QLabel{")+SET_HEIGHT(30)+
                SET_BORDER_SIZE(0)+
                SET_BACKGROUND_COLOR(COLOR_DARK_1)+
                SET_TEXT_COLOR(COLOR_GREY)+
                SET_TEXT_SIZE(TEXT_STANDARD_SIZE)+"}";
    }

    static QString GET_STYLE_QLINEEDIT(){
        return QLatin1String("QLineEdit{")+SET_HEIGHT(30)+
                SET_BORDER_SIZE(0)+
                SET_BACKGROUND_COLOR(COLOR_DARK_2)+
                SET_TEXT_COLOR(COLOR_LIGHT)+
                SET_TEXT_SIZE(TEXT_STANDARD_SIZE)+"}";
    }

    static QString GET_STYLE_QTOOLTYPE(){
        return QLatin1String("QToolTip {")+
                SET_BACKGROUND_COLOR(COLOR_LIGHT)+
                SET_TEXT_COLOR(COLOR_DARK_2)+"}";
    }

    static QString GET_STYLE_QTEXTEDIT(){
        return QLatin1String("QTextEdit{")+SET_BORDER_SIZE(0)+
                SET_BACKGROUND_COLOR(COLOR_DARK_2)+
                SET_TEXT_COLOR(COLOR_LIGHT)+
                SET_TEXT_SIZE(TEXT_STANDARD_SIZE)+QLatin1String("}");
    }

    static QString GET_STYLE_QPUSHBUTTON(){
        return QLatin1String("QPushButton{")+SET_HEIGHT(30)+
                SET_BACKGROUND_COLOR(COLOR_DARK_1)+
                SET_TEXT_COLOR(COLOR_LIGHT)+
                SET_TEXT_SIZE(TEXT_STANDARD_SIZE,BOLD)+
                SET_BORDER_SIZE(0)+"}"+
                QLatin1String("QPushButton:hover{")+SET_TEXT_COLOR(COLOR_LIGHT)+
                SET_TEXT_SIZE(19,BOLD)+"}"+
                QLatin1String("QPushButton:pressed{")+SET_BACKGROUND_COLOR(COLOR_DARK_2)+
                SET_TEXT_COLOR(COLOR_LIGHT)+
                SET_TEXT_SIZE(19,BOLD)+QLatin1String("}");

    }

    static QString GET_STYLE_QLISTVIEW(){
        return QLatin1String("QListView{")+Utility::SET_BACKGROUND_COLOR(COLOR_DARK_1)+
                Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,BOLD)+
                Utility::SET_BORDER_SIZE(0)+
                Utility::SET_TEXT_COLOR(COLOR_WHITE)+QLatin1String("}");

    }

    static QString GET_STYLE_QCHECKBOX(){
        return QLatin1String("QCheckBox{")+SET_HEIGHT(40)+
                SET_BACKGROUND_COLOR(COLOR_DARK_2)+
                SET_TEXT_COLOR(COLOR_LIGHT)+
                SET_TEXT_SIZE(19,BOLD)+QLatin1String("}");

    }

    static QString SET_HEIGHT(size_t iSize){
        return QLatin1String("height: ")+QString::number(iSize)+QLatin1String("px;\n");
    }

    static QString SET_WIDTH(size_t iSize){
        return QLatin1String("width: ")+QString::number(iSize)+QLatin1String("px;\n");
    }

    static QString SET_BORDER_SIZE(size_t iSize){
        return QLatin1String("border: ")+QString::number(iSize)+QLatin1String("px;\n");
    }

    static QString SET_MARGIN_SIZE(size_t iTop,
                                   size_t iRight,
                                   size_t iLeft,
                                   size_t iBottom){
        return QLatin1String("margin: ")+
                QString::number(iTop)+QLatin1String("px ")+
                QString::number(iRight)+QLatin1String("px ")+
                QString::number(iLeft)+QLatin1String("px ")+
                QString::number(iBottom)+QLatin1String("px;\n");
    }

    static QString SET_BORDER_WIDTH(size_t iTop,
                                   size_t iRight,
                                   size_t iLeft,
                                   size_t iBottom){
        return QLatin1String("border-width: ")+
                QString::number(iTop)+QLatin1String("px ")+
                QString::number(iRight)+QLatin1String("px ")+
                QString::number(iLeft)+QLatin1String("px ")+
                QString::number(iBottom)+QLatin1String("px;\n");
    }

    static QString SET_PADDING_SIZE(size_t iTop,
                                    size_t iRight,
                                    size_t iLeft,
                                    size_t iBottom){
        return QLatin1String("padding: ")+
                QString::number(iTop)+QLatin1String("px ")+
                QString::number(iRight)+QLatin1String("px ")+
                QString::number(iLeft)+QLatin1String("px ")+
                QString::number(iBottom)+QLatin1String("px;\n");
    }

    static QString SET_BORDER_COLOR(const QString& iColor){
        return QLatin1String("border-color: ")+iColor+QLatin1String(";\n");
    }

    static QString SET_TEXT_ALIGN(const QString& iAligh){
        return QLatin1String("text-align: ")+iAligh+QLatin1String(";\n");
    }


    static QString SET_BORDER_STYLE(const QString& iAligh){
        return QLatin1String("border-style: ")+iAligh+QLatin1String(";\n");
    }

    static QString SET_TEXT_SIZE(size_t iSize, const QString& iStyle=""){
        QString cssStr{QStringLiteral("font: ")};
        if (!iStyle.isEmpty()){
            cssStr+=iStyle+QLatin1String(" ");
        }
        cssStr+=QString::number(iSize)+QLatin1String("px;\n");
        return cssStr;
    }

    static QString SET_TEXT_COLOR(const QString& iColor){
        return QLatin1String("color: ")+iColor+QLatin1String(";\n");
    }

    static QString SET_BACKGROUND_COLOR(const QString& iColor){
        return QLatin1String("background-color: ")+iColor+QLatin1String(";\n");
    }


    enum ERROR{
        no_error,
        db_not_open,
        db_issue,
        db_failed_to_close,
        db_failed_to_remove,
        db_failed_to_modify,
        db_failed_to_get_data,
        password_empty,
        password_confimation_not_the_same,
        file_not_generated
    };

    static std::string getMsgError(const int& iError){
        std::string errorMsg{""};
        switch (iError) {
        case no_error:
            errorMsg="No error";
            break;
        case db_not_open:
            errorMsg="Db not open";
            break;
        case db_issue:
            errorMsg="Issue with db.";
            break;
        case db_failed_to_close:
            errorMsg="Database failed to close.";
            break;
        case db_failed_to_remove:
            errorMsg="Database failed to remove.";
            break;
        case db_failed_to_modify:
            errorMsg="Database failed to modify.";
            break;
        case db_failed_to_get_data:
            errorMsg="Couldn't get data from database.";
            break;
        case password_empty:
            errorMsg="The password should not be empty.";
            break;
        case password_confimation_not_the_same:
            errorMsg="Both passwords should be the same.";
            break;
        case file_not_generated:
            errorMsg="File not generated.";
            break;
        }

        return errorMsg;
    }
};
