#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QWebSocket>
#include <QtTest/QtTest>

#include <LoginDialog.hpp>
#include <CommunicationManagerMock.hpp>
#include <ui_LoginDialog.h> // to get loginDialog UI definition

using namespace testing;

struct LoginDialogTestSuite : public ::testing::Test
{
    LoginDialogTestSuite();
    StrictMock<CommunicationManagerMock> communicationManagerMock;
    StrictMock<QWebSocket> webSocketMock;
    LoginDialog m_sut;
};

LoginDialogTestSuite::LoginDialogTestSuite()
    : communicationManagerMock{},
      webSocketMock{},
      m_sut(communicationManagerMock, webSocketMock)
{}

TEST_F(LoginDialogTestSuite, SuccesServerConnection)
{
    QSignalSpy buttonSpy(m_sut.getUi()->login, SIGNAL(clicked(bool)));
    QTest::mouseClick(m_sut.getUi()->login, Qt::LeftButton);

    EXPECT_CALL(communicationManagerMock, handle());
    emit webSocketMock.connected();
    EXPECT_EQ(1, buttonSpy.count());
}

TEST_F(LoginDialogTestSuite, SuccesAfterStateChangeServerConnection)
{
    QSignalSpy buttonSpy(m_sut.getUi()->login, SIGNAL(clicked(bool)));
    QTest::mouseClick(m_sut.getUi()->login, Qt::LeftButton);

    EXPECT_CALL(communicationManagerMock, handle());
    emit webSocketMock.stateChanged(QAbstractSocket::ConnectedState);
    EXPECT_EQ(1, buttonSpy.count());
}

TEST_F(LoginDialogTestSuite, FailAfterStateChangeServerConnection)
{
    QSignalSpy buttonSpy(m_sut.getUi()->login, SIGNAL(clicked(bool)));
    QTest::mouseClick(m_sut.getUi()->login, Qt::LeftButton);

    emit webSocketMock.stateChanged(QAbstractSocket::ConnectingState);
    EXPECT_EQ(1, buttonSpy.count());
}

TEST_F(LoginDialogTestSuite, FailServerConnection)
{
    QSignalSpy buttonSpy(m_sut.getUi()->login, SIGNAL(clicked(bool)));
    QTest::mouseClick(m_sut.getUi()->login, Qt::LeftButton);

    EXPECT_EQ(1, buttonSpy.count());
}

#include "LoginDialogTestSuite.moc"
