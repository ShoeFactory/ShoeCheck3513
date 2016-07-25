QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShoeDecetion
TEMPLATE = app

INCLUDEPATH += \
        DBManagement \
        UserManagement\
        MainWindow

SOURCES += \
    main.cpp \
    UserManagement/loginwidget.cpp \
    UserManagement/userauth.cpp \
    MainWindow/mainwindow.cpp \
    UserManagement/user.cpp \
    DBManagement/dbhelper.cpp

HEADERS += \
    UserManagement/loginwidget.h \
    UserManagement/userauth.h \
    MainWindow/mainwindow.h \
    UserManagement/user.h \
    DBManagement/dbhelper.h

FORMS += \
    UserManagement/loginwidget.ui \
    MainWindow/mainwindow.ui
