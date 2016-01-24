#include <gtest/gtest.h>

#include <CommunicationManager.hpp>

#include <QByteArray>
#include <QSignalSpy>

#include "ISocketMock.hpp"
#include "ISerializableDataMock.hpp"
#include "utils/Url.hpp"

using namespace testing;

struct CommunicationManagerTestSuite : public ::testing::Test
{
    CommunicationManagerTestSuite();
    QSharedPointer<SocketMock> webSocketMock;
    SerializableDataMock serializeMock;
    CommunicationManager m_sut;
};

CommunicationManagerTestSuite::CommunicationManagerTestSuite()
    : webSocketMock(QSharedPointer<SocketMock>(new StrictMock<SocketMock>() )),
      m_sut(webSocketMock )
{
}

TEST_F(CommunicationManagerTestSuite, connectCalsOpenSocket){
    EXPECT_CALL(*webSocketMock, open(_));
    Url url;
    m_sut.openConnection(url);
}

TEST_F(CommunicationManagerTestSuite, closeConnectionWhenInConnectedState){
    EXPECT_CALL(*webSocketMock, state()).WillOnce(Return(QAbstractSocket::ConnectedState));
    EXPECT_CALL(*webSocketMock, close(_,_));

    m_sut.closeConnection();
}

TEST_F(CommunicationManagerTestSuite, signalAndSlotMechanismCheck ){
//    EXPECT_CALL( *(webSocketMock.data()), state() ).WillOnce( Return(QAbstractSocket::ConnectedState) );
//    EXPECT_CALL( serializeMock, serialize() ).WillOnce(Return(QByteArray()));

//    QSignalSpy spy(&m_sut, SIGNAL( userRequestSent(RequestMetadata)));
//    m_sut.sendRequest( &serializeMock );
}

TEST_F(CommunicationManagerTestSuite, ServerResponseParseError)
{
//    QByteArray l_dummyArray{};
//    EXPECT_CALL(*m_deserializer, parseFromArray(l_dummyArray)).WillOnce(Return(boost::none));
//    emit webSocketMock->binaryMessageReceived(l_dummyArray);
}

//#include "CommunicationManagerTestSuite.moc"
