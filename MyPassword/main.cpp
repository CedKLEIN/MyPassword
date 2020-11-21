#include "MainWindow.h"
#include "AccountTab.h"
#include "CreateAccountTab.h"
#include "GenerateFileTab.h"
#include "SettingsTab.h"
#include "Database.h"
#include "AccountWindow.h"
#include "Encryption.h"
#include "Account.h"
#include "Log.h"
#include "PasswordSecurity.h"
#include "SecurityLevelWindow.h"

#include <QApplication>

/*
 * To do:
 * set tooltip for each icon
 * Make shoter all name ex: password = pwd ...
 * QSettings save language
 * delete all acount
 * fix bug
 */

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Log log;
    Encryption encryption;
    FacAccount facAccount;
    PasswordSecurity passwordSecurity;
    Database db{facAccount};

    SecurityLevelWindow securityLevelWindow{passwordSecurity};

    AccountWindow accountWindow{facAccount,
                encryption,
                passwordSecurity,
                securityLevelWindow,
                db,
                log};
    SettingsTab settingsTab{facAccount,db};

    CreateAccountTab createAccountTab{encryption,
                passwordSecurity,
                securityLevelWindow,
                db,
                log};

    AccountTab accountTab{facAccount,
                accountWindow,
                createAccountTab,
                passwordSecurity,
                db,
                log,
                settingsTab};

    GenerateFileTab generateFileTab{facAccount};


    MainWindow mainWindow{accountTab,createAccountTab,generateFileTab,settingsTab};
    mainWindow.show();

    return app.exec();
}
