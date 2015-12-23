#include "gtest/gtest.h"
#include "DataStructures/Validators/EmailValidator.hpp"

using namespace testing;

class EmailDataValidationTest : public testing::Test{

protected:
    EmailValidator sut;
};

TEST_F( EmailDataValidationTest, failingEmails){
    EXPECT_FALSE( sut.isValid( "test" ) );
    EXPECT_FALSE( sut.isValid( "@"));
    EXPECT_FALSE( sut.isValid( "@io"));
    EXPECT_FALSE( sut.isValid( "@io.io"));
    EXPECT_FALSE( sut.isValid( ".@io.io"));
    EXPECT_FALSE( sut.isValid( "test@.io.io"));
    EXPECT_FALSE( sut.isValid( "test.@io.io"));
    EXPECT_FALSE( sut.isValid( "test.io-net.com"));
    EXPECT_FALSE( sut.isValid( "test@-io.oi"));
    EXPECT_FALSE( sut.isValid( "test@io..com"));
}

TEST_F( EmailDataValidationTest, passingEmails ){
    EXPECT_TRUE( sut.isValid("test@io.oi" ));
    EXPECT_TRUE( sut.isValid("test@123.com"));
}
