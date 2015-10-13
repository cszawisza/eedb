#include "CategoryWidget.hpp"
#include "ui_CategoryWidget.h"

CategoryWidget::CategoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CategoryWidget)
{
    ui->setupUi(this);
}

CategoryWidget::~CategoryWidget()
{
    delete ui;
}
