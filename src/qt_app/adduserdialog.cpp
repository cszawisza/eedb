#include "adduserdialog.h"
#include "ui_adduserdialog.h"

#include "messages/userregistrationmessage.h"
#include "messages/messagescontainer.h"
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
    MessagesContainer mc;
    mc.fromArray(msg);
    for(int i = 0; i<mc.capsules().size();++i){
        if(mc.getCapsule(i).msgtype() == MsgType::resAddUser ){
            qDebug()<<" got add user response";
            protbuf::RegisterResponse res;
            res.ParseFromString(mc.getCapsule(i).data());
            for(int j = 0 ; j<res.replay_size();j++){
                if(res.replay(j) == protbuf::Replay::EmailExists){
                    ui->status->setText("User email exists");
                }
                else if(res.replay(j) == protbuf::Replay::EmailAddressToLong ){
                    ui->status->setText("Email to long");
                }
                else if(res.replay(j) == protbuf::Replay::EmailNotValidate){
                    ui->status->setText("Email not validate");
                }
                else if(res.replay(j) == protbuf::Replay::UserNameToLong){
                    ui->status->setText("User name to long");
                }
                else if(res.replay(j) == protbuf::Replay::UserNameToShort){
                    ui->status->setText("User name to short");
                }
                else if(res.replay(j) == protbuf::Replay::PasswordToShort){
                    ui->status->setText("User has to short password");
                }
                else if(res.replay(j) == protbuf::Replay::UserAlreadyExists){
                    ui->status->setText("User name exists");
                }
                else if (res.replay(j) == protbuf::Replay::UserAddOk ){
                    ui->status->setText("USER CREATED!!");
                }
            }
        }
    }
}

AddUserDialog::~AddUserDialog()
{
    disconnect(socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(readyRead(QByteArray)));
    delete ui;
}

void AddUserDialog::on_registerNewUser_clicked()
{
    UserRegistrationMessage reg;
    reg.Clear();
    MessagesContainer mc;

    bool hasErrors = false;

    if(ui->name->text().size()<4 || ui->name->text().size() > 34 )
    {
        ui->name->setStyleSheet("background-color : red;");
        hasErrors = true;
    }
    else{
        ui->name->setStyleSheet("background-color : white;");
    }

    if(ui->email->text().size()<7 || ui->email->text().size() > 255 ) /// TODO: add email validator
    {
        ui->email->setStyleSheet("background-color : red;");
        hasErrors = true;
    }
    else{
        ui->email->setStyleSheet("background-color : white;");
    }

    if (hasErrors)
        return;

    bool ok, ok2;
    QString passwd1 = QInputDialog::getText(this, "Wprowadź hasło","Wprowadź hasło",QLineEdit::Password,"",&ok);
    QString passwd2 = QInputDialog::getText(this, "Wprowadź hasło","Wprowadź ponownie hasło",QLineEdit::Password,"",&ok2);

    if (passwd1 != passwd2 )
        return;

    reg.set_name(ui->name->text() );
    reg.set_email(ui->email->text() );
    reg.set_password(passwd1);

    if(ui->address->toPlainText().size())
        reg.set_address(ui->address->toPlainText() );
    if(ui->description->toPlainText().size())
        reg.set_description(ui->description->toPlainText());
    if(ui->phonenumber->text().size())
        reg.set_phonenumber(ui->phonenumber->text());

    if(!reg.IsInitialized()){
        qDebug()<<" message is not initialized!";
        return;
    }
    if(reg.password().size()==0){
        qDebug()<<" password size is 0";
        return;
    }

    mc.addMessage(MsgType::addUser, reg.toArray());

    int bytesSent = socket->sendBinaryMessage(mc.toArray());
    qDebug()<<"Sent bytes: "<< bytesSent;
}
