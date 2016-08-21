#include <QtWidgets>

#include "changepasswddialog.h"
#include "dbhelper.h"
#include "userauth.h"

#pragma execution_character_set("utf-8")


ChangePasswdDialog::ChangePasswdDialog(QWidget *parent) :
    QDialog(parent)
{
    pushButton_ok = new QPushButton("确认",this);
    pushButton_cancel = new QPushButton("取消",this);

    label_newPasswd = new QLabel("新密码：", this);
    label_ackNewPasswd = new QLabel("新密码确认：", this);
    label_prompt = new QLabel(this);
    label_prompt->setStyleSheet("color: rgb(255, 0, 0);");

    lineEdit_newPasswd = new QLineEdit(this);
    lineEdit_ackNewPasswd = new QLineEdit(this);

    connect(pushButton_ok, &QPushButton::clicked, this, &ChangePasswdDialog::pushButton_ok_clicked);
    connect(pushButton_cancel, &QPushButton::clicked, this, &ChangePasswdDialog::pushButton_cancel_clicked);

    connect(lineEdit_newPasswd, &QLineEdit::textChanged, this, &ChangePasswdDialog::userInputChanged);
    connect(lineEdit_ackNewPasswd, &QLineEdit::textChanged, this, &ChangePasswdDialog::userInputChanged);

    QFormLayout *formLayout = new QFormLayout;
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

void ChangePasswdDialog::setTitle(QString title)
{
    setWindowTitle(title);
}

QString ChangePasswdDialog::getNewPasswd()
{
    return lineEdit_newPasswd->text();
}

ChangePasswdDialog::~ChangePasswdDialog()
{
}

void ChangePasswdDialog::showEvent(QShowEvent *)
{
    move((QApplication::desktop()->width()-width())/2,
         (QApplication::desktop()->height()-height())/3);

    lineEdit_newPasswd->clear();
    lineEdit_ackNewPasswd->clear();
    label_prompt->clear();
}

void ChangePasswdDialog::pushButton_ok_clicked()
{
    QString newPasswd = lineEdit_newPasswd->text();
    QString ackNewPasswd = lineEdit_ackNewPasswd->text();

    QString errorString;
    do{
        if(newPasswd.isEmpty() || ackNewPasswd.isEmpty())
        {
            errorString = QString("不能留空");
            break;
        }
        if(newPasswd != ackNewPasswd)
        {
            errorString = QString("两次输入新密码不一致");
            break;
        }
    }while(false);

    if(!errorString.isEmpty())
    {
        label_prompt->setText(errorString);
    }
    else
    {
        accept();
    }
}

void ChangePasswdDialog::pushButton_cancel_clicked()
{
    hide();
}

void ChangePasswdDialog::userInputChanged()
{
    label_prompt->clear();
}
