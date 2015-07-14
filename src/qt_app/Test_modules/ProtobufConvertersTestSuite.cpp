#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QByteArray>
#include "message_conteiner.pb.h"
#include "user.pb.h"
#include <ProtobufConverters.hpp>

using namespace testing;

struct ProtobufConvertersTestSuite : public ::testing::Test
{
    ProtobufConvertersTestSuite();
    const int basicId = 17;
    pb::UserBasic m_basic{};
    pb::MsgUserRequest::Add m_add{};
    pb::MsgUserRequest m_msgUerRequest{};
    pb::ClientRequest m_clientRequest{};

    pb::ClientRequests m_clientRequests{};
};

ProtobufConvertersTestSuite::ProtobufConvertersTestSuite()
{
    m_clientRequests.mutable_request()->Add();
    m_clientRequests.mutable_request(0)->mutable_msguserreq()->mutable_add()->mutable_basic()->set_id(11);
//    m_clientRequests.request(0).set_requestid(basicId);
//    m_clientRequests.mutable_request()->AddAllocated(&m_clientRequest);


    //m_clientRequests.request(0).set_requestid(basicId);
    //p_clientRequest.set_requestid(1);
}


TEST_F(ProtobufConvertersTestSuite, EmptyClientRequest)
{
    const pb::ClientRequests & l_emptyClientRequests{};
    QByteArray l_emptyArray(m_clientRequests.SerializeAsString().c_str(),
                            m_clientRequests.ByteSize());
    EXPECT_EQ(l_emptyArray, convertProtobufMsgToQByteArray(m_clientRequests));
}

//TEST(ProtobufConvertersTestSuite, SuccesConversionFromQByteArrayToProtobuf)
//{
//    const pb::ClientRequests & p_clientRequests{};
//    QByteArray l_dummyArray(p_clientRequests.SerializeAsString().c_str(),
//                            p_clientRequests.ByteSize());

//    EXPECT_CALL(*this, convertQByteArrayToProtobufMsgMock(l_dummyArray)).WillOnce(Return(boost::none));
//    emit webSocketMock.binaryMessageReceived(l_dummyArray);
//    EXPECT_TRUE(true);
//}

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

#include "ProtobufConvertersTestSuite.moc"
