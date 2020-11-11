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
    Interface/IEncryption.h \
    Interface/IGenerateFile.h \
    Interface/IListener.h \
    Interface/ILog.h \
    Log.h \
    MainWindow.h \
    NewAccountWindow.h \
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
    main.cpp

RESOURCES += \
    Ressources.qrc

DISTFILES += \
    Icon/add.png \
    Icon/delete.png \
    Icon/paper.png \
    Icon/save.png
