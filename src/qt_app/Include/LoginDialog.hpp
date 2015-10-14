#pragma once

#include <QDialog>
#include <QSettings>

namespace Ui
{
class LoginDialog;
}

class ILoginVerificator;
class QWebSocket;
class IUserRegister;

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(const ILoginVerificator & p_loginVerificator,
                         QWebSocket & p_webSocket,
                         const IUserRegister & p_userRegister,
                         QWidget *parent = 0);
    ~LoginDialog();

    QWebSocket *socket() const;
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
    QWebSocket & m_socket;
    Action m_action;
    const IUserRegister & m_userRegister;
    QSettings setup;
};

