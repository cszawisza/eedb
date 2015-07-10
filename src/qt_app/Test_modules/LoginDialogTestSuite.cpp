#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <LoginDialog.hpp>
#include <CommunicationManagerMock.hpp>

using namespace testing;

struct LoginDialogTestSuite : public ::testing::Test
{
    LoginDialog l_Dialog{};
    CommunicationManagerMock communicationManagerMock{};
};

TEST_F(LoginDialogTestSuite, FailTest)
{
    l_Dialog.exec();
    EXPECT_CALL(communicationManagerMock, handle());
    EXPECT_FALSE(false);
}
