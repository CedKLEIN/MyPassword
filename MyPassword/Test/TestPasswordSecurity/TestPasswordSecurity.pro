QT += widgets testlib sql

CONFIG += testcase no_testcase_installs

TEMPLATE = app

HEADERS += \
    ../../Src/Account.h \
    ../../Src/AccountTab.h \
    ../../Src/AccountWindow.h \
    ../../Src/CreateAccountTab.h \
    ../../Src/Database.h \
    ../../Src/DateTime.h \
    ../../Src/Encryption.h \
    ../../Src/GenerateFileTab.h \
    ../../Src/InfoTab.h \
    ../../Src/Interface/IDatabase.h \
    ../../Src/Interface/IDateTime.h \
    ../../Src/Interface/IEncryption.h \
    ../../Src/Interface/IListener.h \
    ../../Src/Interface/ILog.h \
    ../../Src/Interface/IPasswordSecurity.h \
    ../../Src/Interface/ISettings.h \
    ../../Src/Log.h \
    ../../Src/MainWindow.h \
    ../../Src/PasswordSecurity.h \
    ../../Src/Settings.h \
    ../../Src/SettingsTab.h \
    ../../Src/Utility.h

SOURCES += \
    ../../Src/Account.cpp \
    ../../Src/AccountTab.cpp \
    ../../Src/AccountWindow.cpp \
    ../../Src/CreateAccountTab.cpp \
    ../../Src/Database.cpp \
    ../../Src/DateTime.cpp \
    ../../Src/Encryption.cpp \
    ../../Src/GenerateFileTab.cpp \
    ../../Src/InfoTab.cpp \
    ../../Src/Log.cpp \
    ../../Src/MainWindow.cpp \
    ../../Src/PasswordSecurity.cpp \
    ../../Src/Settings.cpp \
    ../../Src/SettingsTab.cpp \
    TestPasswordSecurity.cpp

