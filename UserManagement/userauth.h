#ifndef USERAUTH_H
#define USERAUTH_H

#include <QObject>
#include <QSqlDatabase>

#include "user.h"
///
/// \brief The UserAuth class
///集成了用户认证和用户管理
///
class UserAuth : public QObject
{
    Q_OBJECT

public:
    /* 用户认证部分功能 */
    User getCurrentUser() const;
    void setCurrentUser(const User &value);

    /* 数据库用户部分功能 */
    bool validateUser(QString name, QString passwd, User&user);

    /* 数据库检查项目部分功能 */

public:
    static UserAuth *getUserInstance();
private:
    explicit UserAuth(QObject *parent = 0);
    static UserAuth *userAuth;
    User currentUser;
    QSqlDatabase database;
};
#define USER_AUTH UserAuth::getUserInstance()

#endif // USERAUTH_H
