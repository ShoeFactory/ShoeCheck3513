#ifndef USERNAMEPUSHBUTTON_H
#define USERNAMEPUSHBUTTON_H

#include <QPushButton>
#include <QAction>
#include <QMenu>
#include <QShowEvent>
#include "userauth.h"
#include "user.h"

class UserNamePushButton : public QPushButton
{
    Q_OBJECT
public:
    UserNamePushButton(QWidget *parent = 0);
signals:
    void signal_logout();
    void signal_changePasswd();
    void signal_userManage();
    void signal_entryManage();

protected:
    void showEvent(QShowEvent *);

private:
    QMenu *userNameMenu;
    QAction *actionlogout;
    QAction *actionChangePasswd;
    QAction *actionUserManage;
    QAction *actionEntryManage;

};

#endif // USERNAMEPUSHBUTTON_H
