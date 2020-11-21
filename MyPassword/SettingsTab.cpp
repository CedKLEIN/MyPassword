#include "SettingsTab.h"
#include "Account.h"
#include "Interface/IDatabase.h"
#include "Utility.h"

#include <QMessageBox>

SettingsTab::SettingsTab(FacAccount& iFacAccount,IDatabase& iDatabase):
    _facAccount{iFacAccount},
    _database{iDatabase}
{
    setFixedWidth(SIZE_WINDOW_HORIZONTAL);
    setStyleSheet(Utility::GET_STYLE_WIDGET()+
                  Utility::GET_STYLE_QLABEL()+
                  Utility::GET_STYLE_QPUSHBUTTON());

    _titleLabel.setStyleSheet(Utility::SET_TEXT_SIZE(40)+
                              Utility::SET_TEXT_COLOR(COLOR_LIGHT));
    _titleLayout.setAlignment(Qt::AlignCenter);
    _titleLayout.addWidget(&_titleLabel);

    _languageComboBox.setStyleSheet(Utility::SET_HEIGHT(40)+
                                    Utility::SET_BORDER_SIZE(0)+
                                    Utility::SET_BACKGROUND_COLOR(COLOR_DARK_2)+
                                    Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,BOLD));
    _languageComboBox.addItem(QIcon(QStringLiteral(":/english")),tr("  English"));
    _languageComboBox.addItem(QIcon(QStringLiteral(":/france")),tr("  French"));
    _languageComboBox.addItem(QIcon(QStringLiteral(":/spanish")),tr("  Spanish"));

    _resetButt.setStyleSheet(Utility::SET_HEIGHT(40)+
                             Utility::SET_BACKGROUND_COLOR(COLOR_BLUE));

    _mainLayout.setAlignment(Qt::AlignTop);
    _mainLayout.addSpacing(20);
    _mainLayout.addLayout(&_titleLayout);
    _mainLayout.addSpacing(20);
    _mainLayout.addWidget(&_languageLabel);
    _mainLayout.addWidget(&_languageComboBox);
    _mainLayout.addSpacing(20);
    _mainLayout.addWidget(&_resetLabel);
    _mainLayout.addWidget(&_resetButt);
    setLayout(&_mainLayout);

    QObject::connect(&_resetButt,&QPushButton::clicked,this,&SettingsTab::reset);

}

void SettingsTab::reset(){
    int answer{QMessageBox::warning(this, tr("Reset"),
                                    tr("Do you really want to delete all your accounts ?"),
                                    QMessageBox::Yes | QMessageBox::No)};

    if(answer != QMessageBox::Yes)
        return;

    _database.removeAll();
    fireRefreshAccounts();
}
