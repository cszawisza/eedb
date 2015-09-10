#ifndef TST_MAGAZINE_H
#define TST_MAGAZINE_H

#include <QObject>
#include <QTest>

#include "messages/storage.h"

class tst_Magazine :public QObject
{
    Q_OBJECT
public:
    tst_Magazine(QObject *parent = 0);

private slots:
    void init();
    void cleanup();

    void storage_shoudHaveName();
    void setName_shoudSetName();

    void storage_shoudHaveID();

private:

    Storage *mag;
};

#endif // TST_MAGAZINE_H
