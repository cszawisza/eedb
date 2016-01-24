#include <QInputDialog>
#include <QMessageBox>

#include "AddUserDialog.hpp"
#include "ui_AddUserDialog.h"
#include "CommunicationManager.hpp"

#include "DataStructures/Adapters/Protobuf/ClientRequestAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/UserRequestAdapter.hpp"

AddUserDialog::AddUserDialog(QSharedPointer<IUserCommunicationManager> p_communicatioManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog),
    m_communicatioManager(p_communicatioManager),
    stateMachine( new QStateMachine())
{
    ui->setupUi(this);
}

AddUserDialog::~AddUserDialog()
{
    delete ui;
}

QString AddUserDialog::name() const {
    return ui->name->text();
}

QString AddUserDialog::password() const
{
    return ui->password->text();
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
        msgBox.setText(QStringLiteral("Podaj nazwę użytkownika, hasło oraz email"));
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


    auto login = m_communicatioManager->newRequest()->user()->add();
    login->set_nickname( ui->name->text().toStdString() );
    login->set_email(ui->email->text().toStdString() );

    if(! ui->description->toPlainText().isEmpty())
        login->set_description( ui->description->toHtml().toStdString() );
    if(! ui->address->toPlainText().isEmpty() )
        login->set_address( ui->address->toPlainText().toStdString() );
    if(! ui->phonenumber->text().isEmpty() )
        login->set_phoneNumber( ui->phonenumber->text().toStdString() );

    bool ok, ok2;
    QString passwd1 = QInputDialog::getText(this,
                                            QStringLiteral("Wprowadź hasło"),
                                            QStringLiteral("Wprowadź hasło"),
                                            QLineEdit::Password,
                                            QStringLiteral(""),
                                            &ok);
    QString passwd2 = QInputDialog::getText(this,
                                            QStringLiteral("Wprowadź hasło"),
                                            QStringLiteral("Wprowadź ponownie hasło"),
                                            QLineEdit::Password,
                                            QStringLiteral(""),
                                            &ok2);

    if (passwd1 != passwd2 )
        return;
    login->set_password( passwd1.toStdString() );

    m_communicatioManager->sendRequest();
}
