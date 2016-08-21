#include "dbhelper.h"
#include <QApplication>
#include <QtSql>
#include <QString>
#include <QCryptographicHash>

#define USE_QSQLITE

#pragma execution_character_set("utf-8")


DBHelper* DBHelper::dbHelper=NULL;

DBHelper::DBHelper()
{

}

bool DBHelper::isOpen()
{
    return m_db.isOpen();
}

QSqlError DBHelper::createConnection()
{
    DBConnectPara para;
#ifdef USE_QSQLITE
    para.driver = "QSQLITE";
    para.databaseName = QApplication::applicationDirPath() + "/shoecheck.db";
#else

#endif
    return connectToDataBase(para);
}

QString DBHelper::getMD5String(QString readableString)
{
    return QString().append(QCryptographicHash::hash(readableString.toUtf8(), QCryptographicHash::Md5).toHex());
}

QSqlError DBHelper::connectToDataBase(DBConnectPara para)
{
    m_db = QSqlDatabase::addDatabase(para.driver);
    m_db.setHostName(para.hostName);
    m_db.setPort(para.port);
    m_db.setDatabaseName(para.databaseName);
    m_db.setUserName(para.userName);
    m_db.setPassword(para.userPasswd);

    if(!m_db.open())
        return m_db.lastError();

    QStringList tables = m_db.tables();
    if (tables.contains("userroles", Qt::CaseInsensitive)
        && tables.contains("users", Qt::CaseInsensitive))
        return QSqlError();

    //初始化用户数据库
    QSqlQuery q(m_db);
    if( !q.exec("create table userroles(id integer primary key, name varchar(20))") )
        return q.lastError();

    q.exec("insert into userroles values(1, 'admin')");
    q.exec( "insert into userroles values(2, 'normal')" );

    if( !q.exec("create table users(id integer primary key, name varchar(20), passwd varchar(32), role integer, telephone varchar(20) )") )
        return q.lastError();

    QString name;
    QString passwdMD5;
    q.prepare( "insert into users(name, passwd, role) values(:name, :passwdmd5, :role)" );

    name = QString("wangxk");
    passwdMD5 = getMD5String("123");

    q.bindValue(":name", name);
    q.bindValue(":passwdmd5", passwdMD5);
    q.bindValue(":role", 1);
    q.exec();

    name = QString("zhangwl");
    passwdMD5 = getMD5String("123");

    q.bindValue(":name", name);
    q.bindValue(":passwdmd5", passwdMD5);
    q.bindValue(":role", 2);
    q.exec();

    //初始化检测项目数据库
    if( !q.exec("create table shoetypes(id integer primary key, name varchar(50))") )
        return q.lastError();

    q.prepare( "insert into shoetypes(name) values(:name)" );
    name = QString("成品皮鞋");
    q.bindValue(":name", name);
    q.exec();

    name = QString("军用皮鞋");
    q.bindValue(":name", name);
    q.exec();


    if( !q.exec("create table errortypes(id integer primary key, name varchar(30))") )
        return q.lastError();

    q.prepare( "insert into errortypes(name) values(:name)" );
    QStringList errortypes = QStringList()<< "材料" << "缝帮" << "绷帮" << "制底" << "整理修饰";
    foreach (QString errortype, errortypes) {
        name = errortype;
        q.bindValue(":name", name);
        q.exec();
    }

    if( !q.exec("create table erroritems(id integer primary key, name varchar(30))") )
        return q.lastError();
    QStringList erroritems = QStringList()
                             << "皮伤" << "松面"
                             << "线道不规" << "针码大小" << "豁针断线" << "汽眼铆钉"
                             << "吊正歪" << "后帮高低" << "前帮长短" <<  "脱壳里不展" << "包头主跟"
                             << "底偏歪" << "开胶欠胶" << "冲胶不齐" << "子口砂断线"
                             << "碰擦伤" << "内有卡钉" << "帮里不净" << "主跟有楞" << "错号" << "变形" << "子口胶污";
    q.prepare( "insert into erroritems(name) values(:name)" );
    foreach (QString erroritem, erroritems) {
        name = erroritem;
        q.bindValue(":name", name);
        q.exec();
    }

    if( !q.exec("create table detectiontotal(id integer primary key, shoetypeid integer, errortypeid integer, erroritemid integer)") )
        return q.lastError();

    q.prepare( "insert into detectiontotal(shoetypeid, errortypeid, erroritemid) values(:shoetypeid, :errortypeid, :erroritemid)" );
    {
        q.bindValue(":shoetypeid", 1);
        q.bindValue(":errortypeid", 1);
        q.bindValue(":erroritemid", 1);
        q.exec();

        q.bindValue(":shoetypeid", 2);
        q.bindValue(":errortypeid", 1);
        q.bindValue(":erroritemid", 1);
        q.exec();

    }

    return QSqlError();
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
        int role = query.value(3).toInt();
        QString telephone = query.value(4).toString();

        user.setId(id);
        user.setName(userName);
        user.setPasswd(password);
        user.setTelephone(telephone);
        user.setRole(role);

        return true;
    }
    else
    {
        return false;
    }
}

bool DBHelper::updateUserPasswd(QString name, QString newPasswd)
{
    QString passwdMD5;
    QByteArray bb = QCryptographicHash::hash(newPasswd.toUtf8(), QCryptographicHash::Md5 );
    passwdMD5.append(bb.toHex());

    QSqlQuery query(m_db);
    query.prepare("UPDATE users SET passwd=:newPasswd WHERE name=:userName");
    query.bindValue(":newPasswd", passwdMD5);
    query.bindValue(":userName", name);
    query.exec();


    bool result = query.numRowsAffected() > 0;
    if(!result)
    {
        qDebug() << "update passwd failed:  "
                 << query.lastError();
    }
    return result;
}

DBHelper *DBHelper::getDBHelperInstance()
{
    if(dbHelper == NULL)
        dbHelper = new DBHelper;
    return dbHelper;
}

