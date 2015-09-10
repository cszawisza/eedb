#ifndef TST_SERVERTESTS_H
#define TST_SERVERTESTS_H

#include <QString>
#include <QtTest>
#include <QHostAddress>

#include <qcatalogserverworker.h>

class tst_ServerWorkerTests : public QObject
{
    Q_OBJECT

public:
    tst_ServerWorkerTests();

    void waitForSignal(QSignalSpy spy);
    void login(QString name, QString pass);
    void logout();
public slots:

    void onResponseAvalible(QByteArray ba);
private Q_SLOTS:
    void init();
    void initTestCase();
    void cleanupTestCase();
    void cleanup();

    void serverDontRespondToCorruptedMessage();

    void addBasicUserToServer();

    void loginToServer();
    void loginChangesUserStatus();
    void logoutFromServer();

    void logoutWhileNotLoged();
    void loginToServerBadPasswd();
    void loginToServerBadUser();
    void addFullUserToServer();
    void loginGetsUserInformation();

    void addParameter_worksOnlyIfUserIsOnline();
    void addParameter_addsNewParameter();
    void addSameParameter_givesError();

    void addGroup_addsGroup();

private:

    QCatalogServerWorker *worker;
    MessagesContainer *mc;
    QByteArray *binaryMessage;

    QSignalSpy *responseSignalSpy;
};

#endif // TST_SERVERTESTS_H
