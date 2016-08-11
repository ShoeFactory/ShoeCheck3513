#ifndef DBHELPER_H
#define DBHELPER_H

#include <QSqlDatabase>
#include "user.h"

typedef struct DBConnectPara{
    QString driver;

    QString databaseName;
    QString userName;
    QString userPasswd;

    QString hostName;
    int port;

}DBConnectPara;

class DBHelper
{
public:
    /* 帮助函数 */
    bool isOpen();
    QSqlError createConnection();
    QString getMD5String(QString readableString);

    /* 用户部分功能 */
    bool validateUser(QString name, QString passwd, User&user);
    bool updateUserPasswd(QString name, QString newPasswd);

    /* 数据库检查项目部分功能 */

public:
    DBHelper();
    static DBHelper *getDBHelperInstance();
private:
    QSqlError connectToDataBase(DBConnectPara para);

    QSqlDatabase m_db;
    static DBHelper* dbHelper;

};
#define DB_HELPER DBHelper::getDBHelperInstance()
#endif // DBHELPER_H
