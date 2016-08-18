资源名称： Qt Sqlite加密数据库驱动源代码

Tag：
Qt Sqlite 加密 驱动 Driver

资源描述：

    这是我工作了一天的成果，压缩包内包括Qt sqlite加密驱动所有的代码，以及一个调用例程，还有一个sqlite3shell.exe工具，用于加密数据库命令行下的分析。
    使用这个加密驱动很简单，只需以下3步：
    1. 将驱动的代码复制到你的app文件夹（共2个文件夹）
    2. 在app的pro文件中加入
        include(wxsqlite3/wxsqlite3.pri)
        include(zsqlitecipherdriver/zsqlitecipherdriver.pri)
    3. 在需要的地方加入#include "zsqlitecipherdriver.h"，这样就可以使用ZSQLiteCipherDriver类了，这个类是继承自QSqlDriver。所以可以传递给
QSqlDatabase::addDatabase。

    详细的可以查看压缩包内源码。之后，main函数就可以这么使用sqlite的加密驱动：
ZSQLiteCipherDriver *driver = new ZSQLiteCipherDriver();
QSqlDatabase db = QSqlDatabase::addDatabase(driver);
db.setDatabaseName("test.db");
db.setPassword("123");
db.open();
...

    加密驱动的稳定性没有问题，是我从Qt的开源代码中，找到Sqlite没加密的驱动部分，然后修改的。修改的内容不多，最重要的是在数据库的open时，加入了sqlite3_key的调用，实现加密。
    底层的加密实现，是来自wxsqlite3-3.0.6。这个我修改了一个宏定义，让其加密方式采用了AES256，而不是原来的AES128。
    例程中包括了3个实用的函数，分别用来以某一密码打开或创建一个数据库，判断数据库是否处于解密状态，以及修改数据库密码。
    sqlite3shell.exe跟官方提供的sqlite3.exe使用方法一样。只不过对于加密数据库，需要在对数据库进行任何操作前，先执行“PRAGMA key=xxx;”。通过这种方式输入数据库密码。检验之前的密码是否正确可以在命令行中键入“.databases”，如果没有错误提示，那就是解密成功了；如果密码错误，只能关闭sqlite3shell.exe，从头尝试了。

    虽然这个资源，要的分数确实有点多，不过评价之后就能返还的。我相信这个资源值这个价值！下载后在Qt5上可以直接编译。不需要任何修改。Qt4上没试过，不承诺一定可用，但是应该没问题。
