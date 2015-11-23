#pragma once

#include <QDialog>
#include <QSettings>
#include <QSharedPointer>
#include <QStateMachine>

#include "AddUserDialog.hpp"
#include "ICommunicationManager.hpp"
namespace Ui
{
class LoginDialog;
}

class ILoginVerificator;

class IUserRegister;

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(const ILoginVerificator & p_loginVerificator,
                         QSharedPointer<ICommunicationManager> p_communicationManager,
                         const IUserRegister & p_userRegister,
                         QWidget *parent = 0);
    ~LoginDialog();

//    QSharedPointer<ISocket> socket() const;
    Ui::LoginDialog *getUi();

    void prepareUnconnectedState(QState* unconnectedState, QState* tryConnect);
    void prepareTryConnectState(QState* tryConnect, QState* connected, QState *unconnected);
    void prepareConnectedState(QState* connected, QState* disconnect, QState* login, QState* userRegister);
public slots:
    //void readyRead(QByteArray msg);

signals:
    void connectionOk();
    void testConnection( const QUrl &urlToTest );

    void loginOk();
    void loginFailure();
    void showOtherWindow();
    void loginSucces();

protected:
    Ui::LoginDialog *ui;

private slots:
    void doConnectTest();
    //void doReconnect();
    //void doLogin();

private:
    enum class Action {LOGIN, REGISTER, TESTCONNECTION};
    void connectToServer();
    void loginToServer();
    void setDeafultServerInfo();
    void chooseAction();

    QStateMachine *stateMachine;
    QSharedPointer<ICommunicationManager> m_manager;
    const ILoginVerificator & m_loginVerificator;
    Action m_action;
    const IUserRegister & m_userRegister;
    QSettings setup;
    AddUserDialog *userReg;
};

