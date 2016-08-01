#include "usernamepushbutton.h"

#pragma execution_character_set("utf-8")

UserNamePushButton::UserNamePushButton(QWidget *parent)
    :QPushButton(parent)
{
    userNameMenu = new QMenu(this);

    actionlogout = new QAction(tr("登出"), userNameMenu);
    actionChangePasswd = new QAction(tr("修改密码"), userNameMenu);
    actionUserManage = new QAction(tr("用户管理"), userNameMenu);
    actionEntryManage = new QAction(tr("检测项管理"), userNameMenu);

    userNameMenu->addAction(actionlogout);
    userNameMenu->addAction(actionChangePasswd);
    userNameMenu->addAction(actionUserManage);
    userNameMenu->addAction(actionEntryManage);

    connect(actionlogout, &QAction::triggered, this, &UserNamePushButton::signal_logout);
    connect(actionChangePasswd, &QAction::triggered, this, &UserNamePushButton::signal_changePasswd);
    connect(actionUserManage, &QAction::triggered, this, &UserNamePushButton::signal_userManage);
    connect(actionEntryManage, &QAction::triggered, this, &UserNamePushButton::signal_entryManage);

    setMenu(userNameMenu);
    setStyleSheet("QPushButton::menu-indicator{image:none;}");
}

void UserNamePushButton::showEvent(QShowEvent *)
{
    User user = USER_AUTH->getCurrentUser();
    UserRole role = user.getRole();
    //依据当前的身份状态 修改界面显示
    QString roleStr;
    switch (role) {
    case UserRole::Admin:
    {
        roleStr = tr("[Admin]");
        actionUserManage->setVisible(true);
        actionEntryManage->setVisible(true);
        break;
    }
    case UserRole::Normal:
    {
        roleStr = tr("[Normal]");
        actionUserManage->setVisible(false);
        actionEntryManage->setVisible(false);
        break;
    }
    default:
        break;
    }
    setText(user.getName() + roleStr);
}

