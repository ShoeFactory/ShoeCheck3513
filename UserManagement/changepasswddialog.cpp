#include "changepasswddialog.h"
#include "ui_changepasswddialog.h"
#include <QDesktopWidget>
#include "dbhelper.h"
#include "userauth.h"

#pragma execution_character_set("utf-8")


ChangePasswdDialog::ChangePasswdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePasswdDialog)
{
    ui->setupUi(this);
}

ChangePasswdDialog::~ChangePasswdDialog()
{
    delete ui;
}

void ChangePasswdDialog::showEvent(QShowEvent *)
{
    move((QApplication::desktop()->width()-width())/2,
         (QApplication::desktop()->height()-height())/2);

    ui->lineEdit_currentPasswd->clear();
    ui->lineEdit_newPasswd->clear();
    ui->lineEdit_ackNewPasswd->clear();

    ui->label_prompt->setStyleSheet("color: rgb(255, 0, 0);");
    ui->label_prompt->clear();
}

void ChangePasswdDialog::on_pushButton_ok_clicked()
{
    QString currentPasswd = ui->lineEdit_currentPasswd->text();
    QString newPasswd = ui->lineEdit_newPasswd->text();
    QString ackNewPasswd = ui->lineEdit_ackNewPasswd->text();

    QString errorString;
    do{
        if(currentPasswd.isEmpty() || newPasswd.isEmpty() || ackNewPasswd.isEmpty())
        {
            errorString = QString("不能留空");
            break;
        }
        if(newPasswd != ackNewPasswd)
        {
            errorString = QString("两次输入新密码不一致");
            break;
        }
        if(currentPasswd == newPasswd)
        {
            errorString = QString("新旧密码一致");
            break;
        }
    }while(false);

    if(!errorString.isEmpty())
    {
        ui->label_prompt->setText(errorString);
        return;
    }

    User user= USER_AUTH->getCurrentUser();
    bool validateResult = DB_HELPER->validateUser(user.getName(), currentPasswd, user);//验证密码
    if(validateResult)
    {
        if(DB_HELPER->updateUserPasswd(user.getName(), newPasswd))
        {
            hide();
            return;
        }
        else
        {
            ui->label_prompt->setText(QString("更新密码失败"));
        }

    }
    else
    {
        ui->label_prompt->setText(QString("当前密码验证失败"));
    }

}

void ChangePasswdDialog::on_pushButton_cancel_clicked()
{
    hide();
}

void ChangePasswdDialog::on_lineEdit_currentPasswd_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    ui->label_prompt->clear();
}

void ChangePasswdDialog::on_lineEdit_newPasswd_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    ui->label_prompt->clear();
}

void ChangePasswdDialog::on_lineEdit_ackNewPasswd_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    ui->label_prompt->clear();
}
