#include "tst_dbschema_user.h"

#include "messages/user.h"

tst_dbschema_user::tst_dbschema_user(QObject *parent) :
    QObject(parent), currentID(0), currentEmail(0)
{
}

void tst_dbschema_user::init()
{

}

void tst_dbschema_user::initTestCase()
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
    QTest::qSleep(10);
    if(!query->exec("create schema public;")){
        qDebug() << query->lastError().text();
    }
    creator = new DbCreator(this);
    creator->initialize_database();

    database = new PgInterface(db.connectionName());
}

void tst_dbschema_user::removeTable(QString tblName)
{
    if(!query->exec("DROP table " + tblName + ";")){
        qDebug() << query->lastError().text();
    }
}

void tst_dbschema_user::cleanupTestCase()
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

void tst_dbschema_user::cleanup()
{

}

void tst_dbschema_user::createUserShoudGiveNewId()
{
    User u;
    u.set_name(QStringLiteral("zawisza"));
    u.set_email(QStringLiteral("cszawisza@gmail.com"));

    QVERIFY(database->addUser(u,"MY NEW PASSWORD! FUCK YEAH") != 0 );
}

void tst_dbschema_user::everyCreatedUser_shoudHaveUniqueId()
{
    User u1, u2, u3;
    u1.set_name(getUniqueName());
    u1.set_email(getUniqueEmail());
    u2.set_name(getUniqueName());
    u2.set_email(getUniqueEmail());
    u3.set_name(getUniqueName());
    u3.set_email(getUniqueEmail());

    uint startId = database->addUser(u1,"passwd");
    QVERIFY(database->addUser(u2,"passwd") == startId+1);
    QVERIFY(database->addUser(u3,"passwd") == startId+2);
}

void tst_dbschema_user::getBadUser_returnsEmptyUser()
{
    User u = database->getUserByName("bad_user_zse");
    QVERIFY(u.has_id()==true);
    QVERIFY(u.id() == 0);
}

void tst_dbschema_user::createdUser_getsRegisterDate()
{
    User u1, u2;
    u1.set_name(QStringLiteral("exampleUser1"));
    u1.set_email(QStringLiteral("exampleuser1@example.ex"));

    database->addUser(u1,"examplePasswd");
    QVERIFY(u2.has_registrationdate()==false);
    u2 = database->getUserByName(u1.getName());
    QVERIFY(u2.has_registrationdate() );
}

void tst_dbschema_user::createUserWithSameNameOrEmail_throwaException()
{
    User u1,u2;

    u1.set_name(QStringLiteral("admin"));
    u1.set_email(QStringLiteral("sdfsdfsdfs@gmail.com"));
    u2.set_name(QStringLiteral("noname"));
    u2.set_email(QStringLiteral("b.w@linux.pl"));

    QVERIFY_EXCEPTION_THROWN(database->addUser(u1,"passwordd"), QSqlError);
    QVERIFY_EXCEPTION_THROWN(database->addUser(u2,"passwordd"), QSqlError);
}

void tst_dbschema_user::createUserWithoutNeededFields_throwsException()
{
    User u;
    u.set_name( getUniqueName() );
    QVERIFY_EXCEPTION_THROWN(database->addUser(u,"passwordd"), QSqlError);
}

void tst_dbschema_user::getUser_getsUser()
{
    User u;
    u.set_name(getUniqueName());
    u.set_email(getUniqueEmail());
    u.set_phonenumber(QStringLiteral("123123123"));
    u.set_address(QStringLiteral("address USA"));

    database->addUser(u,"passwd");

    User u2 = database->getUserByName( u.getName() );

    QVERIFY(u.getName() == u2.getName());
    QVERIFY(u.getEmail() == u2.getEmail());
    QVERIFY(u.getPhoneNumber() == u2.getPhoneNumber());
    QVERIFY(u.getAddress() == u2.getAddress());

    QVERIFY(u2.has_registrationdate());
    QVERIFY(u2.getStorage()->getID() != 0);
}

//void tst_dbschema_user::addUserBenchmark()
//{
//    QBENCHMARK{
//        User u;
//        u.set_name(getUniqueName());
//        u.set_email(getUniqueEmail());
//        u.setPhoneNumber("123123123");
//        u.setAddress("address USA");
//        database->addUser(u,"passwd");
//    }
//}

void tst_dbschema_user::deleteUser_deletesUser()
{
    User u;
    u.set_name(getUniqueName());
    u.set_email(getUniqueEmail());
    database->addUser(u,"passwd");
    User u2 = database->getUserByName( u.getName() );
    database->deleteUser( u );
    User u3 = database->getUserByName( u.getName() );

    QVERIFY(u2.id() != 0 );
    QVERIFY(u3.id() == 0 );
}

void tst_dbschema_user::checkPassword_returnFalseIfWrongPassword()
{
    User u;
    u.set_name(getUniqueName());
    u.set_email(getUniqueEmail());

    database->addUser(u,"good");

    QVERIFY(database->checkUserPassword(u,"BAD") == false);
    QVERIFY(database->checkUserPassword(u,"good") == true);

    u.set_name(getUniqueName());
    QVERIFY(database->checkUserPassword(u,"BAD") == false);
    QVERIFY(database->checkUserPassword(u,"good") == false);
}

void tst_dbschema_user::addMagazineToUser()
{
    User u;
    u.set_name( getUniqueName() );
    u.set_email( getUniqueEmail() );

    Storage s;
    s.set_name("someName");

    u.set_id(database->addUser(u,"asdadscf" ));
    s.setID(database->addStorage( s ));

    database->linkStorageToUser(u, s);
    u.addStorage(s);

    QVERIFY(u.getStoragesList().size() == 2 );
}

//void tst_dbschema_user::addMeanyStoragesToUser()
//{
//    User u;
//    u.set_name( getUniqueName() );
//    u.set_email( getUniqueEmail() );
//    u.set_id(database->addUser(u,"asdadscf" ));
//    //    for(int i=0;i<1000; i++){
//    Storage s;
//    s.set_name( getUniqueStorage() );
//    s.setID(database->addStorage( s ));
//    database->linkStorageToUser(u, s);

//    QVERIFY(u.getStoragesList().size() == 2 );
//    //    }
//}

QString tst_dbschema_user::getUniqueName()
{
    return QString("exampleUniqueUser") + QString::number(currentID++);
}

QString tst_dbschema_user::getUniqueEmail()
{
    return QString("exampleUniqueEmail")
            + QString::number(currentID++)
            + QString("@aa.aa");
}

QString tst_dbschema_user::getUniqueStorage()
{
    return QString("storage") + QString::number(currentID++);
}



