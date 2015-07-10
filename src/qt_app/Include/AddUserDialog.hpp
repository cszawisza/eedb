#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>
#include <QWebSocket>

///TODO description field: use https://github.com/Anchakor/MRichTextEditor

namespace Ui {
class AddUserDialog;
}

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserDialog(QWebSocket *ws, QWidget *parent = 0);
    ~AddUserDialog();

public slots:
    void readyRead(QByteArray msg);
private slots:
    void on_registerNewUser_clicked();

private:
    Ui::AddUserDialog *ui;
    QWebSocket *socket;
};

#endif // ADDUSERDIALOG_H