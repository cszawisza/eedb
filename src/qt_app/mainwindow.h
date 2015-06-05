#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "addgroup.h"
#include "addparameter.h"
#include "messahehandler.h"
#include "qsciencespinbox.h"
#include "qengineerspinbox.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QWebSocket *getSocket() const;
    void setSocket(QWebSocket *ws);

public slots:
    void showAddGroup();
    void showAddParameter();

private:
    Ui::MainWindow *ui;
    AddGroup *addGroupWidget;
    AddParameterDialog *addParameter;
    MessaheHandler *handler;
    QScienceSpinBox *spinbox;
    QEngineerSpinBox *eSpinBox;
};

#endif // MAINWINDOW_H
