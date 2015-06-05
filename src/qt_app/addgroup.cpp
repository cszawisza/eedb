#include "addgroup.h"
#include "ui_addgroup.h"

AddGroup::AddGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddGroup)
{
    ui->setupUi(this);
}

AddGroup::~AddGroup()
{
    delete ui;
}
