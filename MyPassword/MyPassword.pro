QT += widgets
QT += sql

CONFIG += c++14

HEADERS += \
    Account.h \
    AccountWindow.h \
    Database.h \
    DateTime.h \
    Encryption.h \
    GenerateFile.h \
    Interface/IDatabase.h \
    Interface/IDateTime.h \
    Interface/IEncryption.h \
    Interface/IGenerateFile.h \
    Interface/IListener.h \
    Interface/ILog.h \
    Interface/IPasswordSecurity.h \
    Log.h \
    MainWindow.h \
    NewAccountWindow.h \
    PasswordSecurity.h \
    SecurityLevelWindow.h \
    Utility.h

SOURCES += \
    Account.cpp \
    AccountWindow.cpp \
    Database.cpp \
    DateTime.cpp \
    Encryption.cpp \
    GenerateFile.cpp \
    Log.cpp \
    MainWindow.cpp \
    NewAccountWindow.cpp \
    PasswordSecurity.cpp \
    SecurityLevelWindow.cpp \
    main.cpp

RESOURCES += \
    Ressources.qrc
