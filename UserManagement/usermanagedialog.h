#ifndef USERMANAGEDIALOG_H
#define USERMANAGEDIALOG_H

#include <QDialog>
#include <QShowEvent>
QT_BEGIN_NAMESPACE
class QTableView;
class QSqlRelationalTableModel;
class QSqlRelationalDelegate;
class QPushButton;
QT_END_NAMESPACE

class ChangePasswdDialog;



namespace Ui {
class UserManageDialog;
}

class UserManageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserManageDialog(QWidget *parent = 0);
    ~UserManageDialog();

protected:
    void showEvent(QShowEvent*);

private:
    int generateNewUserId();

private slots:
    void on_addUser();
    void on_removeUser();
    void on_changePasswd();

    void on_ok();
    void on_cancel();
    void on_apply();

private:
    Ui::UserManageDialog *ui;

    QPushButton *button_addUser;
    QPushButton *button_removeUser;
    QPushButton *button_changePasswd;
    ChangePasswdDialog *changePasswdDialog;

    QTableView *userTableView;
    QSqlRelationalTableModel *userTableModel;

    QPushButton *button_ok;
    QPushButton *button_cancel;
    QPushButton *button_apply;

    int uniqueUserId;
};

#endif // USERMANAGEDIALOG_H
