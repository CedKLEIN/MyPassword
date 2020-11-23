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

#include <QApplication>

/*
 * To do:
 * set tooltip for each icon
 * Make shorter all name ex: password = pwd ...
 * QSettings save language
 * fix bug
 */

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Log log;
    Encryption encryption;
    FacAccount facAccount;
    Settings settings;
    Database db{facAccount};
    PasswordSecurity passwordSecurity{settings};

    AccountWindow accountWindow{facAccount,
                encryption,
                passwordSecurity,
                db,
                log};

    SettingsTab settingsTab{facAccount,db,settings};

    CreateAccountTab createAccountTab{encryption,
                passwordSecurity,
                db,
                log};

    AccountTab accountTab{facAccount,
                accountWindow,
                createAccountTab,
                passwordSecurity,
                db,
                log,
                settingsTab,
                settings};

    GenerateFileTab generateFileTab{facAccount};
    InfoTab infoTab{passwordSecurity};

    MainWindow mainWindow{accountTab,createAccountTab,generateFileTab,settingsTab,infoTab};
    mainWindow.show();

    int a= app.exec();

    return a;
}
