#ifndef TST_ITEMPACKAGE_H
#define TST_ITEMPACKAGE_H

#include <QObject>
#include <QTest>

#include "messages/item.h"
#include "messages/user.h"
#include "messages/package.h"
#include "messages/group.h"


class tst_ItemPackage : public QObject
{
    Q_OBJECT
public:
    explicit tst_ItemPackage(QObject *parent = 0);

signals:

public slots:

};

#endif // TST_ITEMPACKAGE_H
