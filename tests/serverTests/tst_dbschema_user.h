#ifndef TST_SBSCHEMA_USER_H
#define TST_SBSCHEMA_USER_H

#include <QObject>
#include <QTest>
#include <QSql>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "dbcreator.h"

#include "pginterface.h"

class tst_dbschema_user : public QObject
{
    Q_OBJECT
public:
    explicit tst_dbschema_user(QObject *parent = 0);
    ~tst_dbschema_user(){
        delete database;
    }
    void removeTable(QString tblName);
signals:

public slots:

private slots:
    void init();
    void initTestCase();
    void cleanupTestCase();
    void cleanup();

    void createUserShoudGiveNewId();
    void everyCreatedUser_shoudHaveUniqueId();
    void getBadUser_returnsEmptyUser();
    void createdUser_getsRegisterDate();
    void createUserWithSameNameOrEmail_throwaException();
    void createUserWithoutNeededFields_throwsException();
    void getUser_getsUser();

//    void addUserBenchmark();
    void deleteUser_deletesUser();

    void checkPassword_returnFalseIfWrongPassword();

    void addMagazineToUser();

//    void addMeanyStoragesToUser();
private:
    QSqlQuery *query;
    QSqlDatabase db;
    DbCreator *creator;

    PgInterface *database;

    int currentID;
    int currentEmail;
    QString getUniqueName();
    QString getUniqueEmail();
    QString getUniqueStorage();
};

#endif // TST_SBSCHEMA_USER_H
