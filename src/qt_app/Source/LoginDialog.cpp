#include "LoginDialog.hpp"
#include "ui_LoginDialog.h"

#include <LoginVerificator.hpp>
#include <UserRegister.hpp>
#include <WebSocket.hpp>
#include <QUrl>
#include <QTimer>

#include "AddUserDialog.hpp"

#define STR(x) #x
#define STATE_GUARD(statename) \
    connect( statename, &QState::entered, [&](){ qDebug() << STR(statename) << " entered "; } );\
    connect( statename, &QState::exited, [&](){ qDebug() << STR(statename) << " exited "; } );

void LoginDialog::prepareUnconnectedState(QState* unconnectedState, QState* tryConnect)
{

}

void LoginDialog::prepareTryConnectState(QState* tryConnect, QState* connected, QState* unconnected)
{

}

void LoginDialog::prepareConnectedState(QState* connected, QState* disconnect, QState* login, QState* userRegister)
{

}

LoginDialog::LoginDialog(const ILoginVerificator &p_loginVerificator,
                         QSharedPointer<ICommunicationManager> p_communicationManager,
                         const IUserRegister &p_userRegister,
                         QWidget *parent):    QDialog(parent),
    ui(new Ui::LoginDialog),
    m_manager(p_communicationManager),
    m_loginVerificator(p_loginVerificator),
    m_action(Action::LOGIN),
    m_userRegister(p_userRegister)
{
    ui->setupUi(this);

    userReg = new AddUserDialog(m_manager, this);
    
    stateMachine = new QStateMachine(this);

    QState* connectedState = new QState();//, waitForSend, waitForResponse, werify;
    QState* tryConnectState = new QState();

    QState* tryDisconnect = new QState(connectedState);
    QState* disconnectedState = new QState(connectedState);
    QState* canLoginState = new QState(connectedState);
    QState* login = new QState(connectedState);
    QState* tryLogin = new QState(connectedState);
    QState* loginFail = new QState(connectedState);
    QState* loginOk = new QState(connectedState);

//    QState* disconnect = new QState(disconnectedState);
    QState* userRegister = new QState(connectedState);
    QState* userRegisterFail = new QState(connectedState);

    STATE_GUARD(connectedState);
    STATE_GUARD(tryConnectState);
    STATE_GUARD(tryDisconnect);
    STATE_GUARD(disconnectedState);
    STATE_GUARD(canLoginState);
    STATE_GUARD(login);
    STATE_GUARD(tryLogin);
    STATE_GUARD(userRegister);
    STATE_GUARD(userRegisterFail);

    disconnectedState->assignProperty( ui->login_groupbox, "enabled", false );
    disconnectedState->assignProperty( ui->connection_groupbox, "enabled", true );
    disconnectedState->assignProperty( ui->connectBtn, "text", "Connect");
    disconnectedState->addTransition(ui->connectBtn, SIGNAL(clicked()), tryConnectState);

    tryConnectState->assignProperty(ui->connection_groupbox, "enabled", false );
    tryConnectState->assignProperty(ui->connectBtn, "text", "Try to connect" );
    tryConnectState->addTransition(m_manager->socket().data(), SIGNAL(opened()), connectedState);
    tryConnectState->addTransition(m_manager->socket().data(), SIGNAL(error(QAbstractSocket::SocketError)), disconnectedState);

    connect(tryConnectState,  &QState::entered, [&](){
        QUrl url;
        url.setHost(ui->serverIp->text());
        url.setPort(ui->serverPort->text().toInt());
        url.setScheme("ws");

        m_manager->socket()->open(url);
    });

    connectedState->assignProperty(ui->connectBtn, "text", "Disconnect");
    connectedState->assignProperty(ui->login_groupbox, "enabled", true );

    connectedState->addTransition(ui->registerNewUser, SIGNAL(clicked()), userRegister);
    connectedState->addTransition(ui->login, SIGNAL(clicked()), login);
    connectedState->addTransition(ui->connectBtn, SIGNAL(clicked()), tryDisconnect);
    connectedState->addTransition(m_manager->socket().data(), SIGNAL(closed()), disconnectedState);
    connectedState->setInitialState(canLoginState);

    connect( tryDisconnect, &QState::entered, [this](){
       m_manager->socket()->close();
    });

//    userRegister->assignProperty( this, "visible", false);
    userRegister->assignProperty( userReg, "visible", true);
    userRegister->addTransition( userReg, SIGNAL(rejected()), canLoginState);
    userRegister->addTransition( userReg, SIGNAL(registrationSuccesfull()), canLoginState );
    connect( userRegister, &QState::exited, [this](){
        userReg->hide();
    });

    canLoginState->assignProperty( ui->login, "enabled", true);

    connect( canLoginState, &QState::entered, [this](){
        ui->userLogin->setText(userReg->name());
        ui->userPassword->setText(userReg->password());
     });

    canLoginState->addTransition( ui->login, SIGNAL(clicked()), tryLogin );
    userRegister->addTransition( userReg, SIGNAL(registrationFailed()), userRegisterFail);
    userRegister->addTransition( userReg, SIGNAL(registrationAborted()), connectedState) ;

    stateMachine->addState(disconnectedState);
    stateMachine->addState(tryConnectState);
    stateMachine->addState(connectedState);
//    stateMachine->addState(tryConnect);
//    stateMachine->addState(connected);
//    stateMachine->addState(login);
//    stateMachine->addState(userRegister);
//    stateMachine->addState(canLoginState);
//    stateMachine->addState(userRegisterFail);


    stateMachine->setInitialState(disconnectedState);
    stateMachine->start();

//    ui->connection_groupbox->setChecked(false);
//    connect(this, SIGNAL(loginSucces()), SLOT(close()));
//    connect(this, SIGNAL(loginSucces()), SIGNAL(showOtherWindow()));
//    setDeafultServerInfo();

//    connect(this, &LoginDialog::loginFailure, [=](){
//        ui->connectResponseLabel->setText("Autentification error");
//    });

//    connect(this, &LoginDialog::loginOk, [=](){
//        ui->connectResponseLabel->setText("Autentification succes");
//        setup.setValue("login", ui->userLogin->text() );
//        setup.setValue("serverIp", ui->serverIp->text() );
//        setup.setValue("serverPort", ui->serverPort->text() );
//        this->accept();
//    });

//    connect(&m_socket, &QWebSocket::disconnected, [=](){
//        qDebug()<<" peer disconnected";
//        ui->connectResponseLabel->setText("peer disconnected");
//    });

    //connect(&m_socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(readyRead(QByteArray)));

//    connect(ui->testConnction, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), [=](){
//        m_action = Action::TESTCONNECTION;
//        connectToServer();
//    });

//    connect(ui->registerNewUser, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), [=](){
//        m_action = Action::REGISTER;
//        connectToServer();
//    });

//    connect(ui->login, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), [=](){
//        m_action = Action::LOGIN;
//        connectToServer();
//    });

//    connect(m_socket.data(), &ISocket::connected, [=]() {
//        chooseAction();
//    });

    ///TODO repair
//    connect(m_socket.data(), static_cast< void(ISocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
//            [=](QAbstractSocket::SocketError e){
//        ui->connectResponseLabel->setText("Connection error: " + QString::number(e));
//        m_socket->close();
//    });

//    setDeafultServerInfo();

    QTimer::singleShot(10, [&](){
        ui->connectBtn->click();
    });
}

