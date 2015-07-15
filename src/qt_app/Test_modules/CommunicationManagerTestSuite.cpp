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
    MOCK_METHOD1(convertProtobufClientRequestsToQByteArrayMock, QByteArray(const pb::ClientRequests &));
    MOCK_METHOD1(convertQByteArrayToProtobufServerResponseMock, boost::optional<pb::ServerResponses>(const QByteArray &));

    CommunicationManagerTestSuite();
    StrictMock<QWebSocket> webSocketMock;
    CommunicationManager m_sut;
};

CommunicationManagerTestSuite::CommunicationManagerTestSuite()
    : webSocketMock{},
      m_sut(webSocketMock,
            [this](const pb::ClientRequests & p_clientRequest)
                { return convertProtobufClientRequestsToQByteArrayMock(p_clientRequest);},
            [this](const QByteArray & p_serverResponse)
                { return convertQByteArrayToProtobufServerResponseMock(p_serverResponse);})
{
    m_sut.handle();
}

TEST_F(CommunicationManagerTestSuite, ServerResponseParseError)
{
    const pb::ClientRequests & p_clientRequests{};
    QByteArray l_dummyArray{};
    EXPECT_CALL(*this, convertQByteArrayToProtobufServerResponseMock(l_dummyArray)).WillOnce(Return(boost::none));
    emit webSocketMock.binaryMessageReceived(l_dummyArray);
    // to do
}

#include "CommunicationManagerTestSuite.moc"
