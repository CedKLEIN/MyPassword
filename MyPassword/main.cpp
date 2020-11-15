#include "MainWindow.h"
#include "AccountTab.h"
#include "CreateAccountTab.h"
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
    GenerateFile generateFile{facAccount};
    Database db{facAccount};

    SecurityLevelWindow securityLevelWindow{passwordSecurity};
    AccountWindow accountWindow{facAccount,
                encryption,
                passwordSecurity,
                securityLevelWindow,
                db,
                log};
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
                generateFile};

    MainWindow _mainWindow{accountTab,createAccountTab};
    _mainWindow.show();

    return app.exec();
}
