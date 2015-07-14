#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QWebSocket>
#include <QByteArray>
#include <CommunicationManager.hpp>
#include "message_conteiner.pb.h"
#include "user.pb.h"

using namespace testing;

struct CommunicationManagerTestSuite : public ::testing::Test
{
    MOCK_METHOD1(convertProtobufMsgToQByteArrayMock, QByteArray(const pb::ClientRequests &));
    MOCK_METHOD1(convertQByteArrayToProtobufMsgMock, boost::optional<pb::ServerResponses>(const QByteArray &));

    CommunicationManagerTestSuite();
    StrictMock<QWebSocket> webSocketMock;
    CommunicationManager m_sut;
};

CommunicationManagerTestSuite::CommunicationManagerTestSuite()
    : webSocketMock{},
      m_sut(webSocketMock,
            [this](const pb::ClientRequests & p_clientRequest)
                { return convertProtobufMsgToQByteArrayMock(p_clientRequest);},
            [this](const QByteArray & p_serverResponse)
                { return convertQByteArrayToProtobufMsgMock(p_serverResponse);})
{
    m_sut.handle();
}

TEST_F(CommunicationManagerTestSuite, zzz)
{
    const pb::ClientRequests & p_clientRequests{};
    QByteArray l_dummyArray(p_clientRequests.SerializeAsString().c_str(),
                            p_clientRequests.ByteSize());

    EXPECT_CALL(*this, convertQByteArrayToProtobufMsgMock(l_dummyArray)).WillOnce(Return(boost::none));
    emit webSocketMock.binaryMessageReceived(l_dummyArray);
    EXPECT_TRUE(true);
}

//TEST_F(LoginDialogTestSuite, SuccesAfterStateChangeServerConnection)
//{
//    QSignalSpy buttonSpy(m_sut.getUi()->login, SIGNAL(clicked(bool)));
//    QTest::mouseClick(m_sut.getUi()->login, Qt::LeftButton);

//    EXPECT_CALL(communicationManagerMock, handle());
//    emit webSocketMock.stateChanged(QAbstractSocket::ConnectedState);
//    EXPECT_EQ(1, buttonSpy.count());
//}

//TEST_F(LoginDialogTestSuite, FailAfterStateChangeServerConnection)
//{
//    QSignalSpy buttonSpy(m_sut.getUi()->login, SIGNAL(clicked(bool)));
//    QTest::mouseClick(m_sut.getUi()->login, Qt::LeftButton);

//    emit webSocketMock.stateChanged(QAbstractSocket::ConnectingState);
//    EXPECT_EQ(1, buttonSpy.count());
//}

//TEST_F(LoginDialogTestSuite, FailServerConnection)
//{
//    QSignalSpy buttonSpy(m_sut.getUi()->login, SIGNAL(clicked(bool)));
//    QTest::mouseClick(m_sut.getUi()->login, Qt::LeftButton);

//    EXPECT_EQ(1, buttonSpy.count());
//}

#include "CommunicationManagerTestSuite.moc"
