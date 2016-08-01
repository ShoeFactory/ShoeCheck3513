#ifndef CHANGEPASSWDDIALOG_H
#define CHANGEPASSWDDIALOG_H

#include <QDialog>
#include <QShowEvent>

namespace Ui {
class ChangePasswdDialog;
}

class ChangePasswdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePasswdDialog(QWidget *parent = 0);
    ~ChangePasswdDialog();

protected:
    void showEvent(QShowEvent*);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_cancel_clicked();

    void on_lineEdit_currentPasswd_textChanged(const QString &arg1);
    void on_lineEdit_newPasswd_textChanged(const QString &arg1);
    void on_lineEdit_ackNewPasswd_textChanged(const QString &arg1);


private:
    Ui::ChangePasswdDialog *ui;
};

#endif // CHANGEPASSWDDIALOG_H
