��Դ���ƣ� Qt Sqlite�������ݿ�����Դ����

Tag��
Qt Sqlite ���� ���� Driver

��Դ������

    �����ҹ�����һ��ĳɹ���ѹ�����ڰ���Qt sqlite�����������еĴ��룬�Լ�һ���������̣�����һ��sqlite3shell.exe���ߣ����ڼ������ݿ��������µķ�����
    ʹ��������������ܼ򵥣�ֻ������3����
    1. �������Ĵ��븴�Ƶ����app�ļ��У���2���ļ��У�
    2. ��app��pro�ļ��м���
        include(wxsqlite3/wxsqlite3.pri)
        include(zsqlitecipherdriver/zsqlitecipherdriver.pri)
    3. ����Ҫ�ĵط�����#include "zsqlitecipherdriver.h"�������Ϳ���ʹ��ZSQLiteCipherDriver���ˣ�������Ǽ̳���QSqlDriver�����Կ��Դ��ݸ�
QSqlDatabase::addDatabase��

    ��ϸ�Ŀ��Բ鿴ѹ������Դ�롣֮��main�����Ϳ�����ôʹ��sqlite�ļ���������
ZSQLiteCipherDriver *driver = new ZSQLiteCipherDriver();
QSqlDatabase db = QSqlDatabase::addDatabase(driver);
db.setDatabaseName("test.db");
db.setPassword("123");
db.open();
...

    �����������ȶ���û�����⣬���Ҵ�Qt�Ŀ�Դ�����У��ҵ�Sqliteû���ܵ��������֣�Ȼ���޸ĵġ��޸ĵ����ݲ��࣬����Ҫ���������ݿ��openʱ��������sqlite3_key�ĵ��ã�ʵ�ּ��ܡ�
    �ײ�ļ���ʵ�֣�������wxsqlite3-3.0.6��������޸���һ���궨�壬������ܷ�ʽ������AES256��������ԭ����AES128��
    �����а�����3��ʵ�õĺ������ֱ�������ĳһ����򿪻򴴽�һ�����ݿ⣬�ж����ݿ��Ƿ��ڽ���״̬���Լ��޸����ݿ����롣
    sqlite3shell.exe���ٷ��ṩ��sqlite3.exeʹ�÷���һ����ֻ�������ڼ������ݿ⣬��Ҫ�ڶ����ݿ�����κβ���ǰ����ִ�С�PRAGMA key=xxx;����ͨ�����ַ�ʽ�������ݿ����롣����֮ǰ�������Ƿ���ȷ�������������м��롰.databases�������û�д�����ʾ���Ǿ��ǽ��ܳɹ��ˣ�����������ֻ�ܹر�sqlite3shell.exe����ͷ�����ˡ�

    ��Ȼ�����Դ��Ҫ�ķ���ȷʵ�е�࣬��������֮����ܷ����ġ������������Դֵ�����ֵ�����غ���Qt5�Ͽ���ֱ�ӱ��롣����Ҫ�κ��޸ġ�Qt4��û�Թ�������ŵһ�����ã�����Ӧ��û���⡣
