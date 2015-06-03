#ifndef TST_DBSCHEMA_ITEM_H
#define TST_DBSCHEMA_ITEM_H

#include <QObject>
#include <QTest>
#include <QSql>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "dbcreator.h"
#include "messages/group.h"
#include "messages/parameter.h"
#include "pginterface.h"

class tst_dbschema_item : public QObject
{
    Q_OBJECT
public:
    explicit tst_dbschema_item(QObject *parent = 0);

signals:

public slots:

private slots:
    void initTestCase();
    void cleanupTestCase();
    void saveItemWithBasicInfo();
private:
    QSqlQuery *query;
    QSqlDatabase db;
    DbCreator *creator;
    PgInterface *database;
};

#endif // TST_DBSCHEMA_ITEM_H
