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

    bool isOpen();
    bool connectToConfigedDB();
    bool initialFillTheEmptyDB();
    bool connectToDataBase(DBConnectPara para);

    /* 用户部分功能 */
    bool validateUser(QString name, QString passwd, User&user);

    /* 数据库检查项目部分功能 */
public:
    DBHelper();
    static DBHelper *getDBHelperInstance();
private:
    QSqlDatabase m_db;
    static DBHelper* dbHelper;

};
#define DB_HELPER DBHelper::getDBHelperInstance()
#endif // DBHELPER_H
