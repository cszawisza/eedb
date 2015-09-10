#include <QVector>
#include <QObject>
#include <QTest>
#include <QTimer>
#include <QCoreApplication>

#include "tst_servertests.h"
#include "tst_user.h"
#include "tst_magazine.h"
#include "tst_dbschema_user.h"
#include "tst_dbschema_storage.h"
#include "tst_item.h"
#include "tst_itempackage.h"
#include "tst_dbschema_groups.h"
#include "tst_parameterconfig.h"
#include "tst_dbschema_item.h"
#include "tst_messagecontainer.h"

QVector<int> testsResult;

void addTest(QObject *o){
    static int testNum=0;
    testsResult.append( QTest::qExec(o, qApp->arguments()) << testNum++ );
    delete o;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("ekatalog_tests"); /// TODO change to QSettings
    db.setHostName("localhost");
    db.setUserName("postgres");
    db.setPassword("postgres");

    addTest(new tst_user);
    addTest(new tst_Magazine );
    addTest(new tst_dbschema_groups);
    addTest(new tst_dbschema_storage );
    addTest(new tst_dbschema_user);
    addTest(new tst_dbschema_item );
    addTest(new tst_item);
    addTest(new tst_ItemPackage);
    addTest(new tst_ParameterConfig );
    addTest(new tst_MessageContainer);
    addTest(new tst_ServerWorkerTests);

    QTimer::singleShot(1,&a,SLOT(quit()));

    quint64 res = 0;
    for(int i=0;i<testsResult.size();i++){
        res += testsResult.at(i);
    }

    return a.exec() | res;
}