Ui::LoginDialog *LoginDialog::getUi()
{
    return ui;
}

//void LoginDialog::readyRead(QByteArray msg){
//    //Server response handler code
//    qDebug()<< msg.toHex();
//    pb::ServerResponses sr;
//    sr.ParseFromArray(msg.data(), msg.size());

//    pb::UserRes loginRes = sr.response(0).userres();

//    if(loginRes.code(0) == pb::UserRes_Reply_LoginPass ){
//        qDebug() << "Login pass";
//    }
//    else if(loginRes.code(0) == pb::UserRes_Reply_LoginDeny){
//        qDebug() << "login deny";
//    }

//    mc.fromArray(msg);
//    for(int i = 0; i<mc.capsules().size();++i)
//        if(mc.getCapsule(i).msgtype() == MsgType::resLogin ){
//            qDebug()<<" got login response";
//            pb::LoginResponse res;
//            res.ParseFromString(mc.getCapsule(i).data());
//            if(res.replay() == pb::Replay::LoginPass){
//                emit loginOk();
//            }
//            else if(res.replay() == pb::Replay::LoginDeny ){
//                emit loginFailure();
//            }
//        }
//        else if(mc.getCapsule(i).msgtype() == MsgType::msgUser){
//            qDebug()<<" got user response";
//            user.fromArray(mc.getCapsule(i).getData());
//        }
//}

