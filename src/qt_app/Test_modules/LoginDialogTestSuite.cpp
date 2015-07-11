#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <LoginDialog.hpp>
#include <ui_LoginDialog.h> // to get loginDialog UI definition
#include <QTest>

#include <CommunicationManagerMock.hpp>


using namespace testing;


#include <QtTest/QtTest>
#include <QtGui>


class TestGui: public QObject
{
    Q_OBJECT

};



struct LoginDialogTestSuite : public ::testing::Test
{
//    CommunicationManagerMock communicationManagerMock{};
    LoginDialog l_Dialog{};
};

TEST_F(LoginDialogTestSuite, FailTest)
{
    LoginDialog l_Dialog{};

    // spy on this signal
    QSignalSpy buttonSpy(l_Dialog.getUi()->login, SIGNAL(clicked(bool)));
    QSignalSpy dialogSpy(&l_Dialog, SIGNAL(loginOk()));

    // add some funny text
    QTest::keyClicks(l_Dialog.getUi()->userLogin, "hello world");
    // emulate a user click
    QTest::mouseClick(l_Dialog.getUi()->login, Qt::LeftButton);

    EXPECT_EQ(1, buttonSpy.count() );
    EXPECT_EQ(0, dialogSpy.count() );
}

#include "LoginDialogTestSuite.moc"
