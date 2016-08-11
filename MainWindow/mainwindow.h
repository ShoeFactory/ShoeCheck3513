#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "usernamepushbutton.h"
#include "usermanagedialog.h"
#include "entrymanagedialog.h"
#include "updatepasswddialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void relogin();
public slots:
    void on_receiveShow();
private slots:
    void on_relogin();
    void on_changePasswd();
    void on_userManage();
    void on_entryManage();

private:
    Ui::MainWindow *ui;
    UpdatePasswdDialog  *updatePasswdDialog;
    UserManageDialog *userManageDialog;
    EntryManageDialog *entryManageDialog;

};

#endif // MAINWINDOW_H
