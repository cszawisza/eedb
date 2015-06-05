//#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QTimer>
#include "logindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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

//    MainWindow *w;
    LoginDialog *lDialog = new LoginDialog();
    if(lDialog->exec()){
//        w = new MainWindow();
//        w->setSocket(lDialog->socket());
//        w->show();
    }
    else{
        QTimer::singleShot(1,&a,SLOT(quit()));
    }
    delete lDialog;
    return a.exec();
}
