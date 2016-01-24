#pragma once

#include <QMainWindow>

class IUserCommunicationManager;

namespace Ui
{
class ApplicationMainWindow;
}

class ApplicationMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ApplicationMainWindow(QSharedPointer<IUserCommunicationManager> p_communicationManager,
                                   QWidget *parent = 0);
    ~ApplicationMainWindow();

private:
    Ui::ApplicationMainWindow *ui;
    QSharedPointer<IUserCommunicationManager> m_communicationManager;
};
