#include "gtest/gtest.h"
#include "DataStructures/Validators/NickNameValidator.hpp"

using namespace data;
using namespace testing;

class NickNameValidatorTest : public testing::Test{

protected:
    NickNameValidator sut;
};

TEST_F( NickNameValidatorTest, toLongName ){
    EXPECT_FALSE(sut.isValid(("asdfghjkloasdfghjklasdfghjklasdfghjklasdfghjklasdfghjklasdfghjklasdfghjklasdfghjklasdfghjklasdfghjklx")));
    sut.setMaxNickNameLength(5);
    EXPECT_FALSE(sut.isValid(("asdfgh") ));
}

TEST_F( NickNameValidatorTest, toShortName ){
    EXPECT_FALSE(sut.isValid(("a")));
    sut.setMinNickNameLength(5);
    EXPECT_FALSE(sut.isValid("aaaa"));
}

TEST_F( NickNameValidatorTest, validNames ){
    EXPECT_TRUE(sut.isValid("A_NAME"));
    EXPECT_TRUE(sut.isValid("aa"));
    EXPECT_TRUE(sut.isValid("a123_"));
}

TEST_F( NickNameValidatorTest, invalidCharacters ){
    EXPECT_FALSE( sut.isValid("name_with_invalid_@_char"));
}
