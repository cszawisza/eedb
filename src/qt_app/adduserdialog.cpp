#include "adduserdialog.h"
#include "ui_adduserdialog.h"

#include "pb_cpp/user.pb.h"
#include "pb_cpp/message_conteiner.pb.h"
#include <QInputDialog>

AddUserDialog::AddUserDialog(QWebSocket *ws, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog),
    socket(ws)
{
    ui->setupUi(this);
    connect(socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(readyRead(QByteArray)));
}

///TODO add print error field, wher you can put all messages from server
void AddUserDialog::readyRead(QByteArray msg){


//    mc.fromArray(msg);
//    for(int i = 0; i<mc.capsules().size();++i){
//        if(mc.getCapsule(i).msgtype() == MsgType::resAddUser ){
//            qDebug()<<" got add user response";
//            protbuf::RegisterResponse res;
//            res.ParseFromString(mc.getCapsule(i).data());
//            for(int j = 0 ; j<res.replay_size();j++){
//                if(res.replay(j) == protbuf::Replay::EmailExists){
//                    ui->status->setText("User email exists");
//                }
//                else if(res.replay(j) == protbuf::Replay::EmailAddressToLong ){
//                    ui->status->setText("Email to long");
//                }
//                else if(res.replay(j) == protbuf::Replay::EmailNotValidate){
//                    ui->status->setText("Email not validate");
//                }
//                else if(res.replay(j) == protbuf::Replay::UserNameToLong){
//                    ui->status->setText("User name to long");
//                }
//                else if(res.replay(j) == protbuf::Replay::UserNameToShort){
//                    ui->status->setText("User name to short");
//                }
//                else if(res.replay(j) == protbuf::Replay::PasswordToShort){
//                    ui->status->setText("User has to short password");
//                }
//                else if(res.replay(j) == protbuf::Replay::UserAlreadyExists){
//                    ui->status->setText("User name exists");
//                }
//                else if (res.replay(j) == protbuf::Replay::UserAddOk ){
//                    ui->status->setText("USER CREATED!!");
//                }
//            }
//        }
//    }


}

AddUserDialog::~AddUserDialog()
{
    disconnect(socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(readyRead(QByteArray)));
    delete ui;
}

void AddUserDialog::on_registerNewUser_clicked()
{
    protbuf::ClientRequests fullMessage;
    auto loginReq = fullMessage.add_request();
    auto userMsg = loginReq->mutable_msguserreq();
    auto login = userMsg->mutable_add();
    login->mutable_details()->set_name( ui->name->text().toStdString() );
    login->mutable_details()->set_email(ui->email->text().toStdString() );

    if(! ui->description->toPlainText().isEmpty())
        login->mutable_details()->set_description( ui->description->toHtml().toStdString() );
    if(! ui->address->toPlainText().isEmpty() )
        login->mutable_details()->set_address( ui->address->toPlainText().toStdString() );
    if(! ui->phonenumber->text().isEmpty() )
        login->mutable_details()->set_phone_number( ui->phonenumber->text().toStdString() );

    bool ok, ok2;
    QString passwd1 = QInputDialog::getText(this, "Wprowadź hasło","Wprowadź hasło",QLineEdit::Password,"",&ok);
    QString passwd2 = QInputDialog::getText(this, "Wprowadź hasło","Wprowadź ponownie hasło",QLineEdit::Password,"",&ok2);

    if (passwd1 != passwd2 )
        return;
    login->set_password( passwd1.toStdString() );

    QByteArray ba;
    ba.resize(fullMessage.ByteSize());
    fullMessage.SerializeToArray(ba.data(), ba.size() );

    socket->sendBinaryMessage(ba);
}
