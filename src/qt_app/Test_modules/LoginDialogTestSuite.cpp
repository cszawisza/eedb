#include <gtest/gtest.h>
#include <gmock/gmock.h>

//#include <CommunicationManagerMock.hpp>

using namespace testing;

struct LoginDialogTestSuite : public ::testing::Test
{

};

TEST_F(LoginDialogTestSuite, FailTest)
{
    EXPECT_FALSE(false);
}
