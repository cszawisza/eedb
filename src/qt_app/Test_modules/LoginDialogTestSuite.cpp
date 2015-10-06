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
    QSignalSpy buttonSpy(m_sut.getUi()->login, SIGNAL(clicked(bool)));
    QSignalSpy spy(&m_sut, SIGNAL(loginSucces()));

    m_sut.getUi()->userLogin->setText("login");
    m_sut.getUi()->userPassword->setText("pass");
    EXPECT_CALL(loginVerificatorMock, tryLogin(m_sut.getUi()->userPassword->text().toStdString(),
                                               m_sut.getUi()->userLogin->text().toStdString())).WillOnce(Return(true));
    emit webSocketMock.connected();
    QTest::mouseClick(m_sut.getUi()->login, Qt::LeftButton);

    EXPECT_EQ(1, buttonSpy.count());
    //QVERIFY(buttonSpy.wait(10));
    EXPECT_EQ(1, spy.count());
}

TEST_F(LoginDialogTestSuite, DontInvokeMainWindowAfterSuccesfullServerConnection)
{
    QSignalSpy buttonSpy(m_sut.getUi()->login, SIGNAL(clicked(bool)));
    QSignalSpy spy(&m_sut, SIGNAL(loginSucces()));

    m_sut.getUi()->userLogin->setText("login");
    m_sut.getUi()->userPassword->setText("pass");
    EXPECT_CALL(loginVerificatorMock, tryLogin(m_sut.getUi()->userPassword->text().toStdString(),
                                               m_sut.getUi()->userLogin->text().toStdString())).WillOnce(Return(false));
    emit webSocketMock.connected();
    QTest::mouseClick(m_sut.getUi()->login, Qt::LeftButton);

    EXPECT_EQ(1, buttonSpy.count());
    EXPECT_EQ(0, spy.count());
}

//#include "LoginDialogTestSuite.moc"
