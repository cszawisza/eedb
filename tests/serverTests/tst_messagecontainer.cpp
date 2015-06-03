#include "tst_messagecontainer.h"

#include <QTest>
#include <QtCore>

tst_MessageContainer::tst_MessageContainer(QObject *parent) :
    QObject(parent)
{
}

void tst_MessageContainer::init()
{
    m_con.Clear();
}

QString getRandomData(){
    QByteArray ba;
    qsrand(1);

    for(int i = 0;i < 1*1024*1024; i++){
        ba.append(char(qrand()%255));
    }
    return QString::fromLatin1(ba);
}

void tst_MessageContainer::containerIsEmptyByDefault()
{
    QVERIFY(m_con.capsules().size() == 0 );
}

void tst_MessageContainer::addCapsule_incrementSize()
{
    m_con.addMessage(MsgType::addUser, QByteArray(2,'a'));
    QVERIFY(m_con.capsules().size() == 1);
}

void tst_MessageContainer::deserialize_givesSameData()
{
    QString message = "SOME MESSAGEłłĄŚŁĆŁŚÐƏÐŒ¾¾¿";
    MsgType type = MsgType::addUser;
    m_con.addMessage(type, message );

    QByteArray ba = m_con.toArray();

    MessagesContainer ret;
    ret.fromArray(ba);

    QVERIFY(ret.capsules().size() == 1);
    QVERIFY(ret.capsules(0).data() == m_con.capsules(0).data());
}

void tst_MessageContainer::serializeBigData_givesDataWithProtocolImpact()
{
    QString message = getRandomData();
    MsgType type = MsgType::addUser;
    m_con.addMessage(type, message.toLatin1() );

    QByteArray ba = m_con.toArray();

    QVERIFY(ba.size() == m_con.ByteSize() );
}

void tst_MessageContainer::extractCapcule_givesBackData()
{
    QString message = "SOME MESSAGEŚĆ‘¿¿°£±¼¾±¾¿¾£±°±£Œ°ĘŒ↔ÐŚƏ∞Ć∞Ć∞";
    QByteArray bMessage = "SOME MESSAGEŚĆ‘¿¿°£±¼¾±¾¿¾£±°±£Œ°ĘŒ↔ÐŚƏ∞Ć∞Ć∞";
    MsgType type = MsgType::addUser;

    m_con.addMessage(type, message );
    m_con.addMessage(type, bMessage );
    QVERIFY(m_con.capsules().size() == 2);

    QString ret1 = QString::fromStdString(m_con.getCapsule(0).data());
    QString ret2 = QString::fromStdString(m_con.getCapsule(1).data());
    QByteArray ret4 = m_con.getCapsule(0).getData();
    QByteArray ret5 = m_con.getCapsule(1).getData();
    QVERIFY(ret1 == message);
    QVERIFY(ret2 == message);
    QVERIFY(ret4 == bMessage);
    QVERIFY(ret5 == bMessage);
    QVERIFY(ret1 == ret4);
}

void tst_MessageContainer::extractBigCapsule_givesData()
{
    QString message = getRandomData();
    MsgType type = MsgType::addUser;

    m_con.addMessage(type, message );

    QVERIFY(m_con.capsules().size() == 1);

    QString ret1 = QString::fromStdString(m_con.getCapsule(0).data());
    QByteArray ret2 = m_con.getCapsule(0).getData();
    QString ret3 = m_con.getCapsule(0).getData();

    QVERIFY(ret1 == message);
    QVERIFY(ret2 == ret1);
    QVERIFY(ret3 == ret2);
}

void tst_MessageContainer::dataStaysAfterDeserialization()
{
    QString message = getRandomData();
    MsgType type = MsgType::addUser;
    m_con.addMessage(type, message );

    QByteArray ba = m_con.toArray();

    MessagesContainer mc;
    mc.fromArray(ba);

    QString s1 = QString::fromStdString( mc.getCapsule(0).data() );
    QString s2 = QString::fromStdString( m_con.getCapsule(0).data() );
    QVERIFY(s1 == s2);
    QVERIFY(s1 == message );

}

QByteArray tmessage = getRandomData().toLatin1();
MsgType ttype = MsgType::addUser;
QByteArray *tba = new QByteArray();
QByteArray rba;

void tst_MessageContainer::toArrayByPointer_benchmark()
{
    QBENCHMARK{
        m_con.addMessage(ttype, tmessage);
        m_con.toArray(tba);
        MessagesContainer mc;
        mc.fromArray(tba);
        m_con.Clear();
    }
}

void tst_MessageContainer::toArrayByReference_benchmark()
{
    QBENCHMARK{
        m_con.addMessage(ttype, tmessage);
        rba = m_con.toArray();
        MessagesContainer mc;
        mc.fromArray(tba);
        m_con.Clear();
    }
}

#include "messages/userregistrationmessage.h"

void tst_MessageContainer::registerUserMessage()
{
    UserRegistrationMessage msg;
    msg.set_name("stefan");
    msg.set_password("aaaa");
    msg.set_email("email@com.pl");
    msg.set_address(getRandomData());
    msg.set_description(getRandomData());

    MsgType type = MsgType::addUser;

    m_con.addMessage(type, msg.toArray() );

    QVERIFY(m_con.capsules().size() == 1);

    QString ret1 = QString::fromStdString(m_con.getCapsule(0).data());
    QByteArray ret2 = m_con.getCapsule(0).getData();
    QString ret3 = m_con.getCapsule(0).getData();

    QVERIFY(ret1 == QString::fromStdString( msg.SerializeAsString() ) );
    QVERIFY(ret2 == ret1);
    QVERIFY(ret3 == ret2);;
}
