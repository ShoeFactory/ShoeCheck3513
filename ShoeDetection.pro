QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_ICONS =  shoedetection.ico

TARGET = ShoeDetetion
TEMPLATE = app

INCLUDEPATH += \
        DBManagement \
        UserManagement\
        EntryManagement \
        MainWindow

SOURCES += \
    main.cpp \
    UserManagement/userauth.cpp \
    MainWindow/mainwindow.cpp \
    UserManagement/user.cpp \
    DBManagement/dbhelper.cpp \
    UserManagement/usernamepushbutton.cpp \
    UserManagement/changepasswddialog.cpp \
    UserManagement/usermanagedialog.cpp \
    UserManagement/logindialog.cpp \
    UserManagement/updatepasswddialog.cpp \
    EntryManagement/entrymanagedialog.cpp \
    EntryManagement/entrysingle.cpp \
    EntryManagement/entrytotal.cpp

HEADERS += \
    UserManagement/userauth.h \
    MainWindow/mainwindow.h \
    UserManagement/user.h \
    DBManagement/dbhelper.h \
    UserManagement/usernamepushbutton.h \
    UserManagement/changepasswddialog.h \
    UserManagement/usermanagedialog.h \
    UserManagement/logindialog.h \
    UserManagement/updatepasswddialog.h \
    EntryManagement/entrymanagedialog.h \
    EntryManagement/entrysingle.h \
    EntryManagement/entrytotal.h

FORMS += \
    MainWindow/mainwindow.ui \
    UserManagement/usermanagedialog.ui \
    UserManagement/logindialog.ui \
    EntryManagement/entrymanagedialog.ui
