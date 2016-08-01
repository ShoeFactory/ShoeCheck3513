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
    DBManagement/dbhelper.cpp \
    UserManagement/usernamepushbutton.cpp \
    UserManagement/changepasswddialog.cpp \
    UserManagement/usermanagedialog.cpp \
    UserManagement/entrymanagedialog.cpp

HEADERS += \
    UserManagement/loginwidget.h \
    UserManagement/userauth.h \
    MainWindow/mainwindow.h \
    UserManagement/user.h \
    DBManagement/dbhelper.h \
    UserManagement/usernamepushbutton.h \
    UserManagement/changepasswddialog.h \
    UserManagement/usermanagedialog.h \
    UserManagement/entrymanagedialog.h

FORMS += \
    UserManagement/loginwidget.ui \
    MainWindow/mainwindow.ui \
    UserManagement/changepasswddialog.ui \
    UserManagement/usermanagedialog.ui \
    UserManagement/entrymanagedialog.ui
