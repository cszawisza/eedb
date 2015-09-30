#pragma once

#include <QMainWindow>

namespace Ui
{
class ApplicationMainWindow;
}

class ApplicationMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ApplicationMainWindow(QWidget *parent = 0);
    ~ApplicationMainWindow();

private:
    Ui::ApplicationMainWindow *ui;
};
