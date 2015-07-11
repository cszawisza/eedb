#pragma once

#include <QDialog>
#include <QSettings>
#include <QAbstractSocket>
#include <QWebSocket>
#include <CommunicationManager.hpp>

//#include "messages/user.h"

namespace Ui
{
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

    QWebSocket *socket() const;
    void setSocket(QWebSocket *socket);
    Ui::LoginDialog *getUi();

public slots:
    void readyRead(QByteArray msg);
signals:
    void loginOk();
    void loginFailure();
protected:
    Ui::LoginDialog *ui;
private:
    QSettings setup;

private slots:
    void doConnectTest();
    void doReconnect();
    void doLogin();
private:
    //    User user;
    QWebSocket *m_socket;
    CommunicationManager m_communicationManager;
};

