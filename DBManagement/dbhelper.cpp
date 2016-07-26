#include "dbhelper.h"
#include <QApplication>
#include <QtSql>
#include <QString>
#include <QCryptographicHash>

DBHelper* DBHelper::dbHelper=NULL;

DBHelper::DBHelper()
{

}

bool DBHelper::isOpen()
{
    return m_db.isOpen();
}

bool DBHelper::connectToConfigedDB()
{
    //从配置文件中读取
    //这里应该读取一个xml文件吧
    //xml文件的位置绝对是写死的
    DBConnectPara para;
    para.driver = "QSQLITE";
    para.databaseName = QApplication::applicationDirPath() + "/shoecheck.db";

    return connectToDataBase(para);
}

bool DBHelper::initialFillTheEmptyDB()
{
    bool success = false;
    // you should check if args are ok first...

    QString name = "wxk";

    QString passwdMD5;
    QString pwd="123";
    QByteArray bb = QCryptographicHash::hash(pwd.toUtf8(), QCryptographicHash::Md5 );
    passwdMD5.append(bb.toHex());

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO users (name, passwd) VALUES (:name, :passwd)");
    query.bindValue(":name", name);
    query.bindValue(":passwd", passwdMD5);

    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "addPerson error:  "
                 << query.lastError();
    }

    return success;
}

bool DBHelper::connectToDataBase(DBConnectPara para)
{
    if(m_db.isOpen())
        m_db.close();

    QString driver = para.driver;

    if(driver == "QSQLITE")
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName(para.databaseName);
    }
    else if(driver == "QMYSQL")
    {
        m_db = QSqlDatabase::addDatabase("QMYSQL");

        m_db.setHostName(para.hostName);
        m_db.setPort(para.port);
        m_db.setDatabaseName(para.databaseName);
        m_db.setUserName(para.userName);
        m_db.setPassword(para.userPasswd);
    }
    else
    {
        return false;
    }

    return m_db.open();
}

bool DBHelper::validateUser(QString name, QString passwd, User &user)
{
    QString passwdMD5;
    QByteArray bb = QCryptographicHash::hash(passwd.toUtf8(), QCryptographicHash::Md5 );
    passwdMD5.append(bb.toHex());

    QSqlQuery query(m_db);
    query.prepare("select * from users where name=:username and passwd=:passwd");
    query.bindValue(":username", name);
    query.bindValue(":passwd", passwdMD5);

    query.exec();
    if(query.next())
    {
        int id = query.value(0).toInt();
        QString userName = query.value(1).toString();
        QString password = query.value(2).toString();
        QString telephone = query.value(3).toString();
        int role = query.value(4).toInt();

        user.setId(id);
        user.setName(userName);
        user.setPasswd(password);
        user.setTelephone(telephone);
        user.setRole((UserRole)role);

        return true;
    }
    else
    {
        return false;
    }
}

DBHelper *DBHelper::getDBHelperInstance()
{
    if(dbHelper == NULL)
        dbHelper = new DBHelper;
    return dbHelper;
}

