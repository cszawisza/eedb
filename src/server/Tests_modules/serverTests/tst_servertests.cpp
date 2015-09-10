#include "tst_servertests.h"

#include "messages/userregistrationmessage.h"
#include "messages/parameter.h"
#include "messages/loginrequest.h"
#include "messages/group.h"

#include <QSignalSpy>

bool signalSign = false;
tst_ServerWorkerTests::tst_ServerWorkerTests()
{
}

void tst_ServerWorkerTests::onResponseAvalible(QByteArray ba)
{
    binaryMessage->clear();
    binaryMessage->append(ba);
}

void tst_ServerWorkerTests::init()
{
}

void tst_ServerWorkerTests::initTestCase()
{
    mc = new MessagesContainer();
    worker = new QCatalogServerWorker(QSqlDatabase::database());
    responseSignalSpy = new QSignalSpy(worker, SIGNAL(responseAvalible(QByteArray)));
    connect(worker, SIGNAL(responseAvalible(QByteArray)), this, SLOT(onResponseAvalible(QByteArray)));
    binaryMessage = new QByteArray();
}

void tst_ServerWorkerTests::cleanupTestCase()
{
    delete mc;
    delete binaryMessage;
    delete worker;
    delete responseSignalSpy;
}

void tst_ServerWorkerTests::cleanup()
{
    mc->Clear();
    responseSignalSpy->clear();
    binaryMessage->clear();
}


void tst_ServerWorkerTests::serverDontRespondToCorruptedMessage()
{
    QSignalSpy spy(worker, SIGNAL(messageCorrupted() ));
    const QByteArray ba = QByteArray(1000,'\0');
    worker->readyRead(ba);
    QVERIFY( spy.count() == 1 );
}

void tst_ServerWorkerTests::addBasicUserToServer()
{
    UserRegistrationMessage registrationMessage;
    UserRegistrationMessageReplay registerResponse;

    registrationMessage.set_name(QStringLiteral("testuser"));
    registrationMessage.set_password(QStringLiteral("some_password"));
    registrationMessage.set_email("valid@email.com");

    mc->addMessage(&registrationMessage);
    QByteArray ba = mc->toArray();
    worker->readyRead(ba);

    ba.clear();
    mc->Clear();
    QVERIFY( mc->fromArray(binaryMessage) );

    ba = QByteArray (mc->getCapsule(0).toArray());

    QVERIFY( registerResponse.fromArray(ba));
    QVERIFY( registerResponse.replay(0) == protbuf::Replay::UserAddOk );
}

void tst_ServerWorkerTests::loginToServer()
{
    LoginRequest loginRequest;
    LoginRequestResponse loginResponse;

    loginRequest.set_name(QStringLiteral("testuser"));
    loginRequest.set_password(QStringLiteral("some_password"));

    mc->addMessage( &loginRequest );

    QByteArray ba = mc->toArray();
    worker->readyRead(ba);

    mc->Clear();
    QVERIFY(mc->fromArray(binaryMessage));
    QVERIFY(loginResponse.fromArray(mc->getCapsule(0).getData()));
    QVERIFY(loginResponse.replay() == protbuf::Replay::LoginPass);
}

void tst_ServerWorkerTests::loginChangesUserStatus()
{
    LoginRequest loginRequest;
    LoginRequestResponse loginResponse;

    loginRequest.set_name(QStringLiteral("testuser"));
    loginRequest.set_password(QStringLiteral("some_password"));

    mc->addMessage( &loginRequest );

    QByteArray ba = mc->toArray();
    worker->readyRead(ba);

    mc->Clear();
    QVERIFY(mc->fromArray(binaryMessage));
    QVERIFY(loginResponse.fromArray(mc->getCapsule(0).getData()));
    QVERIFY(loginResponse.replay() == protbuf::Replay::UserAlreadyLogged);
}

void tst_ServerWorkerTests::logoutFromServer()
{
    LogoutRequest logoutRequest;
    LoginRequestResponse loginResponse;

    logoutRequest.set_logout(true);

    mc->addMessage( &logoutRequest );

    QByteArray ba = mc->toArray();
    worker->readyRead(ba);

    mc->Clear();
    QVERIFY(mc->fromArray(binaryMessage));
    QVERIFY(loginResponse.fromArray(mc->getCapsule(0).getData()));
    QVERIFY(loginResponse.replay() == protbuf::Replay::LogoutOk);
}

