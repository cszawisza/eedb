#ifndef ADDGROUP_H
#define ADDGROUP_H

#include <QWidget>

namespace Ui {
class AddGroup;
}

class AddGroup : public QWidget
{
    Q_OBJECT

public:
    explicit AddGroup(QWidget *parent = 0);
    ~AddGroup();

private:
    Ui::AddGroup *ui;
};

#endif // ADDGROUP_H
