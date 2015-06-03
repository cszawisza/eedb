#include "tst_magazine.h"

tst_Magazine::tst_Magazine(QObject *parent):
    QObject(parent)
{
}

void tst_Magazine::init()
{
    mag = new Storage();
}

void tst_Magazine::cleanup()
{
    delete mag;
}

void tst_Magazine::storage_shoudHaveName()
{
    QVERIFY (mag->getName() == "" );
}

void tst_Magazine::setName_shoudSetName()
{
    mag->set_name("magazynek");
    QVERIFY (mag->getName() == "magazynek");
}

void tst_Magazine::storage_shoudHaveID()
{
    QVERIFY (mag->getID() == 0 );
}
