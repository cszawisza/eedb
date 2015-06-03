#ifndef TST_ITEM_H
#define TST_ITEM_H

#include <QObject>
#include <QTest>
#include <string>

#include "messages/item.h"
#include "messages/user.h"
#include "messages/package.h"
#include "messages/group.h"

class tst_item : public QObject
{
    Q_OBJECT
public:
    explicit tst_item(QObject *parent = 0);

signals:

public slots:

private slots:
    void initTestCase();
    void cleanupTestCase();

    void getParameters_givesEmptyMap();
    void insertParameter_insertsNewParameter();
    void insertSameParameter_changesParameterFromGivenId();
    void toArray_formsArray();
    void specialCharacters_HaveProperEncoding();

private:
    QByteArray *ba;
    QString longText;
    std::string str;
};

#endif // TST_ITEM_H
