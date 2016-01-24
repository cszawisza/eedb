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

#include <Interfaces/ClientRequest.hpp>
#include <Interfaces/UserRequests.hpp>

#define STR(x) #x
#define STATE_GUARD(statename) \
     connect( statename, &QState::entered, [&](){ qDebug() << STR(statename) << " entered "; } );  connect( statename, &QState::exited, [&](){ qDebug() << STR(statename) << " exited "; } );

LoginDialog::LoginDialog(const ILoginVerificator &p_loginVerificator,
                         QSharedPointer<IUserCommunicationManager> p_communicationManager,
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
    tryConnectState->addTransition(ui->connectBtn, SIGNAL(clicked()), tryDisconnect);

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

    tryDisconnect->addTransition( m_manager.data(), SIGNAL(socketDisconnected()), disconnectedState);
    connect( tryDisconnect, &QState::entered, [this](){
       m_manager->closeConnection();
    });

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

    tryLogin->addTransition(&m_loginVerificator, SIGNAL(loginSuccess()), loginOk);
    tryLogin->addTransition(&m_loginVerificator, SIGNAL(loginError()), loginFail);

    loginFail->addTransition(this, SIGNAL(loginFailure()), canLoginState);

    connect(tryLogin, &QState::entered, [this](){
        loginToServer();
    });

    connect(loginOk, &QState::entered, [this](){
        emit loginPass();
        this->accept();
    });

    connect(loginFail, &QState::entered, [this](){
        qDebug() << "FAILED!";
        QTimer::singleShot(500, [this]() { emit loginFailure(); } );
    });

    stateMachine->addState(disconnectedState);
    stateMachine->addState(tryConnectState);
    stateMachine->addState(connectedState);

    stateMachine->setInitialState(disconnectedState);
    stateMachine->start();


    // Communication manager connections
    connect( m_manager.data(), SIGNAL(receivedMessage(responses::IUser)),
             this, SLOT(userResponseReceived(responses::IUser)));

    connect(&m_loginVerificator, SIGNAL(loginError(QString)), this, SLOT(showBadUsernameTooltip(QString)));

    QTimer::singleShot(0, [&](){
        ui->connectBtn->click();
    });

    setDeafultServerInfo();
}

Ui::LoginDialog *LoginDialog::getUi()
{
    return ui;
}

void LoginDialog::userResponseReceived(const responses::IUser &msg)
{
    if(msg.has_login()){
        m_loginVerificator.loginResponseReceived( msg.get_login() );
    }
    else if( msg.has_add() ){
//        m_userRegister
    }
}

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

    auto login = m_manager->newRequest()->user()->login();

    login->set_password(l_pass);
    login->credentials()->set_authorization(l_login);

    m_manager->sendRequest();
}

void LoginDialog::setDeafultServerInfo()
{
    ui->serverIp->setText(setup.value(QStringLiteral("ServerIp"), QStringLiteral("localhost")).toString());
    ui->serverPort->setText(setup.value(QStringLiteral("ServerPort"), 6666).toString());
    ui->userLogin->setText(setup.value(QStringLiteral("Login"), QStringLiteral("")).toString());
    ui->userPassword->setEchoMode(QLineEdit::Password);
}

void LoginDialog::showBadUsernameTooltip(QString txt)
{
    ui->userLogin->setToolTip( txt );
    ui->userLogin->setToolTipDuration(2000);
}
