#include "windowlistaccount.h"
#include "windownewaccount.h"
#include "Database.h"
#include "Encryption.h"
#include "Account.h"
#include "Error.h"
#include "Log.h"
#include "GenerateFile.h"

#include <QApplication>

/*
 * To do:
 * Unit test
 * Better display
 * Create Fac for displayWindow ?
 */

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Log log;
    Error error;
    Encryption encryption;
    FacAccount facAccount;
    GenerateFile generateFile(facAccount,error);
    Database db(facAccount,error);
    WindowNewAccount windowNewAccount(encryption,db,error,log);

    WindowListAccount windowListAccount(facAccount,windowNewAccount,encryption,db,error,log,generateFile);
    windowListAccount.show();

    int result = app.exec();

    return result;

}
