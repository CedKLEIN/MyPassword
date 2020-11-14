#include "MainWindow.h"
#include "NewAccountWindow.h"
#include "Database.h"
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
 * Display level security
 * Settings
 * Check number caractere per lineEdit
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
    FacDisplayAccountWindow facWindowDisplay;
    NewAccountWindow newAccount{encryption,passwordSecurity,securityLevelWindow,db,log};

    MainWindow mainWindow{facAccount,
                facWindowDisplay,
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
