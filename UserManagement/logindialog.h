#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QShowEvent>
#include "userauth.h"
#include "dbhelper.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
signals:
    void loginEccepted();
public slots:
    void on_relogin();
private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_login_clicked();

    void on_lineEdit_userName_textChanged(const QString &arg1);
    void on_lineEdit_userPasswd_textChanged(const QString &arg1);

    void on_pushButton_configDB_clicked();

protected:
    void showEvent(QShowEvent*);

private:
    Ui::LoginDialog *ui;
};
#endif // LOGINDIALOG_H
