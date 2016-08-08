#include <QApplication>

#include <QSqlError>
#include "logindialog.h"
#include "mainwindow.h"
#include "dbhelper.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DB_HELPER->createConnection();

    MainWindow mainWindow;
    LoginDialog loginDialog;

    QObject::connect(&loginDialog, SIGNAL(loginEccepted()),
                     &mainWindow, SLOT(on_receiveShow()));
    QObject::connect(&mainWindow, SIGNAL(relogin()),
                     &loginDialog, SLOT(on_relogin()));

    loginDialog.show();

    return a.exec();
}
