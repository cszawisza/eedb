#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QWebSocket>
#include <QtTest/QtTest>

#include <LoginDialog.hpp>
#include <CommunicationManagerMock.hpp>
#include <LoginVerificatorMock.hpp>
#include <UserRegisterMock.hpp>
#include <ISocketMock.hpp>
#include <ui_LoginDialog.h> // to get loginDialog UI definition

using namespace testing;

struct LoginDialogTestSuite : public ::testing::Test
{
    LoginDialogTestSuite();
    ~LoginDialogTestSuite(){
        delete m_sut;
    }

    StrictMock<LoginVerificatorMock> loginVerificatorMock;
    StrictMock<UserRegisterMock> userRegisterMock;
    QSharedPointer<SocketMock> webSocketMock;
    QSharedPointer<CommunicationManagerMock> communicationManager;
    LoginDialog *m_sut;
};

LoginDialogTestSuite::LoginDialogTestSuite()
    : loginVerificatorMock{},
      userRegisterMock{},
      webSocketMock(QSharedPointer<SocketMock>(new StrictMock<SocketMock>() )),
      communicationManager( QSharedPointer<CommunicationManagerMock>(new CommunicationManagerMock() ))
{
    EXPECT_CALL(*communicationManager, socket()).WillRepeatedly( Return(webSocketMock) );
    m_sut = new LoginDialog(loginVerificatorMock, communicationManager, userRegisterMock);
}

TEST_F(LoginDialogTestSuite, InvokeMainWindowAfterSuccesfullServerConnection)
{
    QSignalSpy buttonSpy(m_sut->getUi()->login, SIGNAL(clicked(bool)));
    QSignalSpy spy(m_sut, SIGNAL(loginSucces()));

    m_sut->getUi()->userLogin->setText("login");
    m_sut->getUi()->userPassword->setText("pass");
    EXPECT_CALL(*webSocketMock, open( _ ));
    EXPECT_CALL(loginVerificatorMock, tryLogin(m_sut->getUi()->userPassword->text().toStdString(),
                                               m_sut->getUi()->userLogin->text().toStdString())).WillOnce(Return(true));
    emit webSocketMock->opened();
    QTest::mouseClick(m_sut->getUi()->login, Qt::LeftButton);

    EXPECT_EQ(1, buttonSpy.count());
    //QVERIFY(buttonSpy.wait(10));
    EXPECT_EQ(1, spy.count());
}

TEST_F(LoginDialogTestSuite, DontInvokeMainWindowAfterSuccesfullServerConnection)
{
    QSignalSpy buttonSpy(m_sut->getUi()->login, SIGNAL(clicked(bool)));
    QSignalSpy spy(m_sut, SIGNAL(loginSucces()));

    m_sut->getUi()->userLogin->setText("login");
    m_sut->getUi()->userPassword->setText("pass");

    EXPECT_CALL(*(webSocketMock.data()), open( _ ));
    EXPECT_CALL(loginVerificatorMock, tryLogin(m_sut->getUi()->userPassword->text().toStdString(),
                                               m_sut->getUi()->userLogin->text().toStdString())).WillOnce(Return(false));
    emit webSocketMock->opened();
    QTest::mouseClick(m_sut->getUi()->login, Qt::LeftButton);

    EXPECT_EQ(1, buttonSpy.count());
    EXPECT_EQ(0, spy.count());
}

TEST_F(LoginDialogTestSuite, InvokeRegisterWindowAfterSuccesfullServerConnection)
{
    EXPECT_CALL(*(webSocketMock.data()), open( _ ));
    EXPECT_CALL(*(webSocketMock.data()), close( _ , _));

    EXPECT_CALL(userRegisterMock, registerUser());

    QSignalSpy buttonSpy(m_sut->getUi()->registerNewUser, SIGNAL(clicked(bool)));
    QTest::mouseClick(m_sut->getUi()->registerNewUser, Qt::LeftButton);

    emit webSocketMock->opened();
    EXPECT_EQ(1, buttonSpy.count());
}

//#include "LoginDialogTestSuite.moc"
