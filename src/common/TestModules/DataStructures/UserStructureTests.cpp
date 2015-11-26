#include <gtest/gtest.h>

#include "Validators/UserDataValidators.hpp"

using namespace data;
using namespace data::requests;

TEST(UserTestCase,AddValidData){
    user::Add m_sut;
    EXPECT_FALSE( isValid(m_sut) );

    m_sut.email = Email("simple@email.com");
    m_sut.password = String("a password");
    m_sut.name = Name("name");

    EXPECT_TRUE( isValid(m_sut) );
}

TEST(UserTestCase, LoginValidData){
    user::Login m_sut;
    EXPECT_FALSE( isValid(m_sut));

    m_sut.cred.data = Email("asdf@asdf.as");
    m_sut.password = String("none");
    EXPECT_TRUE( isValid(m_sut));
}
