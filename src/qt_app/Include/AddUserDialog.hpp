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
    explicit AddUserDialog(ICommunicationManager & m_communicatioManager,
                           QWidget *parent = 0);
    ~AddUserDialog();

private slots:
    void on_registerNewUser_clicked();

private:
    Ui::AddUserDialog *ui;
    ICommunicationManager & m_communicatioManager;
};
