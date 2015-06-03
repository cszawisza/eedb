#include "tst_dbschema_groups.h"

tst_dbschema_groups::tst_dbschema_groups(QObject *parent) :
    QObject(parent)
{
}

void tst_dbschema_groups::init()
{

}

void tst_dbschema_groups::initTestCase()
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
    database->setActiveUser(1); /// TODO get admin ID
}

void tst_dbschema_groups::cleanupTestCase()
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
    delete database;
}

void tst_dbschema_groups::cleanup()
{

}

void tst_dbschema_groups::addGroupToDatabase_shoudSaveGroupWithAllInformation()
{
    Group g;
    g.set_parentid(1);
    g.set_name("first group");
    g.set_description("description 1");
    g.setAllowItems(true);
    g.setAllowRecipe(true);

    g.set_id(database->addGroup(g));

    QVERIFY(g.id() != 0);
}

void tst_dbschema_groups::addMeanygroups_givesSerialIDNumbers()
{
    Group g, g2;
    g.set_parentid(1);
    g.set_name("second group");
    g.set_description("description 2");
    g.setAllowItems(true);
    g.setAllowRecipe(true);

    g2.set_parentid(1);
    g2.set_name("third group");
    g2.set_description("description 3");
    g2.setAllowItems(true);
    g2.setAllowRecipe(false);

    g.set_id(database->addGroup(g));
    g2.setID(database->addGroup(g2));

    QVERIFY(g2.getID() == g.getID() + 1);
}

void tst_dbschema_groups::databaseShoudAllowCreateGroupsWithSameNameAndDifferentParent()
{
    Group primaryGroup1, primaryGroup2, child1, child2;
    primaryGroup1.set_parentid(1);
    primaryGroup1.set_name("primary group 1");
    primaryGroup1.set_description("description for primary 1");
    primaryGroup1.setAllowItems(true);
    primaryGroup1.setAllowRecipe(true);
    primaryGroup1.set_id(database->addGroup(primaryGroup1));

    primaryGroup2.set_parentid(1);
    primaryGroup2.set_name("primary group 2");
    primaryGroup2.set_description("description for primary 2");
    primaryGroup2.setAllowItems(true);
    primaryGroup2.setAllowRecipe(true);
    primaryGroup2.set_id(database->addGroup(primaryGroup2));

    child1.set_parentid(primaryGroup1.id() );
    child1.set_name("CHILD");
    child1.setAllowItems(true);
    child1.setAllowRecipe(true);
    child1.set_id(database->addGroup(child1));

    child2.set_parentid(primaryGroup2.id() );
    child2.set_name("CHILD");
    child2.setAllowItems(true);
    child2.setAllowRecipe(true);
    child2.set_id(database->addGroup(child2));

    QVERIFY(child1.id() != 0);
    QVERIFY(child2.id() != 0);
    QVERIFY(child1.id() != child2.id());
}

void tst_dbschema_groups::databaseThrowsExceptionWhenDoubleGroupAdd()
{
    Group primaryGroup1;
    primaryGroup1.set_parentid(1);
    primaryGroup1.set_name("some group");
    primaryGroup1.setAllowItems(true);
    primaryGroup1.setAllowRecipe(true);
    primaryGroup1.set_id(database->addGroup(primaryGroup1));
    QVERIFY_EXCEPTION_THROWN(primaryGroup1.set_id(database->addGroup(primaryGroup1)), QSqlError );
}

void tst_dbschema_groups::linkGroupWithParameter_linksGroupWithParameter()
{


    Parameter p1, p2;
    p1.set_name("Parameter1");
    p1.set_symbol("P1");
    p1.mutable_config()->set_type(ParameterConfig::STRING );
    if(p1.IsInitialized() ){
        qDebug()<< "is initialized";
    }

    p2.set_name("Parameter2");
    p2.set_symbol("P2");
    p2.mutable_config()->set_defaultvalue( QString::number(21).toStdString() );
    p2.mutable_config()->set_type(ParameterConfig::INT);

    database->addParameter(p1);
    database->addParameter(p2);

    Group g;
    g.set_parentid(1);
    g.set_name("Parameter_test");
    g.setAllowItems(true);
    g.setAllowRecipe(true);
    g.set_id(database->addGroup(g));
    g.add_parameter(p1);
    g.add_parameter(p2);

    QVERIFY(g.getParameters().size() == 2);
}

void tst_dbschema_groups::getGroup_getsGroupInfo()
{
    Group g;

    g.MergeFrom(database->getGroup(1));

    QVERIFY(g.id() == 1);
    QVERIFY(g.parentid() == 0);
    QVERIFY(g.name() == "ROOT");
    QVERIFY(g.description()== "The base group for all groups");
    QVERIFY(g.allowitems() == false);
    QVERIFY(g.allowsets() == false);
}

void tst_dbschema_groups::getGroup_getsGroupParameters()
{


    Parameter p1, p2, p3, p4;
    p1.set_name("Parameter5");
    p1.set_symbol("P5");
    p1.mutable_config()->set_type(ParameterConfig::STRING);

    p2.set_name("Parameter6");
    p2.set_symbol("P2");
    p2.mutable_config()->set_defaultvalue( QString::number(21).toStdString() );
    p2.mutable_config()->set_type(ParameterConfig::INT);
    p2.mutable_config()->set_maxvalue(230);
    p2.mutable_config()->set_minvalue(-23);

    p3.set_name("Parameter7");
    p3.set_symbol("P3");
    p3.mutable_config()->set_defaultvalue(QString::number(0.00001).toStdString() );
    p3.mutable_config()->set_type(ParameterConfig::DOUBLE );
    p3.mutable_config()->set_maxvalue(1e12);
    p3.mutable_config()->set_minvalue(1e-12);

    p4.set_name("Parameter8");
    p4.set_symbol("P4");
    p4.mutable_config()->set_defaultvalue(" some custom parameter ");
    p4.mutable_config()->set_type(ParameterConfig::STRING);

    database->addParameter(p1);
    database->addParameter(p2);
    database->addParameter(p3);
    database->addParameter(p4);

    Group g;
    g.set_parentid(1);
    g.set_name("group_test");
    g.setAllowItems(true);
    g.setAllowRecipe(true);
    g.add_parameter(p1);
    g.add_parameter(p2);
    g.add_parameter(p3);
    g.add_parameter(p4);
    database->addGroup(g);

    Group g2;
    g2.MergeFrom(database->getGroup( g.id() ));
    QVERIFY(g2.getParameters().size() == 4 );
}
