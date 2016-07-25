#include <QApplication>
#include "loginwidget.h"
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    LoginWidget loginWidget;

    QObject::connect(&loginWidget, SIGNAL(loginEccepted()),
                     &mainWindow, SLOT(on_receiveShow()));
    QObject::connect(&mainWindow, SIGNAL(relogin()),
                     &loginWidget, SLOT(on_relogin()));

    loginWidget.show();

    return a.exec();
}
