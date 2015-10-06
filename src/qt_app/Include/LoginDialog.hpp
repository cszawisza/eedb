#pragma once

#include <QDialog>
#include <QSettings>
#include <QAbstractSocket>

namespace Ui
{
class LoginDialog;
}

class ILoginVerificator;
class QWebSocket;

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(const ILoginVerificator & p_loginVerificator,
                         QWebSocket & p_webSocket,
                         QWidget *parent = 0);
    ~LoginDialog();

    QWebSocket *socket() const;
    Ui::LoginDialog *getUi();

public slots:
    void readyRead(QByteArray msg);

signals:
    void loginOk();
    void loginFailure();
    void showOtherWindow();
    void loginSucces();

protected:
    Ui::LoginDialog *ui;

private slots:
    void doConnectTest();
    void doReconnect();
    void doLogin();

private:
    void connectToServer();
    void loginToServer();
    void setDeafultServerInfo();
    //    User user;
    QSettings setup;
    QWebSocket & m_socket;
    const ILoginVerificator & m_loginVerificator;
};

