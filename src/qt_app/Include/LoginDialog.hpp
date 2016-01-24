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
                         QSharedPointer<IUserCommunicationManager> p_communicationManager,
                         const IUserRegister & p_userRegister,
                         QWidget *parent = 0);
    ~LoginDialog();

    Ui::LoginDialog *getUi();

private slots:

    void userResponseReceived(const responses::IUser &);

signals:
    void loginPass();
    void loginFailure();
    void showOtherWindow();

protected:
    Ui::LoginDialog *ui;
private:
    void connectToServer();
    void loginToServer();
    void setDeafultServerInfo();

    QStateMachine *stateMachine;
    QSharedPointer<IUserCommunicationManager> m_manager;
    const ILoginVerificator & m_loginVerificator;
    const IUserRegister & m_userRegister;
    QSettings setup;
    AddUserDialog *userReg;

private slots:
    void showBadUsernameTooltip( QString txt );
signals:

    void userRegisterOkExitSignal();
};

