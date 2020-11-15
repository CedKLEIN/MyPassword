#pragma once

#include <string>
#include <QString>
#include <QSize>

static const QString COLOR_WHITE{"#FFFFFF"};
static const QString COLOR_RED{"#D32F2F"};
static const QString COLOR_GREEN{"#388E3C"};
static const QString COLOR_BLUE{"#1177BB"};
static const QString COLOR_BLUE_LIGHT{"#7BDCFE"};
static const QString COLOR_YELLOW{"#DCDC9D"};
static const QString COLOR_PINK{"#C586C0"};
static const QString COLOR_GREY{"#9E9E9E"};
static const QString COLOR_DARK_0{"#1E1E1E"};
static const QString COLOR_DARK_1{"#252526"};
static const QString COLOR_DARK_2{"#333333"};
static const QString COLOR_LIGHT{"#E0E0E0"};
static const QString ITALIC{"italic"};
static const QString BOLD{"bold"};
static const QString LEFT{"left"};
static const QString RIGHT{"right"};
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
        return "QWidget{"+SET_BACKGROUND_COLOR(COLOR_DARK_1)+
                SET_TEXT_COLOR(COLOR_LIGHT)+"}";
    }

    static QString GET_STYLE_QLABEL(){
        return "QLabel{"+SET_HEIGHT(30)+
                SET_BORDER_SIZE(0)+
                SET_BACKGROUND_COLOR(COLOR_DARK_1)+
                SET_TEXT_COLOR(COLOR_GREY)+
                SET_TEXT_SIZE(TEXT_STANDARD_SIZE)+"}";
    }

    static QString GET_STYLE_QLINEEDIT(){
        return "QLineEdit{"+SET_HEIGHT(30)+
                SET_BORDER_SIZE(0)+
                SET_BACKGROUND_COLOR(COLOR_DARK_2)+
                SET_TEXT_COLOR(COLOR_LIGHT)+
                SET_TEXT_SIZE(TEXT_STANDARD_SIZE)+"}";
    }

    static QString GET_STYLE_QTEXTEDIT(){
        return "QTextEdit{"+SET_BORDER_SIZE(0)+
                SET_BACKGROUND_COLOR(COLOR_DARK_2)+
                SET_TEXT_COLOR(COLOR_LIGHT)+
                SET_TEXT_SIZE(TEXT_STANDARD_SIZE)+"}";
    }

    static QString GET_STYLE_QPUSHBUTTON(){
        return "QPushButton{"+SET_HEIGHT(30)+
                SET_BACKGROUND_COLOR(COLOR_DARK_1)+
                SET_TEXT_COLOR(COLOR_LIGHT)+
                SET_TEXT_SIZE(TEXT_STANDARD_SIZE,BOLD)+
                SET_BORDER_SIZE(0)+"}"+
                "QPushButton:hover{"+SET_TEXT_COLOR(COLOR_LIGHT)+
                SET_TEXT_SIZE(19,BOLD)+"}"+
                "QPushButton:pressed{"+SET_BACKGROUND_COLOR(COLOR_DARK_2)+
                SET_TEXT_COLOR(COLOR_LIGHT)+
                SET_TEXT_SIZE(19,BOLD)+"}";

    }

    static QString GET_STYLE_QLISTVIEW(){
        return "QListView{"+Utility::SET_BACKGROUND_COLOR(COLOR_DARK_1)+
                Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,BOLD)+
                Utility::SET_BORDER_SIZE(0)+
                Utility::SET_TEXT_COLOR(COLOR_WHITE)+"}";

    }

    static QString SET_HEIGHT(size_t iSize){
        return "height: "+QString::number(iSize)+"px;\n";
    }

    static QString SET_WIDTH(size_t iSize){
        return "width: "+QString::number(iSize)+"px;\n";
    }

    static QString SET_BORDER_SIZE(size_t iSize){
        return "border: "+QString::number(iSize)+"px;\n";
    }

    static QString SET_MARGIN_SIZE(size_t iTop,
                                   size_t iRight,
                                   size_t iLeft,
                                   size_t iBottom){
        return "margin: "+QString::number(iTop)+"px \
                                                "+QString::number(iRight)+"px \
                                                "+QString::number(iLeft)+"px \
                                                "+QString::number(iBottom)+"px;\n";
    }

    static QString SET_PADDING_SIZE(size_t iTop,
                                   size_t iRight,
                                   size_t iLeft,
                                   size_t iBottom){
        return "padding: "+QString::number(iTop)+"px \
                                                "+QString::number(iRight)+"px \
                                                "+QString::number(iLeft)+"px \
                                                "+QString::number(iBottom)+"px;\n";
    }

    static QString SET_BORDER_COLOR(const QString& iColor){
        return "border-color: "+iColor+";\n";
    }

    static QString SET_TEXT_ALIGN(const QString& iAligh){
        return "text-align: "+iAligh+";\n";
    }

    static QString SET_TEXT_SIZE(size_t iSize, const QString& iStyle=""){
        QString cssStr{"font: "};
        if (!iStyle.isEmpty()){
            cssStr+=iStyle+" ";
        }
        cssStr+=QString::number(iSize)+"px;\n";
        return cssStr;
    }

    static QString SET_TEXT_COLOR(const QString& iColor){
        return "color: "+iColor+";\n";
    }

    static QString SET_BACKGROUND_COLOR(const QString& iColor){
        return "background-color: "+iColor+";\n";
    }


    enum ERROR{
        no_error,
        db_not_open,
        db_unique_key_already_exist,
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
        case db_unique_key_already_exist:
            errorMsg="This name is already existing.";
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
