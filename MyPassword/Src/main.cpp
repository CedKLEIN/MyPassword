#include "MainWindow.h"
#include "AccountTab.h"
#include "CreateAccountTab.h"
#include "GenerateFileTab.h"
#include "SettingsTab.h"
#include "InfoTab.h"
#include "Database.h"
#include "AccountWindow.h"
#include "Encryption.h"
#include "Account.h"
#include "Log.h"
#include "PasswordSecurity.h"
#include "Settings.h"
#include "Utility.h"

#include <QApplication>
#include <QTranslator>

/*
 * Add a text file to generate a file from extern before import data
 * Make new translation
 */

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Settings settings;

    QTranslator translator;
    if(settings.getLanguage() == FRENCH){
        translator.load("mypassword_fr");
        app.installTranslator(&translator);
    }else if(settings.getLanguage() == SPANISH){
        translator.load("mypassword_es");
        app.installTranslator(&translator);
    }

    Log log;
    Encryption encryption;
    FacAccount facAccount;
    Database db{facAccount};
    PasswordSecurity passwordSecurity{settings};


    AccountWindow accountWindow{facAccount,
                encryption,
                passwordSecurity,
                db,
                log};

    SettingsTab settingsTab{facAccount,db,log,settings,app};

    CreateAccountTab createAccountTab{encryption,
                passwordSecurity,
                db,
                log};

    GenerateFileTab generateFileTab{facAccount,db,log};

    AccountTab accountTab{facAccount,
                accountWindow,
                createAccountTab,
                generateFileTab,
                passwordSecurity,
                db,
                log,
                settingsTab,
                settings};

    InfoTab infoTab{passwordSecurity,settingsTab};

    MainWindow mainWindow{accountTab,createAccountTab,generateFileTab,settingsTab,infoTab};
    mainWindow.show();

    return app.exec();
}
