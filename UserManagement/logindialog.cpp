#include "logindialog.h"
#include "ui_logindialog.h"

#pragma execution_character_set("utf-8")

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    ui->pushButton_login->setDefault(true);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_relogin()
{
    show();
}

void LoginDialog::on_pushButton_cancel_clicked()
{
    close();
}

void LoginDialog::on_pushButton_login_clicked()
{
    User user;
    if(DB_HELPER->validateUser(ui->lineEdit_userName->text(),
                               ui->lineEdit_userPasswd->text(),
                               user))
    {
        USER_AUTH->setCurrentUser(user);
        ui->lineEdit_userPasswd->clear();
        hide();
        emit loginEccepted();
    }
    else
    {
        ui->lineEdit_userPasswd->clear();
        ui->label_prompt->setText(QString("错误的用户名或密码"));
    }

}

void LoginDialog::on_lineEdit_userName_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    ui->label_prompt->clear();
}

void LoginDialog::on_lineEdit_userPasswd_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    ui->label_prompt->clear();
}

void LoginDialog::showEvent(QShowEvent *)
{
    ui->label_prompt->setStyleSheet("color: rgb(255, 0, 0);");
    ui->label_prompt->clear();

    QString connectStatus;
    if(DB_HELPER->isOpen())
    {
        connectStatus = QString("欢迎使用……");
        ui->pushButton_configDB->setHidden(true);
    }
    else
    {
        connectStatus = QString("连接数据库失败…");
        ui->pushButton_configDB->setHidden(false);
    }
    ui->label_status->setText(connectStatus);
}

void LoginDialog::on_pushButton_configDB_clicked()
{

}
