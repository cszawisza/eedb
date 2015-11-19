#pragma once

#include <QDialog>
#include <QSettings>
#include <QSharedPointer>

#include "ISocket.hpp"
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
                         QSharedPointer<ISocket> p_webSocket,
                         const IUserRegister & p_userRegister,
                         QWidget *parent = 0);
    ~LoginDialog();

    QSharedPointer<ISocket> socket() const;
    Ui::LoginDialog *getUi();

public slots:
    //void readyRead(QByteArray msg);

signals:
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

    const ILoginVerificator & m_loginVerificator;
    QSharedPointer<ISocket> m_socket;
    Action m_action;
    const IUserRegister & m_userRegister;
    QSettings setup;
};

