QT += widgets
QT += sql

CONFIG += c++14

HEADERS += \
    Account.h \
    Database.h \
    DateTime.h \
    Encryption.h \
    Error.h \
    GenerateFile.h \
    Interface/IDatabase.h \
    Interface/IEncryption.h \
    Interface/IGenerateFile.h \
    Interface/IListener.h \
    Interface/ILog.h \
    Log.h \
    windowdisplayaccount.h \
    windowlistaccount.h \
    windownewaccount.h

SOURCES += \
    Account.cpp \
    Database.cpp \
    DateTime.cpp \
    Encryption.cpp \
    GenerateFile.cpp \
    Log.cpp \
    main.cpp \
    windowdisplayaccount.cpp \
    windowlistaccount.cpp \
    windownewaccount.cpp

RESOURCES += \
    Ressources.qrc
