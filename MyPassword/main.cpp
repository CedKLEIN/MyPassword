#include "MainWindow.h"
#include "NewAccountWindow.h"
#include "Database.h"
#include "Encryption.h"
#include "Account.h"
#include "Log.h"
#include "GenerateFile.h"

#include <QApplication>

/*
 * To do:
 * Better display
 * set tooltip for each icon
 * Check english only
 * Make shoter all name ex: password = pwd ...
 */

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Log log;
    Encryption encryption;
    FacAccount facAccount;
    GenerateFile generateFile{facAccount};
    Database db{facAccount};
    FacWindowDisplayAccount facWindowDisplayAccount;
    NewAccountWindow windowNewAccount{encryption,db,log};

    MainWindow windowListAccount{
                facAccount,
                facWindowDisplayAccount,
                windowNewAccount,
                encryption,
                db,
                log,
                generateFile};

    windowListAccount.show();

    return app.exec();
}
