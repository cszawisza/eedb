#include "LoginDialog.hpp"
#include "ui_LoginDialog.h"

#include <QAbstractSocket>
#include <QTimer>
#include <QWebSocket>

#include "message_conteiner.pb.h"
#include "user.pb.h"

#include "AddUserDialog.hpp"
#include <ILoginVerificator.hpp>

LoginDialog::LoginDialog(const ILoginVerificator & p_loginVerificator,
                         QWebSocket & p_webSocket,
                         QWidget *parent) :
    ui(new Ui::LoginDialog),
    m_loginVerificator(p_loginVerificator),
    m_socket(p_webSocket),
    QDialog(parent)
{
    ui->setupUi(this);
    ui->connection_groupbox->setChecked(false);
    connect(this, SIGNAL(loginSucces()), SLOT(close()));
    connect(this, SIGNAL(loginSucces()), SIGNAL(showOtherWindow()));

    qRegisterMetaType<QAbstractSocket::SocketState>();

    setDeafultServerInfo();

    connect(ui->testConnction, SIGNAL(clicked()), this, SLOT(doConnectTest()));

    connect(ui->registerNewUser, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked),
            [=](){
        doReconnect();
        if(m_socket.state() == QAbstractSocket::ConnectedState){
            disconnect(&m_socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(readyRead(QByteArray)));
            AddUserDialog *dialog = new AddUserDialog(&m_socket, this);
            dialog->exec();
            connect(&m_socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(readyRead(QByteArray)));
        }
        else{
            ui->connectResponseLabel->setText("peer disconnected");
        }
    });

    connect(this, &LoginDialog::loginFailure, [=](){
        ui->connectResponseLabel->setText("Autentification error");
    });

    connect(this, &LoginDialog::loginOk, [=](){
        ui->connectResponseLabel->setText("Autentification succes");
        setup.setValue("login", ui->userLogin->text() );
        setup.setValue("serverIp", ui->serverIp->text() );
        setup.setValue("serverPort", ui->serverPort->text() );
        this->accept();
    });

    connect(&m_socket, &QWebSocket::disconnected, [=](){
        qDebug()<<" peer disconnected";
        ui->connectResponseLabel->setText("peer disconnected");
    });

    connect(&m_socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(readyRead(QByteArray)));





    connect(ui->login, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), [=](){
        connectToServer();
        qDebug() << "WebSocket state: " << m_socket.state();
        if (m_socket.state() == QAbstractSocket::ConnectedState)
        {
            loginToServer();
        }
        qDebug() << "WebSocket state: " << m_socket.state();
    });
}

Ui::LoginDialog *LoginDialog::getUi()
{
    return ui;
}

void LoginDialog::readyRead(QByteArray msg){
    //Server response handler code
    qDebug()<< msg.toHex();
    pb::ServerResponses sr;
    sr.ParseFromArray(msg.data(), msg.size());

    pb::UserRes loginRes = sr.response(0).userres();

    if(loginRes.code(0) == pb::UserRes_Reply_LoginPass ){
        qDebug() << "Login pass";
    }
    else if(loginRes.code(0) == pb::UserRes_Reply_LoginDeny){
        qDebug() << "login deny";
    }

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
}

void LoginDialog::doReconnect(){
    static QString host = "";
    static int port = 0;

    QUrl url;
    url.setHost(ui->serverIp->text());
    url.setPort(ui->serverPort->text().toInt());
    url.setScheme("ws");

    if( host != url.host() || port != url.port() ){
        port = url.port();
        host = url.host();
        qDebug() << "closing socket";
        m_socket.close();
    }

    if(m_socket.state() == QAbstractSocket::UnconnectedState){
        m_socket.open(url);
        QEventLoop pause;
        QTimer *timer = new QTimer();
        timer->setSingleShot(1000);
        connect(timer, SIGNAL(timeout()), &pause, SLOT(quit()));
        connect(&m_socket, SIGNAL( connected() ), &pause, SLOT(quit()));
    }
}

void LoginDialog::doLogin()
{
    pb::ClientRequests fullMessage;
    auto loginReq = fullMessage.add_request();

    auto userMsg = loginReq->mutable_userreq();

    auto login = userMsg->mutable_login();
    login->set_password(ui->userPassword->text().toStdString() );
    login->mutable_cred()->set_name(ui->userLogin->text().toStdString());

    QByteArray ba;
    ba.resize(fullMessage.ByteSize());
    fullMessage.SerializeToArray(ba.data(), ba.size() );

    qDebug()<<" socket connected!: sending message: "<< QString(ba.toHex());

    m_socket.sendBinaryMessage(ba);
}

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
    static QWebSocket *socket = new QWebSocket();
    QUrl url;
    url.setHost(ui->serverIp->text());
    url.setPort(ui->serverPort->text().toInt());
    url.setScheme("ws");

    connect(socket, &QWebSocket::connected, [=]() {
        ui->connectResponseLabel->setText("connection okqqq!");
        qDebug() << "WebSocket state (slot): " << socket->state();
        socket->close(QWebSocketProtocol::CloseCodeNormal, "Test connection, sorry for interrupt ;)");
        socket->disconnect();
    });

    connect(socket, static_cast< void(QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error), [=](QAbstractSocket::SocketError e){
        qDebug()<<"error" << e;
        ui->connectResponseLabel->setText("connection error: " + QString::number(e));
        socket->disconnect();
    });

    qDebug()<<" try to connect to " << url.toString();
    socket->open(url);
    qDebug() << "WebSocket state: " << socket->state();
}

void showMsg()
{
    qDebug() << "Some MSG";
}

void LoginDialog::connectToServer()
{
    QUrl l_url{};
    l_url.setHost(ui->serverIp->text());
    l_url.setPort(ui->serverPort->text().toInt());
    l_url.setScheme("ws");
    m_socket.open(l_url);
    connect(&m_socket, &QWebSocket::connected, [&]() {
        qDebug() << "WebSocket state (connectToServer): " << m_socket.state();
        showMsg();
    });
}

void LoginDialog::loginToServer()
{
    const std::string l_login = ui->userLogin->text().toStdString();
    const std::string l_pass = ui->userPassword->text().toStdString();
    if (m_loginVerificator.tryLogin(l_pass, l_login))
    {
        qDebug() << "Success login";
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
