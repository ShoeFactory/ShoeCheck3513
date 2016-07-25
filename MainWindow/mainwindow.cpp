#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //username下面隐藏的action
    userNameMenu = new QMenu(this);
    actionlogout = new QAction(tr("Log Out"), userNameMenu);
    actionChangePasswd = new QAction(tr("Change Pwd"), userNameMenu);
    actionUserManage = new QAction(tr("User Manage"), userNameMenu);
    actionEntryManage = new QAction(tr("Entry Manage"), userNameMenu);
    userNameMenu->addAction(actionlogout);
    userNameMenu->addAction(actionChangePasswd);
    userNameMenu->addAction(actionUserManage);
    userNameMenu->addAction(actionEntryManage);
    connect(actionlogout, &QAction::triggered, this, &MainWindow::on_relogin);
    ui->pushButton_userName->setMenu(userNameMenu);
    ui->pushButton_userName->setStyleSheet("QPushButton::menu-indicator{image:none;}");
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

void MainWindow::showEvent(QShowEvent *)
{
    User user = USER_AUTH->getCurrentUser();
    UserRole role = user.getRole();
    //依据当前的身份状态 修改界面显示
    QString roleStr;
    switch (role) {
    case UserRole::Admin:
    {
        roleStr = tr("[Admin]");
        actionUserManage->setVisible(true);
        actionEntryManage->setVisible(true);
        break;
    }
    case UserRole::Normal:
    {
        roleStr = tr("[Normal]");
        actionUserManage->setVisible(false);
        actionEntryManage->setVisible(false);
        break;
    }
    default:
        break;
    }
    ui->pushButton_userName->setText(user.getName() + roleStr);
}
