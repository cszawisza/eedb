#include "gtest/gtest.h"
#include "DataStructures/Validators/NickNameValidator.hpp"

using namespace testing;

class NickNameValidatorTest : public testing::Test{

protected:
    NickNameValidator sut;
};

TEST_F( NickNameValidatorTest, toLongName ){
    EXPECT_FALSE(sut.isValid("asdfghjkloasdfghjklasdfghjklasdfghjklasdfghjklasdfghjklasdfghjklasdfghjklasdfghjklasdfghjklasdfghjklx"));
    EXPECT_TRUE (sut.isValid("sdjhfsdfhjklx"));
    sut.setMaxNickNameLength(5);
    EXPECT_FALSE(sut.isValid(("asdfgh") ));
    EXPECT_FALSE(sut.isValid(("asdfh") ));
}

TEST_F( NickNameValidatorTest, toShortName ){
    EXPECT_FALSE(sut.isValid(("a")));
    sut.setMinNickNameLength(5);
    EXPECT_FALSE(sut.isValid("aaaa"));
}

TEST_F( NickNameValidatorTest, validNames ){
    EXPECT_TRUE(sut.isValid("A_NAME"));
    EXPECT_TRUE(sut.isValid("aaa"));
    EXPECT_TRUE(sut.isValid("a123_"));
}

TEST_F( NickNameValidatorTest, invalidCharacters ){
    EXPECT_FALSE( sut.isValid("name_with_invalid_@_char"));
    EXPECT_FALSE( sut.isValid("name_with_invalid_ _char"));
}
