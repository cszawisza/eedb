#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QTimer>
#include <QByteArray>

#include <LoginDialog.hpp>
#include <CommunicationManager.hpp>
#include <LoginVerificator.hpp>
#include <ApplicationMainWindow.hpp>
#include <UserRegister.hpp>
#include <WebSocket.hpp>

#include <Adapters/Protobuf/ClientRequestAdapter.hpp>
#include <Adapters/Protobuf/ServerResponseAdapter.hpp>

#include <memory>

namespace
{

void showHelloMessage(const char *argv)
{
    QFile prog(QString::fromLatin1(argv));
    QString msg{};

    msg.append(QStringLiteral("Program ma wielkość "));
    msg.append(QString::number(prog.size()));
    msg.append(QStringLiteral(" bajtów, czyli "));
    msg.append(QString::number(static_cast<double>(prog.size()/1024)));
    msg.append(QStringLiteral(" kilobajtów\n"));
    msg.append(QStringLiteral("Został skompilowany w dniu "));
    msg.append(QStringLiteral(__DATE__));
    msg.append(QStringLiteral(" o godzinie "));
    msg.append(QStringLiteral(__TIME__));
    msg.append(QStringLiteral("\nna kompilatorze GCC w wersji "));
    msg.append(QStringLiteral(__VERSION__));
    msg.append(QStringLiteral("\nkorzystając z QT w wersji "));
    msg.append(QStringLiteral(QT_VERSION_STR));
    qDebug() << msg.toUtf8();
}

void killApp(QApplication &a)
{
    QTimer::singleShot(1, &a, SLOT(quit()));
    a.exec();
}

void showMainWindow(QApplication &a, QSharedPointer<ICommunicationManager> l_communicationManager)
{
    ApplicationMainWindow l_mainApp(l_communicationManager);
    l_mainApp.show();
    a.exec();
}

void showLoginDialog(QApplication &a)
{
    QSharedPointer<ISocket> l_webSocket = QSharedPointer<ISocket>(new WebSocket());

    QSharedPointer<ICommunicationManager>  l_communicationManager =
            QSharedPointer<ICommunicationManager>(
                new CommunicationManager(l_webSocket ));
    LoginVerificator l_loginVerificator;
    UserRegister l_userRegisterDialog;

    auto *lDialog = new LoginDialog(l_loginVerificator, l_communicationManager, l_userRegisterDialog);

    if(lDialog->exec() != QDialog::Accepted )
        killApp(a);
    else{
        lDialog->deleteLater();
        showMainWindow(a, l_communicationManager);
    }
}

} // anonymous

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("EKATALOG"));
    QCoreApplication::setOrganizationName(QStringLiteral("BAPP"));
    showHelloMessage(argv[0]);
    showLoginDialog(a);
}
