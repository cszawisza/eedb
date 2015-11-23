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

    Ui::LoginDialog *getUi();

public slots:

signals:
    void loginOk();
    void loginFailure();
    void showOtherWindow();
    void loginSucces();

protected:
    Ui::LoginDialog *ui;
private:
    void connectToServer();
    void loginToServer();
    void setDeafultServerInfo();
    void chooseAction();

    QStateMachine *stateMachine;
    QSharedPointer<ICommunicationManager> m_manager;
    const ILoginVerificator & m_loginVerificator;
    const IUserRegister & m_userRegister;
    QSettings setup;
    AddUserDialog *userReg;
signals:

    void userRegisterOkExitSignal();
};