void tst_ServerWorkerTests::logoutWhileNotLoged()
{
    LogoutRequest logoutRequest;

    logoutRequest.set_logout(true);

    mc->addMessage( &logoutRequest );

    QByteArray ba = mc->toArray();
    worker->readyRead(ba);

    mc->Clear();
    QVERIFY(mc->fromArray(binaryMessage));
    QVERIFY(mc->capsules().size() == 1);
    QVERIFY(mc->getCapsule(0).msgtype() == MsgType::msgUserNotLogged );
}

void tst_ServerWorkerTests::loginToServerBadPasswd()
{
    LoginRequest loginRequest;
    LoginRequestResponse loginResponse;

    loginRequest.set_name(QStringLiteral("testuser"));
    loginRequest.set_password(QStringLiteral("bad_passwd"));

    mc->addMessage( &loginRequest );

    QByteArray ba = mc->toArray();
    worker->readyRead(ba);

    mc->Clear();
    QVERIFY(mc->fromArray(binaryMessage));
    QVERIFY(loginResponse.fromArray(mc->getCapsule(0).getData()));
    QVERIFY(loginResponse.replay() == protbuf::Replay::LoginDeny);
}

void tst_ServerWorkerTests::loginToServerBadUser()
{
    LoginRequest loginRequest;
    LoginRequestResponse loginResponse;

    loginRequest.set_name(QStringLiteral("bad_user"));
    loginRequest.set_password(QStringLiteral("bad_passwd"));

    mc->addMessage( &loginRequest );

    QByteArray ba = mc->toArray();
    worker->readyRead(ba);

    mc->Clear();
    QVERIFY(mc->fromArray(binaryMessage));
    QVERIFY(loginResponse.fromArray(mc->getCapsule(0).getData()));
    QVERIFY(loginResponse.replay() == protbuf::Replay::LoginDeny);
}

void tst_ServerWorkerTests::addFullUserToServer()
{
    UserRegistrationMessage registrationMessage;
    UserRegistrationMessageReplay registerResponse;

    registrationMessage.set_name(QStringLiteral("testuser2"));
    registrationMessage.set_password(QStringLiteral("some_password2"));
    registrationMessage.set_email(QStringLiteral("valid2@email.com"));
    registrationMessage.set_phonenumber(QStringLiteral("123456789"));
    registrationMessage.set_description(QStringLiteral("some description"));
    registrationMessage.set_address(QStringLiteral("aaaaaaaaaaaaaaaaaaa"));

    mc->addMessage(&registrationMessage);
    QByteArray ba = mc->toArray();
    worker->readyRead(ba);

    ba.clear();
    mc->Clear();
    QVERIFY( mc->fromArray(binaryMessage) );

    ba = QByteArray (mc->getCapsule(0).toArray());

    QVERIFY( registerResponse.fromArray(ba));
    QVERIFY( registerResponse.replay(0) == protbuf::Replay::UserAddOk );
}

void tst_ServerWorkerTests::login(QString name, QString pass)
{
    LoginRequest loginRequest;
    loginRequest.set_name(name);
    loginRequest.set_password(pass);

    mc->addMessage( &loginRequest );
    QByteArray ba = mc->toArray();
    worker->readyRead(ba);
    mc->Clear();
}

void tst_ServerWorkerTests::logout()
{
    login("testuser2","some_password2");

    LogoutRequest logoutRequest;
    LoginRequestResponse loginResponse;

    logoutRequest.set_logout(true);

    mc->addMessage( &logoutRequest );

    QByteArray ba = mc->toArray();
    worker->readyRead(ba);
    mc->Clear();
    QVERIFY(mc->fromArray(binaryMessage));
    QVERIFY(loginResponse.fromArray(mc->getCapsule(0).getData()));
    QVERIFY(loginResponse.replay() == protbuf::Replay::LogoutOk);
    mc->Clear();
    binaryMessage->clear();
}

