#include <QCoreApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QFile>

/**
 * @brief isDbDecrypted
 * Sqlite似乎没有提供判断密码是否正确的函数，可用本函数检查一个打开了的数据库
 * 是否被成功解密了。
 *
 * @param db
 * @return
 */
bool isDbDecrypted(QSqlDatabase &db)
{
    QSqlQuery query(db);
    return query.exec("select name,sql from sqlite_master"
                      " where type = 'table'");
}

/**
 * @brief changePassword
 * 对已经成功打开了的数据库修改密码。注意：
 * 1. 如果数据库还未用正确密码打开，是无法使用本函数修改密码的。
 * 2. 如果数据库文件比较大，修改密码可能需要消耗比较长的时间（需要将所有的数据重新加密）。
 * 3. 密码支持的字符，这里未测试，但是单引号肯定是不能用在密码中的。
 *
 * @param db
 * @param newPassword
 * @return 返回密码是否修改成功
 */

bool changePassword(
        QSqlDatabase &db, const QString &newPassword)
{
    QSqlQuery query(db);
    return query.exec(QString("PRAGMA rekey='%1';").arg(newPassword));
}


/**
 * @brief openOrCreateDb
 * 打开已存在的数据库，或新建未存在的数据库。
 * 本函数认为大小等于0的文件等同于不存在
 *
 * @param db
 * @param dbName
 * @param password
 * @return
 *          0   表示密码错误，或该文件不是数据库文件
 *          1   表示新建成功
 *          2   表示打开成功
 *          -1  表示新建失败
 *          -2  表示打开失败
 */
int openOrCreateDb(
        QSqlDatabase &db,
        const QString &dbName,
        const QString &password)
{
    QFile file(dbName);
    //判断文件是否存在并且文件大于0。此处认为大小等于0的文件等同于不存在
    bool isDbFileExists = file.exists() && (file.size() > 0);

    db.setDatabaseName(dbName);
    db.setPassword(password);

    if (!db.open()) return isDbFileExists ? -2 : -1;

    if (isDbFileExists && !isDbDecrypted(db))
    {
        db.close();//要关闭数据库，这样下一次的db.setPassword()才有用
        return 0;
    }
    return isDbFileExists ? 2 : 1;
}


void insertValuesIntoDb(QSqlDatabase &db, int count)
{
    QSqlQuery query(db);
    query.exec("create table mapping (id int, name varchar)");
    for (int i = 0; i < count; i++)
    {
        query.exec(QString("insert into mapping values (%1, '%2')")
                   .arg(i).arg(i*i));
    }
}

void readAndPrintDb(QSqlDatabase &db)
{
    QSqlQuery query(db);
    query.exec("select id, name from mapping");
    while (query.next())
    {
        int a = query.value(0).toInt();
        QString b = query.value(1).toString();
        qDebug() << a << "*" << a << "=" << b;
    }
}

#include "zsqlitecipherdriver.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    ZSQLiteCipherDriver *driver = new ZSQLiteCipherDriver();
    QSqlDatabase db = QSqlDatabase::addDatabase(driver);
    QString pwd[] = {"zhouqian", "zq", "aaa", "zhouqian", "bbb"};
    for (int i = 0; i < 5; i ++)
    {
        switch(openOrCreateDb(db, "test.db", pwd[i]))
        {
        case -2:
        case -1:
            qDebug()<<"数据库打开或新建失败！";
            break;
        case 0:
            qDebug()<<"密码错误！"<<pwd[i];
            break;
        case 1:
            qDebug()<<"数据库新建成功，密码："<<pwd[i];
            insertValuesIntoDb(db, 5);
            qDebug()<<"插入数据完成。";
            //no break;
        case 2:
            qDebug()<<"数据库打开成功，密码："<<pwd[i];
            readAndPrintDb(db);
            break;
        }
        db.close();
        qDebug() << "第" << i+1 << "次数据库操作结束\n";
    }

    //qDebug()<<changePassword(db, "");

    delete driver;
    qDebug()<<"App End";
    return app.exec();
}
