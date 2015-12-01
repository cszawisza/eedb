#include "gtest/gtest.h"
#include "DataStructures/Validators/EmailValidator.hpp"

using namespace data;
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

//TEST_F( EmailDataValidationTest, rareInvelidCases ){
//    // address is to long
//    EXPECT_FALSE( sut.isValid( "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghiklm@abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghikl.abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghikl.abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghij"));
//    EXPECT_FALSE( sut.isValid( "a@abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghikl.abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghikl.abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghikl.abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefg.hij"));
//    // domain to long
//    EXPECT_FALSE( sut.isValid( "a@abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghikl.abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghikl.abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghikl.abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefg.hijk"));
//}

TEST_F( EmailDataValidationTest, passingEmails ){
    EXPECT_TRUE( sut.isValid("test@io.oi" ));
    EXPECT_TRUE( sut.isValid("test@123.com"));
}
