#include "ApplicationMainWindow.hpp"
#include "ui_ApplicationMainWindow.h"

ApplicationMainWindow::ApplicationMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ApplicationMainWindow)
{
    ui->setupUi(this);
}

ApplicationMainWindow::~ApplicationMainWindow()
{
    delete ui;
}
