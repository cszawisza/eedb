#ifndef CATEGORYWIDGET_HPP
#define CATEGORYWIDGET_HPP

#include <QWidget>

namespace Ui {
class CategoryWidget;
}

class CategoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CategoryWidget(QWidget *parent = 0);
    ~CategoryWidget();

private:
    Ui::CategoryWidget *ui;
};

#endif // CATEGORYWIDGET_HPP
