#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <LoginDialog.hpp>
#include <CommunicationManagerMock.hpp>

using namespace testing;

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