//void LoginDialog::doReconnect(){
//    static QString host = "";
//    static int port = 0;

//    QUrl url;
//    url.setHost(ui->serverIp->text());
//    url.setPort(ui->serverPort->text().toInt());
//    url.setScheme("ws");

//    if( host != url.host() || port != url.port() ){
//        port = url.port();
//        host = url.host();
//        qDebug() << "closing socket";
//        m_socket->close();
//    }

//    if(m_socket->state() == QAbstractSocket::UnconnectedState){
//        m_socket->open(url);
//        QEventLoop pause;
//        QTimer *timer = new QTimer();
//        timer->setSingleShot(1000);
//        connect(timer, SIGNAL(timeout()), &pause, SLOT(quit()));
//        connect(&m_socket, SIGNAL( connected() ), &pause, SLOT(quit()));
//    }
//}

//void LoginDialog::doLogin()
//{
//    pb::ClientRequests fullMessage;
//    auto loginReq = fullMessage.add_request();

//    auto userMsg = loginReq->mutable_userreq();

//    auto login = userMsg->mutable_login();
//    login->set_password(ui->userPassword->text().toStdString() );
//    login->mutable_cred()->set_name(ui->userLogin->text().toStdString());

//    QByteArray ba;
//    ba.resize(fullMessage.ByteSize());
//    fullMessage.SerializeToArray(ba.data(), ba.size() );

//    qDebug()<<" socket connected!: sending message: "<< QString(ba.toHex());

//    m_socket->sendBinaryMessage(ba);
//}

//QSharedPointer<ISocket> LoginDialog::socket() const
//{
//    return m_socket;
//}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::doConnectTest()
{
//    emit testConnection(
//    ui->connectResponseLabel->setText("Connection ok!");
//    m_socket->close(ISocket::CloseCodeNormal, "Test connection, sorry for interrupt ;)");
}

void LoginDialog::connectToServer()
{
    QUrl l_url{};
    l_url.setHost(ui->serverIp->text());
    l_url.setPort(ui->serverPort->text().toInt());
    l_url.setScheme("ws");
    emit testConnection(l_url);
}

void LoginDialog::loginToServer()
{
    const std::string l_login = ui->userLogin->text().toStdString();
    const std::string l_pass = ui->userPassword->text().toStdString();
    if (m_loginVerificator.tryLogin(l_pass, l_login))
    {
        emit loginSucces();
    }
}

void LoginDialog::setDeafultServerInfo()
{
    ui->serverIp->setText(setup.value("ServerIp", "eedb.pl").toString());
    ui->serverPort->setText(setup.value("ServerPort", 6666).toString());
    ui->userLogin->setText(setup.value("Login", "").toString());
    ui->userPassword->setEchoMode(QLineEdit::Password);
}

void LoginDialog::chooseAction()
{
//    if (m_action == Action::LOGIN)
//        loginToServer();
//    else if (m_action == Action::REGISTER)
//    {
//        m_userRegister.registerUser();
//        m_manager->close();
//    }
//    else if (m_action == Action::TESTCONNECTION)
//        doConnectTest();
}
