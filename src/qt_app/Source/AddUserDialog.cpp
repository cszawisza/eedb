#include <QInputDialog>
#include <QMessageBox>

#include "AddUserDialog.hpp"
#include "ui_AddUserDialog.h"
#include "CommunicationManager.hpp"

AddUserDialog::AddUserDialog(ICommunicationManager & p_communicatioManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog),
    m_communicatioManager(p_communicatioManager)
{
    ui->setupUi(this);
}

AddUserDialog::~AddUserDialog()
{
    delete ui;
}

void AddUserDialog::on_registerNewUser_clicked()
{
    std::string l_userName{};
    std::string l_userPassword{};
    std::string l_userEmail{};
    std::string l_userAdress{};
    std::string l_userDescritpion{};
    std::string l_userPhoneNumber{};

    if(!(!(ui->name->text().isEmpty()) && !(ui->email->text().isEmpty()) && !(ui->password->text().isEmpty()))) // NOR
    {
        QMessageBox msgBox{};
        msgBox.setText("Podaj nazwę użytkownika, hasło oraz email");
        msgBox.exec();
        return;
    }
    else
    {
        l_userEmail = ui->email->text().toStdString();
        l_userName = ui->name->text().toStdString();
        l_userPassword = ui->password->text().toStdString();
    }
    l_userAdress = ui->address->toPlainText().toStdString();
    l_userDescritpion = ui->description->toPlainText().toStdString();
    l_userPhoneNumber = ui->phonenumber->text().toStdString();

    ///FIXME
//    m_communicatioManager.handleRegister(l_userName, l_userPassword, l_userEmail,
//                                         l_userAdress, l_userDescritpion, l_userPhoneNumber);
//    pb::ClientRequests fullMessage;
//    auto loginReq = fullMessage.add_request();
//    auto userMsg = loginReq->mutable_userreq();
//    auto login = userMsg->mutable_add();
//    login->mutable_basic()->set_name( ui->name->text().toStdString() );
//    login->mutable_basic()->set_email(ui->email->text().toStdString() );

//    if(! ui->description->toPlainText().isEmpty())
//        login->mutable_basic()->set_description( ui->description->toHtml().toStdString() );
//    if(! ui->address->toPlainText().isEmpty() )
//        login->mutable_details()->set_address( ui->address->toPlainText().toStdString() );
//    if(! ui->phonenumber->text().isEmpty() )
//        login->mutable_details()->set_phone_number( ui->phonenumber->text().toStdString() );

//    bool ok, ok2;
//    QString passwd1 = QInputDialog::getText(this, "Wprowadź hasło","Wprowadź hasło",QLineEdit::Password,"",&ok);
//    QString passwd2 = QInputDialog::getText(this, "Wprowadź hasło","Wprowadź ponownie hasło",QLineEdit::Password,"",&ok2);

//    if (passwd1 != passwd2 )
//        return;
//    login->set_password( passwd1.toStdString() );

//    QByteArray ba;
//    ba.resize(fullMessage.ByteSize());
//    fullMessage.SerializeToArray(ba.data(), ba.size() );

//    m_socket.sendBinaryMessage(ba);
}
