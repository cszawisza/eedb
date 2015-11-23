#pragma once

#include <QMainWindow>

class ICommunicationManager;

namespace Ui
{
class ApplicationMainWindow;
}

class ApplicationMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ApplicationMainWindow(QSharedPointer<ICommunicationManager> p_communicationManager,
                                   QWidget *parent = 0);
    ~ApplicationMainWindow();

private:
    Ui::ApplicationMainWindow *ui;
    QSharedPointer<ICommunicationManager> m_communicationManager;
};
