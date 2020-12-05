TEMPLATE = app
QT += widgets
QT += sql

CONFIG += c++17

RC_FILE = myapp.rc

TRANSLATIONS = mypassword_fr.ts mypassword_es.ts

RESOURCES += \
    Ressources.qrc

RC_ICONS = myappico.ico

HEADERS += \
    Account.h \
    AccountTab.h \
    AccountWindow.h \
    CreateAccountTab.h \
    Database.h \
    DateTime.h \
    Encryption.h \
    GenerateFileTab.h \
    InfoTab.h \
    Interface/IDatabase.h \
    Interface/IDateTime.h \
    Interface/IEncryption.h \
    Interface/ILog.h \
    Interface/IPasswordSecurity.h \
    Interface/ISettings.h \
    Interface/IUpdateAccountListener.h \
    Interface/IUpdateIconThemeListener.h \
    Log.h \
    MainWindow.h \
    PasswordSecurity.h \
    Settings.h \
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
    InfoTab.cpp \
    Log.cpp \
    MainWindow.cpp \
    PasswordSecurity.cpp \
    Settings.cpp \
    SettingsTab.cpp \
    main.cpp
