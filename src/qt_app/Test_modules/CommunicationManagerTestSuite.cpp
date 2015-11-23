#include <gtest/gtest.h>
#include <QByteArray>
#include <CommunicationManager.hpp>
#include "message_conteiner.pb.h"
#include "user.pb.h"
#include "ISocketMock.hpp"
#include <QSignalSpy>
using namespace testing;

struct CommunicationManagerTestSuite : public ::testing::Test
{
    MOCK_METHOD1(convertProtobufClientRequestsToQByteArrayMock, QByteArray(const pb::ClientRequests &));
    MOCK_METHOD1(convertQByteArrayToProtobufServerResponseMock, boost::optional<pb::ServerResponses>(const QByteArray &));

    CommunicationManagerTestSuite();
    QSharedPointer<SocketMock> webSocketMock;
    CommunicationManager m_sut;
};

CommunicationManagerTestSuite::CommunicationManagerTestSuite()
    : webSocketMock(QSharedPointer<SocketMock>(new StrictMock<SocketMock>() )),
      m_sut(webSocketMock,
            [this](const pb::ClientRequests & p_clientRequest)
                { return convertProtobufClientRequestsToQByteArrayMock(p_clientRequest);},
            [this](const QByteArray & p_serverResponse)
                { return convertQByteArrayToProtobufServerResponseMock(p_serverResponse);})
{
}

//TEST_F(CommunicationManagerTestSuite, signalAndSlotMechanismCheck ){
//    EXPECT_CALL( *(webSocketMock.data()), state() ).WillOnce( Return(QAbstractSocket::ConnectedState) );

//    QSignalSpy spy(&m_sut, SIGNAL( userRequestSent(RequestMetadata)));
//    m_sut.sendUserRequest( std::make_shared<pb::UserReq>() );
//}

TEST_F(CommunicationManagerTestSuite, ServerResponseParseError)
{
    QByteArray l_dummyArray{};
//    EXPECT_CALL(*this, convertQByteArrayToProtobufServerResponseMock(l_dummyArray)).WillOnce(Return(boost::none));
//    emit webSocketMock->binaryMessageReceived(l_dummyArray);
    ///TODO
}

//#include "CommunicationManagerTestSuite.moc"
