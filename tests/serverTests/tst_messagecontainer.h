#ifndef TST_MESSAGECONTAINER_H
#define TST_MESSAGECONTAINER_H

#include <QObject>

#include "messages/messagescontainer.h"


class tst_MessageContainer : public QObject
{
    Q_OBJECT
public:
    explicit tst_MessageContainer(QObject *parent = 0);

signals:

public slots:

private slots:
    void init();
    void containerIsEmptyByDefault();
    void addCapsule_incrementSize();
    void deserialize_givesSameData();
    void serializeBigData_givesDataWithProtocolImpact();
    void extractCapcule_givesBackData();
    void extractBigCapsule_givesData();
    void dataStaysAfterDeserialization();
    void toArrayByPointer_benchmark();
    void toArrayByReference_benchmark();

    void registerUserMessage();
private:
    MessagesContainer m_con;
//    MessageCapsule m_cap;

};

#endif // TST_MESSAGECONTAINER_H
