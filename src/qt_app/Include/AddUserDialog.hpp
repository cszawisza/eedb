#pragma once

#include <QDialog>
#include <QState>
#include <QFinalState>
#include <QStateMachine>

///TODO description field: use https://github.com/Anchakor/MRichTextEditor

namespace Ui
{
class AddUserDialog;
}

class IUserCommunicationManager;

class AddUserDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddUserDialog(QSharedPointer<IUserCommunicationManager> m_communicatioManager,
                           QWidget *parent = 0);
    ~AddUserDialog();

    QString name() const;
    QString password() const;

private slots:
    void on_registerNewUser_clicked();

signals:
    void registrationSuccesfull();
    void registrationFailed();
    void registrationAborted();
private:
    Ui::AddUserDialog *ui;
    QSharedPointer<IUserCommunicationManager> m_communicatioManager;
    QStateMachine *stateMachine;
};
