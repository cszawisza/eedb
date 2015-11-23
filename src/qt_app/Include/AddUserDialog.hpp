#pragma once

#include <QDialog>

///TODO description field: use https://github.com/Anchakor/MRichTextEditor

namespace Ui
{
class AddUserDialog;
}

class ICommunicationManager;

class AddUserDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddUserDialog(QSharedPointer<ICommunicationManager> m_communicatioManager,
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
    QSharedPointer<ICommunicationManager> m_communicatioManager;
};
