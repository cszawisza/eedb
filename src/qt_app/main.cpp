#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QTimer>
#include <QByteArray>
#include <LoginDialog.hpp>
#include <CommunicationManager.hpp>
#include "ApplicationMainWindow.hpp"
#include <QWebSocket>
#include <ProtobufConverters.hpp>

namespace
{

void showHelloMessage(const char *argv)
{
    QFile prog(argv);
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
    msg.append(QT_VERSION_STR);
    qDebug() << msg.toUtf8();
}

void showLoginDialog(QApplication &a, ApplicationMainWindow & p_mainApp)
{
    QWebSocket l_webSocket("EKatalog client");
    auto l_protobufToQbyteArrayConverter = [](const pb::ClientRequests & p_clientRequests)
    {
        return convertProtobufClientRequestsToQByteArray(p_clientRequests);
    };
    auto l_qbyteArrayToProtobufConverter = [](const QByteArray & p_serverResponse)
    {
        return convertQByteArrayToProtobufServerResponse(p_serverResponse);
    };
    CommunicationManager l_communicationManager(l_webSocket,
                                                l_protobufToQbyteArrayConverter,
                                                l_qbyteArrayToProtobufConverter);
    LoginDialog lDialog(l_communicationManager, l_webSocket);
    QObject::connect(&lDialog, SIGNAL(showOtherWindow()), &p_mainApp, SLOT(show()));
    lDialog.exec();
    if(!a.exec())
    {
        QTimer::singleShot(1, &a, SLOT(quit()));
    }
}

} // anonymous

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ApplicationMainWindow l_mainApp{};

    QCoreApplication::setApplicationName(QStringLiteral("EKATALOG"));
    QCoreApplication::setOrganizationName(QStringLiteral("BAPP"));
    showHelloMessage(argv[0]);
    showLoginDialog(a, l_mainApp);
}
