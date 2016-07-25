QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShoeDecetion
TEMPLATE = app

INCLUDEPATH += \
        UserManagement\
        MainWindow

SOURCES += \
    main.cpp \
    UserManagement/loginwidget.cpp \
    UserManagement/userauth.cpp \
    MainWindow/mainwindow.cpp \
    UserManagement/user.cpp

HEADERS += \
    UserManagement/loginwidget.h \
    UserManagement/userauth.h \
    MainWindow/mainwindow.h \
    UserManagement/user.h

FORMS += \
    UserManagement/loginwidget.ui \
    MainWindow/mainwindow.ui
