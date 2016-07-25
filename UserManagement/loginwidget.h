#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QShowEvent>
#include "userauth.h"
#include "dbhelper.h"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
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
    Ui::LoginWidget *ui;
};

#endif // LOGINWIDGET_H
