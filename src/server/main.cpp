#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QAbstractSocket>
#include "core/server.h"

int keepassx_main_impl(int argc, char *argv[], int (*app_run)() )
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("eedb"));
    QCoreApplication::setOrganizationName(QStringLiteral("eedb"));

    EEDB server;
    try{
        server.startServer();
    }
    catch(QWebSocketProtocol::CloseCode e){
        qDebug() << "QWebSocket throw error :" << e << " exiting";
        exit(1);
    }

    return app_run();
}

int qApp_exec(){
    return qApp->exec();
}

int keepassx_main(int argc, char** argv ){
    return keepassx_main_impl(argc,argv,qApp_exec);
}
