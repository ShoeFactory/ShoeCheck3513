#ifndef UPDATEPASSWDDIALOG_H
#define UPDATEPASSWDDIALOG_H

#include <QDialog>
#include <QShowEvent>

class QPushButton;
class QLineEdit;
class QLabel;

class UpdatePasswdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdatePasswdDialog(QWidget *parent = 0);
    ~UpdatePasswdDialog();

protected:
    void showEvent(QShowEvent*);

private slots:
    void pushButton_ok_clicked();
    void pushButton_cancel_clicked();

    void userInputChanged();

private:
    QPushButton *pushButton_ok;
    QPushButton *pushButton_cancel;

    QLabel *label_currentPasswd;
    QLabel *label_newPasswd;
    QLabel *label_ackNewPasswd;
    QLabel *label_prompt;

    QLineEdit *lineEdit_currentPasswd;
    QLineEdit *lineEdit_newPasswd;
    QLineEdit *lineEdit_ackNewPasswd;
};

#endif // UPDATEPASSWDDIALOG_H
