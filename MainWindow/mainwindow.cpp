#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_userName, &UserNamePushButton::signal_logout, this, &MainWindow::on_relogin);
    connect(ui->pushButton_userName, &UserNamePushButton::signal_changePasswd, this, &MainWindow::on_changePasswd);
    connect(ui->pushButton_userName, &UserNamePushButton::signal_userManage, this, &MainWindow::on_userManage);
    connect(ui->pushButton_userName, &UserNamePushButton::signal_entryManage, this, &MainWindow::on_entryManage);

    updatePasswdDialog = new UpdatePasswdDialog(this);
    userManageDialog = new UserManageDialog(this);
    entryManageDialog = new EntryManageDialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_receiveShow()
{
    show();
}

void MainWindow::on_relogin()
{
    hide();
    emit relogin();
}

void MainWindow::on_changePasswd()
{
    updatePasswdDialog->exec();
}

void MainWindow::on_userManage()
{
    userManageDialog->exec();
}

void MainWindow::on_entryManage()
{
    entryManageDialog->exec();
}
