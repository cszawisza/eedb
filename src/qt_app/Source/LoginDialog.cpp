#include "LoginDialog.hpp"
#include "ui_LoginDialog.h"

#include <LoginVerificator.hpp>
#include <UserRegister.hpp>
#include <WebSocket.hpp>
#include <QUrl>
#include <QTimer>
#include <QFinalState>

#include "utils/Url.hpp"
#include "AddUserDialog.hpp"

#define STR(x) #x
#define STATE_GUARD(statename) \
    // connect( statename, &QState::entered, [&](){ qDebug() << STR(statename) << " entered "; } );  connect( statename, &QState::exited, [&](){ qDebug() << STR(statename) << " exited "; } );


LoginDialog::LoginDialog(const ILoginVerificator &p_loginVerificator,
                         QSharedPointer<ICommunicationManager> p_communicationManager,
                         const IUserRegister &p_userRegister,
                         QWidget *parent):    QDialog(parent),
    ui(new Ui::LoginDialog),
    m_manager(p_communicationManager),
    m_loginVerificator(p_loginVerificator),
    m_userRegister(p_userRegister),
    userReg(nullptr)
{
    ui->setupUi(this);
    stateMachine = new QStateMachine(this);

    userReg = new AddUserDialog(m_manager, this);

    QState* connectedState = new QState();
    QState* tryConnectState = new QState();

    QState* tryDisconnect = new QState(connectedState);
    QState* disconnectedState = new QState(connectedState);
    QState* canLoginState = new QState(connectedState);
    QState* login = new QState(connectedState);
    QState* tryLogin = new QState(connectedState);
    QState* loginFail = new QState(connectedState);
    QState* loginOk = new QState(connectedState);

    QState* userRegister = new QState(connectedState);
    QState* userRegisterOk = new QState(connectedState);
    QState* userRegisterFail = new QState(connectedState);

    STATE_GUARD(connectedState);
    STATE_GUARD(tryConnectState);
    STATE_GUARD(tryDisconnect);
    STATE_GUARD(disconnectedState);
    STATE_GUARD(canLoginState);
    STATE_GUARD(login);
    STATE_GUARD(tryLogin);
    STATE_GUARD(userRegister);
    STATE_GUARD(userRegisterOk);
    STATE_GUARD(userRegisterFail);

    disconnectedState->assignProperty( ui->login_groupbox, "enabled", false );
    disconnectedState->assignProperty( ui->connection_groupbox, "enabled", true );
    disconnectedState->assignProperty( ui->connectBtn, "text", QStringLiteral("Connect"));
    disconnectedState->addTransition(ui->connectBtn, SIGNAL(clicked()), tryConnectState);

    tryConnectState->assignProperty(ui->connection_groupbox, "enabled", false );
    tryConnectState->assignProperty(ui->connectBtn, "text", QStringLiteral("Try to connect") );
    tryConnectState->addTransition(m_manager.data(), SIGNAL(socketConnected()), connectedState);
    tryConnectState->addTransition(m_manager.data(), SIGNAL(socketDisconnected()), disconnectedState);

    connect(tryConnectState,  &QState::entered, [&](){
        connectToServer();
    });

    connectedState->assignProperty(ui->connectBtn, "text", QStringLiteral("Disconnect"));
    connectedState->assignProperty(ui->login_groupbox, "enabled", true );

    connectedState->addTransition(ui->registerNewUser, SIGNAL(clicked()), userRegister);
    connectedState->addTransition(ui->login, SIGNAL(clicked()), login);
    connectedState->addTransition(ui->connectBtn, SIGNAL(clicked()), tryDisconnect);
    connectedState->addTransition(m_manager.data(), SIGNAL(socketDisconnected()), disconnectedState);
    connectedState->setInitialState(canLoginState);

    connect( tryDisconnect, &QState::entered, [this](){
       m_manager->closeConnection();
    });

//    userRegister->assignProperty( userReg, "visible", true);
    userRegister->addTransition( userReg, SIGNAL(rejected()), canLoginState);
    userRegister->addTransition( userReg, SIGNAL(registrationSuccesfull()), userRegisterOk );
    userRegister->addTransition( userReg, SIGNAL(registrationFailed()), userRegisterFail);
    userRegister->addTransition( userReg, SIGNAL(registrationAborted()), canLoginState) ;

    connect( userRegister, &QState::entered, [&](){
        QTimer::singleShot( 0, userReg, SIGNAL(exec()));
    });
    connect( userRegister, &QState::exited, [this](){
        userReg->hide();
    });

    canLoginState->assignProperty( ui->login, "enabled", true);
    canLoginState->addTransition( ui->login, SIGNAL(clicked()), tryLogin );

    userRegisterOk->addTransition( this, SIGNAL(userRegisterOkExitSignal()), canLoginState);
    connect( userRegisterOk, &QState::entered, [this](){
        ui->userLogin->setText(userReg->name());
        ui->userPassword->setText(userReg->password());
        ui->login->setFocus();
        emit userRegisterOkExitSignal();
     });

    tryLogin->addTransition(this, SIGNAL(loginSucces()), loginOk);
    tryLogin->addTransition(this, SIGNAL(loginFailure()), loginFail);
    connect(tryLogin, &QState::entered, [this](){
        loginToServer();
    });

    connect(loginOk, &QState::entered, [this](){
        this->accept();
    });

    stateMachine->addState(disconnectedState);
    stateMachine->addState(tryConnectState);
    stateMachine->addState(connectedState);

    stateMachine->setInitialState(disconnectedState);
    stateMachine->start();

    setDeafultServerInfo();

    QTimer::singleShot(0, [&](){
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
//    protobuf::ServerResponses sr;
//    sr.ParseFromArray(msg.data(), msg.size());

//    protobuf::UserRes loginRes = sr.response(0).userres();

//    if(loginRes.code(0) == protobuf::UserRes_Reply_LoginPass ){
//        qDebug() << "Login pass";
//    }
//    else if(loginRes.code(0) == protobuf::UserRes_Reply_LoginDeny){
//        qDebug() << "login deny";
//    }

//    mc.fromArray(msg);
//    for(int i = 0; i<mc.capsules().size();++i)
//        if(mc.getCapsule(i).msgtype() == MsgType::resLogin ){
//            qDebug()<<" got login response";
//            protobuf::LoginResponse res;
//            res.ParseFromString(mc.getCapsule(i).data());
//            if(res.replay() == protobuf::Replay::LoginPass){
//                emit loginOk();
//            }
//            else if(res.replay() == protobuf::Replay::LoginDeny ){
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
//    protobuf::ClientRequests fullMessage;
//    auto loginReq = fullMessage.add_request();

//    auto userMsg = loginReq->mutable_userreq();

//    auto login = userMsg->mutable_login();
//    login->set_password(ui->userPassword->text().toStdString() );
//    login->mutable_cred()->set_nickname(ui->userLogin->text().toStdString());

//    QByteArray ba;
//    ba.resize(fullMessage.ByteSize());
//    fullMessage.SerializeToArray(ba.data(), ba.size() );

//    qDebug()<<" socket connected!: sending message: "<< QString(ba.toHex());

//    m_socket->sendBinaryMessage(ba);
//}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::connectToServer()
{
    Url l_url;
    l_url.setHost(ui->serverIp->text());
    l_url.setPort(ui->serverPort->text().toInt());

    m_manager->openConnection(l_url);
}

void LoginDialog::loginToServer()
{
    const std::string l_login = ui->userLogin->text().toStdString();
    const std::string l_pass = ui->userPassword->text().toStdString();
    if (m_loginVerificator.tryLogin(l_pass, l_login))
    {
        emit loginSucces();
    }
    else
        emit loginFailure();
}

void LoginDialog::setDeafultServerInfo()
{
    ui->serverIp->setText(setup.value(QStringLiteral("ServerIp"), QStringLiteral("eedb.pl")).toString());
    ui->serverPort->setText(setup.value(QStringLiteral("ServerPort"), 6666).toString());
    ui->userLogin->setText(setup.value(QStringLiteral("Login"), QStringLiteral("")).toString());
    ui->userPassword->setEchoMode(QLineEdit::Password);
}
