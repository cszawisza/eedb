#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QWebSocket>
#include <QtTest/QtTest>

#include <LoginDialog.hpp>
#include <LoginVerificatorMock.hpp>
#include <ui_LoginDialog.h> // to get loginDialog UI definition

using namespace testing;

struct LoginDialogTestSuite : public ::testing::Test
{
    LoginDialogTestSuite();
    StrictMock<LoginVerificatorMock> loginVerificatorMock;
    StrictMock<QWebSocket> webSocketMock;
    LoginDialog m_sut;
};

LoginDialogTestSuite::LoginDialogTestSuite()
    : loginVerificatorMock{},
      webSocketMock{},
      m_sut(loginVerificatorMock, webSocketMock)
{}

TEST_F(LoginDialogTestSuite, InvokeMainWindowAfterSuccesfullServerConnection)
{
    m_sut.getUi()->userLogin->setText("login");
    m_sut.getUi()->userPassword->setText("pass");
    EXPECT_CALL(loginVerificatorMock, tryLogin(m_sut.getUi()->userPassword->text().toStdString(),
                                               m_sut.getUi()->userLogin->text().toStdString())).WillOnce(Return(true));
    QSignalSpy buttonSpy(m_sut.getUi()->login, SIGNAL(clicked(bool)));
    QTest::mouseClick(m_sut.getUi()->login, Qt::LeftButton);

    //QSignalSpy spy(m_sut.getUi(), SIGNAL(loginSucces()));
    //QCOMPARE(spy.count(), 1);

    emit webSocketMock.connected();
    EXPECT_EQ(1, buttonSpy.count());
}

TEST_F(LoginDialogTestSuite, DontInvokeMainWindowAfterSuccesfullServerConnection)
{
    m_sut.getUi()->userLogin->setText("login");
    m_sut.getUi()->userPassword->setText("pass");
    EXPECT_CALL(loginVerificatorMock, tryLogin(m_sut.getUi()->userPassword->text().toStdString(),
                                               m_sut.getUi()->userLogin->text().toStdString())).WillOnce(Return(false));
    QSignalSpy buttonSpy(m_sut.getUi()->login, SIGNAL(clicked(bool)));
    QTest::mouseClick(m_sut.getUi()->login, Qt::LeftButton);

    emit webSocketMock.connected();
    EXPECT_EQ(1, buttonSpy.count());
}

//TEST_F(LoginDialogTestSuite, SuccesServerConnection)
//{
//    m_sut.getUi()->userLogin->setText("login");
//    m_sut.getUi()->userPassword->setText("pass");
//    EXPECT_CALL(loginVerificatorMock, tryLogin(m_sut.getUi()->userPassword->text().toStdString(),
//                                               m_sut.getUi()->userLogin->text().toStdString())).WillOnce(Return(false));
//    QSignalSpy buttonSpy(m_sut.getUi()->login, SIGNAL(clicked(bool)));
//    QTest::mouseClick(m_sut.getUi()->login, Qt::LeftButton);

//    emit webSocketMock.connected();
//    EXPECT_EQ(1, buttonSpy.count());
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

//#include "LoginDialogTestSuite.moc"
