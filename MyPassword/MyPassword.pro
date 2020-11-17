QT += widgets
QT += sql

CONFIG += c++14

HEADERS += \
    Account.h \
    AccountTab.h \
    AccountWindow.h \
    CreateAccountTab.h \
    Database.h \
    DateTime.h \
    Encryption.h \
    GenerateFileTab.h \
    Interface/IDatabase.h \
    Interface/IDateTime.h \
    Interface/IEncryption.h \
    Interface/IListener.h \
    Interface/ILog.h \
    Interface/IPasswordSecurity.h \
    Log.h \
    MainWindow.h \
    PasswordSecurity.h \
    SecurityLevelWindow.h \
    SettingsTab.h \
    Utility.h

SOURCES += \
    Account.cpp \
    AccountTab.cpp \
    AccountWindow.cpp \
    CreateAccountTab.cpp \
    Database.cpp \
    DateTime.cpp \
    Encryption.cpp \
    GenerateFileTab.cpp \
    Log.cpp \
    MainWindow.cpp \
    PasswordSecurity.cpp \
    SecurityLevelWindow.cpp \
    SettingsTab.cpp \
    main.cpp

RESOURCES += \
    Ressources.qrc
