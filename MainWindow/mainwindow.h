#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShowEvent>
#include <QMenu>

#include "userauth.h"

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
protected:
    void showEvent(QShowEvent*);

private:
    Ui::MainWindow *ui;

    QMenu *userNameMenu;
    QAction *actionlogout;
    QAction *actionChangePasswd;
    QAction *actionUserManage;
    QAction *actionEntryManage;

};

#endif // MAINWINDOW_H
