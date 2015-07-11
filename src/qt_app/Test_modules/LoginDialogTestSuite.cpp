#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <LoginDialog.hpp>
#include <CommunicationManagerMock.hpp>


using namespace testing;


#include <QtTest/QtTest>
#include <QtGui>


class TestGui: public QObject
{
    Q_OBJECT

private slots:
    void testGui();

};

void TestGui::testGui()
{
    LoginDialog l_Dialog{};
//    l_Dialog.show();

    //QTest::keyClicks(l_Dialog.getUi(), "hello world");
    QTest::mouseClick(&l_Dialog.getUi()->login, Qt::LeftButton);

    EXPECT_FALSE(false);
}

struct LoginDialogTestSuite : public ::testing::Test
{
//    CommunicationManagerMock communicationManagerMock{};
    LoginDialog l_Dialog{};
};

TEST_F(LoginDialogTestSuite, FailTest)
{
    //l_Dialog.exec();
    //EXPECT_CALL(communicationManagerMock, handle());
    EXPECT_FALSE(false);
}

#include "LoginDialogTestSuite.moc"
