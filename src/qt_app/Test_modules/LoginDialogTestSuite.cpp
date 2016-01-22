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
    QSharedPointer<CommunicationManagerMock> communicationManager;
    LoginDialog *m_sut;

    void goToLoginState(){
        EXPECT_CALL(*communicationManager, openConnection(_));

        QEventLoop loop;

        QTimer::singleShot(1,&loop, [&](){
            loop.exit();
        });
        loop.exec();

        emit communicationManager->socketConnected();

        QTimer::singleShot(1,&loop, [&](){
            loop.exit();
        });
        loop.exec();

    }
};

LoginDialogTestSuite::LoginDialogTestSuite()
    : loginVerificatorMock{},
      userRegisterMock{},
      communicationManager( QSharedPointer<CommunicationManagerMock>(new CommunicationManagerMock() ))
{
    m_sut = new LoginDialog(loginVerificatorMock, communicationManager, userRegisterMock);
}

TEST_F(LoginDialogTestSuite, goToLoginStateTest){
    this->goToLoginState();
}

TEST_F(LoginDialogTestSuite, InvokeMainWindowAfterSuccesfullServerConnection)
{
    this->goToLoginState();
    QSignalSpy buttonSpy(m_sut->getUi()->login, SIGNAL(clicked(bool)));
    QSignalSpy spy(m_sut, SIGNAL(loginSucces()));

    m_sut->getUi()->userLogin->setText(QStringLiteral("login"));
    m_sut->getUi()->userPassword->setText(QStringLiteral("pass"));
    EXPECT_CALL(loginVerificatorMock, tryLogin(m_sut->getUi()->userPassword->text().toStdString(),
                                               m_sut->getUi()->userLogin->text().toStdString())).WillOnce(Return(true));

    QTest::mouseClick(m_sut->getUi()->login, Qt::LeftButton);
    spy.wait(10);

    EXPECT_EQ(1, buttonSpy.count());
    EXPECT_EQ(1, spy.count());
}

TEST_F(LoginDialogTestSuite, DontInvokeMainWindowAfterSuccesfullServerConnection)
{
    this->goToLoginState();
    QSignalSpy buttonSpy(m_sut->getUi()->login, SIGNAL(clicked(bool)));
    QSignalSpy spy(m_sut, SIGNAL(loginSucces()));

    m_sut->getUi()->userLogin->setText(QStringLiteral("login"));
    m_sut->getUi()->userPassword->setText(QStringLiteral("pass"));

    EXPECT_CALL(loginVerificatorMock, tryLogin(m_sut->getUi()->userPassword->text().toStdString(),
                                               m_sut->getUi()->userLogin->text().toStdString())).WillOnce(Return(false));

    QTest::mouseClick(m_sut->getUi()->login, Qt::LeftButton);

    EXPECT_EQ(1, buttonSpy.count());
    EXPECT_EQ(0, spy.count());
}

//TEST_F(LoginDialogTestSuite, InvokeRegisterWindowAfterSuccesfullServerConnection)
//{
//    goToLoginState();

//    EXPECT_CALL(userRegisterMock, registerUser());

//    QSignalSpy buttonSpy(m_sut->getUi()->registerNewUser, SIGNAL(clicked(bool)));
//    QTest::mouseClick(m_sut->getUi()->registerNewUser, Qt::LeftButton);

//    emit webSocketMock->opened();
//    EXPECT_EQ(1, buttonSpy.count());
//}

////#include "LoginDialogTestSuite.moc"
