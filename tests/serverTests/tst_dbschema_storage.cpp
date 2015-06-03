#include "tst_dbschema_storage.h"

tst_dbschema_storage::tst_dbschema_storage(QObject *parent) :
    QObject(parent)
{
}

void tst_dbschema_storage::init()
{

}

void tst_dbschema_storage::initTestCase()
{

    db = QSqlDatabase::database();
    query = new QSqlQuery(db);
    if(!db.open()){
        qDebug()<<db.lastError().text();
    }

    query->exec("CREATE DATABASE ekatalog_tests;");

    db.close();
    db.setDatabaseName("ekatalog_tests");

    if(!db.open()){
        qDebug()<<db.lastError().text();
    }
    if(!query->exec("DROP schema public cascade;")){
        qDebug() << query->lastError().text();
    }
    if(!query->exec("create schema public;")){
        qDebug() << query->lastError().text();
    }

    creator = new DbCreator(this);
    creator->initialize_database();
    delete creator;
    database = new PgInterface(db.connectionName());
}
void tst_dbschema_storage::removeTable(QString tblName)
{
    if(!query->exec("DROP table " + tblName + ";")){
        qDebug() << query->lastError().text();
    }
}
void tst_dbschema_storage::cleanupTestCase()
{

    if(!query->exec("DROP schema public cascade;")){
        qDebug() << query->lastError().text();
    }
    if(!query->exec("create schema public;")){
        qDebug() << query->lastError().text();
    }

    if (db.isOpen()){
        db.close();
    }
    delete query;
}

void tst_dbschema_storage::cleanup()
{

}

void tst_dbschema_storage::createStorege_givesAddData()
{
    uint id = 0;
    Storage s;
    s.set_name("some");
    s.setID(database->addStorage(s));
    QVERIFY( s.getID() != id);
    QVERIFY( s.has_name() );
}

void tst_dbschema_storage::createMessage_divesNotNullArray()
{
    Storage s;
    s.set_name("some2");
    s.setID(1000);
    s.setCreationDate(QDateTime::currentDateTime());

    QByteArray ba = s.toArray();
    QVERIFY(ba.size()>0);
}

void tst_dbschema_storage::fromArray_formsProperStorage()
{

    Storage s;
    QString str;
    for(int i=0;i<1000;i++){
        str.append("String");
    }
    s.set_name(str);
    s.setID(1000);
    s.setCreationDate(QDateTime::currentDateTime());
    QByteArray ba = s.toArray();
    QVERIFY(ba.size()>0);

    Storage s2;
    s2.fromArray(ba);

    QVERIFY(s2.getName() == s.getName() );
    QVERIFY(s2.getID() == s.getID() );
    QVERIFY(s2.getCreationDate() == s.getCreationDate() );

}

void tst_dbschema_storage::fromArray_formsProperStorage2()
{
    QByteArray *ba = new QByteArray();
    Storage s;
    QString str;
    for(int i=0;i<1000;i++){
        str.append("String");
    }
    s.set_name(str);
    s.setID(1000);
    s.setCreationDate(QDateTime::currentDateTime());
    s.toArray(ba);
    QVERIFY(ba->size()>0);

    Storage s2;
    s2.fromArray(ba);

    QVERIFY(s2.getName() == s.getName() );
    QVERIFY(s2.getID() == s.getID() );
    QVERIFY(s2.getCreationDate() == s.getCreationDate() );
    delete ba;
}
