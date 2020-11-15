#include "MainWindow.h"
#include "NewAccountWindow.h"
#include "Database.h"
#include "AccountWindow.h"
#include "Encryption.h"
#include "Account.h"
#include "Log.h"
#include "GenerateFile.h"
#include "PasswordSecurity.h"
#include "SecurityLevelWindow.h"

#include <QApplication>

/*
 * To do:
 * Better display
 * set tooltip for each icon
 * Check english only
 * Make shoter all name ex: password = pwd ...
 * Settings
 * Check number caractere per lineEdit
 * Clear items
 */

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Log log;
    Encryption encryption;
    FacAccount facAccount;
    PasswordSecurity passwordSecurity;
    SecurityLevelWindow securityLevelWindow{passwordSecurity};
    GenerateFile generateFile{facAccount};
    Database db{facAccount};
    AccountWindow accountWindow{facAccount,
                encryption,
                passwordSecurity,
                securityLevelWindow,
                db,
                log};
    NewAccountWindow newAccount{encryption,
                passwordSecurity,
                securityLevelWindow,
                db,
                log};

    MainWindow mainWindow{facAccount,
                accountWindow,
                newAccount,
                encryption,
                passwordSecurity,
                securityLevelWindow,
                db,
                log,
                generateFile};

    mainWindow.show();

    return app.exec();
}
