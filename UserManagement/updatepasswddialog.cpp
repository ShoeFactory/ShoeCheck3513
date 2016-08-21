#include <QtWidgets>

#include "updatepasswddialog.h"
#include "dbhelper.h"
#include "userauth.h"

#pragma execution_character_set("utf-8")


UpdatePasswdDialog::UpdatePasswdDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("修改密码");

    pushButton_ok = new QPushButton("确认",this);
    pushButton_cancel = new QPushButton("取消",this);

    label_currentPasswd = new QLabel("当前密码：", this);
    label_newPasswd = new QLabel("新密码：", this);
    label_ackNewPasswd = new QLabel("新密码确认：", this);
    label_prompt = new QLabel(this);
    label_prompt->setStyleSheet("color: rgb(255, 0, 0);");


    lineEdit_currentPasswd = new QLineEdit(this);
    lineEdit_newPasswd = new QLineEdit(this);
    lineEdit_ackNewPasswd = new QLineEdit(this);

    connect(pushButton_ok, &QPushButton::clicked, this, &UpdatePasswdDialog::pushButton_ok_clicked);
    connect(pushButton_cancel, &QPushButton::clicked, this, &UpdatePasswdDialog::pushButton_cancel_clicked);

    connect(lineEdit_currentPasswd, &QLineEdit::textChanged, this, &UpdatePasswdDialog::userInputChanged);
    connect(lineEdit_newPasswd, &QLineEdit::textChanged, this, &UpdatePasswdDialog::userInputChanged);
    connect(lineEdit_ackNewPasswd, &QLineEdit::textChanged, this, &UpdatePasswdDialog::userInputChanged);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(label_currentPasswd, lineEdit_currentPasswd);
    formLayout->addRow(label_newPasswd, lineEdit_newPasswd);
    formLayout->addRow(label_ackNewPasswd, lineEdit_ackNewPasswd);

    QHBoxLayout *hboxLayout = new QHBoxLayout;
    hboxLayout->addStretch();
    hboxLayout->addWidget(pushButton_ok);
    hboxLayout->addWidget(pushButton_cancel);
    hboxLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(label_prompt);
    mainLayout->addLayout(hboxLayout);
    mainLayout->addStretch();

}

UpdatePasswdDialog::~UpdatePasswdDialog()
{
}

void UpdatePasswdDialog::showEvent(QShowEvent *)
{
    move((QApplication::desktop()->width()-width())/2,
         (QApplication::desktop()->height()-height())/3);

    lineEdit_currentPasswd->clear();
    lineEdit_newPasswd->clear();
    lineEdit_ackNewPasswd->clear();

    label_prompt->clear();
}

void UpdatePasswdDialog::pushButton_ok_clicked()
{
    QString currentPasswd = lineEdit_currentPasswd->text();
    QString newPasswd = lineEdit_newPasswd->text();
    QString ackNewPasswd = lineEdit_ackNewPasswd->text();

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
        label_prompt->setText(errorString);
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
            label_prompt->setText(QString("更新密码失败"));
        }

    }
    else
    {
        label_prompt->setText(QString("当前密码验证失败"));
    }

}

void UpdatePasswdDialog::pushButton_cancel_clicked()
{
    hide();
}

void UpdatePasswdDialog::userInputChanged()
{
    label_prompt->clear();
}
