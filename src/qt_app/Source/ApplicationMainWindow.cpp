#include "ApplicationMainWindow.hpp"
#include <ICommunicationManager.hpp>
#include "ui_ApplicationMainWindow.h"

ApplicationMainWindow::ApplicationMainWindow(const ICommunicationManager & p_communicationManager,
                                             QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ApplicationMainWindow),
    m_communicationManager(p_communicationManager)
{
    ui->setupUi(this);
}

ApplicationMainWindow::~ApplicationMainWindow()
{
    delete ui;
}
