#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDoubleSpinBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    addGroupWidget(new AddGroup),
    addParameter(new AddParameterDialog),
    handler(new MessaheHandler(this))
{
    ui->setupUi(this);

    connect(ui->actionAddGroup, SIGNAL(triggered()), this, SLOT(showAddGroup()));
    connect(ui->actionAddParameter, SIGNAL(triggered()), this, SLOT(showAddParameter()));

    connect(addParameter, SIGNAL(requestAvalible(MsgType,QByteArray)),
            handler, SLOT(queryMessage(MsgType,QByteArray)));
    connect(addParameter, SIGNAL(requestReady()),
            handler, SLOT(sendPandingMessages()));

    connect(handler, SIGNAL(recived_resAddParameter(QByteArray)),
            addParameter, SLOT(AddResponse(QByteArray)));
    connect(handler, SIGNAL(recived_resParameters(QByteArray)),
            addParameter, SLOT(SelectResponse(QByteArray)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAddGroup()
{
    addGroupWidget->show();
}

void MainWindow::showAddParameter()
{
    addParameter->show();
}

QWebSocket *MainWindow::getSocket() const
{
    return handler->getSocket();
}

void MainWindow::setSocket(QWebSocket *ws)
{
    handler->setSocket(ws);
    addParameter->requestParameters();

    handler->sendPandingMessages();
}
