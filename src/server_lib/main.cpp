#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QAbstractSocket>
//#include "qcatalogserver.h"


int keepassx_main_impl(int argc, char *argv[], int (*app_run)() )
{
    QCoreApplication a(argc, argv);

    QCoreApplication::setApplicationName(QStringLiteral("EKATALOG"));
    QCoreApplication::setOrganizationName(QStringLiteral("BAPP"));

    QFile *prog;
    QString *msg;

    prog = new QFile(argv [0]);
    msg = new QString();

    msg->append(QStringLiteral("Program ma wielkość "));
    msg->append(QString::number(prog->size()));
    msg->append(QStringLiteral(" bajtów, czyli "));
    msg->append(QString::number((double)prog->size()/1024));
    msg->append(QStringLiteral(" kilobajtów\n"));
    msg->append(QStringLiteral("Został skompilowany w dniu "));
    msg->append(QStringLiteral(__DATE__));
    msg->append(QStringLiteral(" o godzinie "));
    msg->append(QStringLiteral(__TIME__));
    msg->append(QStringLiteral("\nna kompilatorze GCC w wersji "));
    msg->append(QStringLiteral(__VERSION__));
    msg->append(QStringLiteral("\nkożystając z QT w wersji "));
    msg->append(QT_VERSION_STR);
    qDebug() << msg->toUtf8();

    delete prog;
    delete msg;

//    QCatalogServer server;
//    try{
//        server.startServer();
//    }
//    catch(QWebSocketProtocol::CloseCode e){
//        qDebug() << "QWebSocket throw error :" << e << " exiting";
//        exit(1);
//    }

    return app_run();
}

int qApp_exec(){
    return qApp->exec();
}

int keepassx_main(int argc, char** argv ){
    return keepassx_main_impl(argc,argv,qApp_exec);
}
