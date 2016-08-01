#include "loginwidget.h"
#include "ui_loginwidget.h"

#pragma execution_character_set("utf-8")

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    ui->pushButton_login->setDefault(true);
    ui->pushButton_login->setFocus();
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_relogin()
{
    show();
}

void LoginWidget::on_pushButton_cancel_clicked()
{
    qApp->quit();
}

void LoginWidget::on_pushButton_login_clicked()
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

void LoginWidget::on_lineEdit_userName_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    ui->label_prompt->clear();
}

void LoginWidget::on_lineEdit_userPasswd_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    ui->label_prompt->clear();
}

void LoginWidget::showEvent(QShowEvent *)
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
    ui->pushButton_login->setFocus();
}

void LoginWidget::on_pushButton_configDB_clicked()
{

}

void LoginWidget::on_lineEdit_userName_editingFinished()
{
    ui->pushButton_login->setFocus();
}