void tst_ServerWorkerTests::loginGetsUserInformation()
{
    LoginRequestResponse loginResponse;
    User userData;
    login("testuser2", "some_password2");

    QVERIFY(mc->fromArray(binaryMessage));
    QVERIFY(mc->capsules().size() >= 2);
    QVERIFY(loginResponse.fromArray(mc->getCapsule(0).getData()));
    QVERIFY(loginResponse.replay() == protbuf::Replay::LoginPass);
    QVERIFY(userData.fromArray(mc->getCapsule(1).getData()));
    QVERIFY(userData.name() == "testuser2");
    QVERIFY(userData.phonenumber() == "123456789");
    QVERIFY(userData.description() == "some description");
    QVERIFY(userData.address() == "aaaaaaaaaaaaaaaaaaa");
    QVERIFY(userData.getStoragesList().size() == 1 );
    QVERIFY(userData.storagesNumber() == 1);
    QVERIFY(userData.getDefaultStorageId() != 0 );
    ///TODO last login + registration date;

    logout();
}

void tst_ServerWorkerTests::addParameter_worksOnlyIfUserIsOnline()
{
    logout();
    QByteArray msg;
    mc->addMessage(MsgType::reqParameters, msg);
    worker->readyRead(mc->toArray());
    mc->Clear();

    QVERIFY(mc->fromArray(binaryMessage));
    QVERIFY(mc->capsules().size() == 1);
    QVERIFY(mc->getCapsule(0).msgtype() == MsgType::msgUserNotLogged );
}

void tst_ServerWorkerTests::addParameter_addsNewParameter()
{
    login("testuser2", "some_password2");
    Parameter param;
    ResponseAddParameter resParameter;
    param.set_name(QStringLiteral("test_parameter_1"));
    param.set_symbol("test_p1");
    param.mutable_config()->set_minvalue(10);
    param.mutable_config()->set_maxvalue(20);
    param.mutable_config()->set_type(ParameterConfig::INT);

    mc->addMessage(MsgType::addParameter, param.toArray() );

    worker->readyRead(mc->toArray());
    mc->Clear();

    QVERIFY(mc->fromArray(binaryMessage));
    QVERIFY(mc->capsules().size() >=1); /// return addParameterOK + list of all parameters
    QVERIFY(mc->getCapsule(0).msgtype() == MsgType::resAddParameter );
    QVERIFY(resParameter.fromArray( mc->getCapsule(0).getData() ));
    QVERIFY(resParameter.replay().size() == 1);
    QVERIFY(resParameter.replay(0) == protbuf::resAddParameter::addOk );
}

void tst_ServerWorkerTests::addSameParameter_givesError()
{
    login("testuser2", "some_password2");
    Parameter param;
    ResponseAddParameter resParameter;
    param.set_name(QStringLiteral("test_parameter_1"));
    param.set_symbol("test_p1");
    param.mutable_config()->set_minvalue(10);
    param.mutable_config()->set_maxvalue(20);
    param.mutable_config()->set_type(ParameterConfig::INT);

    mc->addMessage(MsgType::addParameter, param.toArray() );

    worker->readyRead(mc->toArray());

    mc->Clear();

    QVERIFY(mc->fromArray(binaryMessage));
    QVERIFY(mc->capsules().size() == 1);
    QVERIFY(mc->getCapsule(0).msgtype() == MsgType::resAddParameter );
    QVERIFY(resParameter.fromArray( mc->getCapsule(0).getData() ));
    QVERIFY(resParameter.replay().size() == 1);
    QVERIFY(resParameter.replay(0) == protbuf::resAddParameter::parameterExists );
    logout();
}

void tst_ServerWorkerTests::addGroup_addsGroup()
{
    login("testuser2", "some_password2");

    RequestAddGroup g;
    RequestParameters rp;
    ResponseParameters resParameters;

    g.set_name("test_group");
    g.set_parentid(1);
    g.set_allowsets(true);
    g.set_allowitems(true);

    mc->addMessage(rp);
    worker->readyRead(mc->toArray());

    mc->Clear();
    QVERIFY(mc->fromArray(binaryMessage));
    QVERIFY(mc->capsules().size() == 1);
    QVERIFY(resParameters.fromArray(mc->getCapsule(0).getData() ));

    for(int i=0;i<resParameters.parameters_size();i++){
            g.add_parameters()->set_id(resParameters.parameters(i).id());
    }

    mc->Clear();
    mc->addMessage(g);
    worker->readyRead(mc->toArray());
    mc->Clear();

    QVERIFY(mc->fromArray(binaryMessage));
    QVERIFY(mc->capsules().size() == 1);

    logout();
}

