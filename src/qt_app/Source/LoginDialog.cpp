#include "LoginDialog.hpp"
#include "ui_LoginDialog.h"

#include <QWebSocket>

#include <LoginVerificator.hpp>
#include <UserRegister.hpp>

LoginDialog::LoginDialog(const ILoginVerificator & p_loginVerificator,
                         QWebSocket & p_webSocket,
                         const IUserRegister & p_userRegister,
                         QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    m_loginVerificator(p_loginVerificator),
    m_socket(p_webSocket),
    m_action(Action::LOGIN),
    m_userRegister(p_userRegister)
{
    ui->setupUi(this);
    ui->connection_groupbox->setChecked(false);
    connect(this, SIGNAL(loginSucces()), SLOT(close()));
    connect(this, SIGNAL(loginSucces()), SIGNAL(showOtherWindow()));
    setDeafultServerInfo();


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

    connect(ui->testConnction, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), [=](){
        m_action = Action::TESTCONNECTION;
        connectToServer();
    });

    connect(ui->registerNewUser, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), [=](){
        m_action = Action::REGISTER;
        connectToServer();
    });

    connect(ui->login, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), [=](){
        m_action = Action::LOGIN;
        connectToServer();
    });

    connect(&m_socket, &QWebSocket::connected, [=]() {
        chooseAction();
    });

    connect(&m_socket, static_cast< void(QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
            [=](QAbstractSocket::SocketError e){
        ui->connectResponseLabel->setText("Connection error: " + QString::number(e));
        m_socket.close();
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
//        m_socket.close();
//    }

//    if(m_socket.state() == QAbstractSocket::UnconnectedState){
//        m_socket.open(url);
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

//    m_socket.sendBinaryMessage(ba);
//}

QWebSocket *LoginDialog::socket() const
{
    return &m_socket;
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::doConnectTest()
{
    ui->connectResponseLabel->setText("Connection ok!");
    m_socket.close(QWebSocketProtocol::CloseCodeNormal, "Test connection, sorry for interrupt ;)");
}

void LoginDialog::connectToServer()
{
    QUrl l_url{};
    l_url.setHost(ui->serverIp->text());
    l_url.setPort(ui->serverPort->text().toInt());
    l_url.setScheme("ws");
    m_socket.open(l_url);
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
    if (m_action == Action::LOGIN)
        loginToServer();
    else if (m_action == Action::REGISTER)
    {
        m_userRegister.registerUser();
        m_socket.close();
    }
    else if (m_action == Action::TESTCONNECTION)
        doConnectTest();
}
