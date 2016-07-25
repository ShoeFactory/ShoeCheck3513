#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    ui->label_prompt->setStyleSheet("color: rgb(255, 0, 0);");
    ui->label_prompt->clear();

    ui->pushButton_login->setDefault(true);
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
    ui->lineEdit_userPasswd->clear();

    User user;
    if(USER_AUTH->validateUser(ui->lineEdit_userName->text(),
                               ui->lineEdit_userPasswd->text(),
                               user))
    {
        USER_AUTH->setCurrentUser(user);
        hide();
        emit loginEccepted();
    }
    else
    {
        ui->label_prompt->setText(QString("Wrong UserName or Password"));
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
