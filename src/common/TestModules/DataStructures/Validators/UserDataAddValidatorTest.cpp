#include "../Mocks/UserAddMock.hpp"
#include "DataStructures/Validators/UserDataValidators.hpp"

#include <memory>

using namespace data;
using data::requests::user::IAdd;
using namespace testing;

class UserAddDataValidationsTests : public testing::Test{

protected:
    UserAddMock sut;
};

TEST_F( UserAddDataValidationsTests, requiredFieldsFail){
    EXPECT_CALL(sut, has_email()).WillOnce(Return(false));

    EXPECT_FALSE(hasRequiredFields<IAdd>(sut));
}

TEST_F( UserAddDataValidationsTests, allRequiredAvalible ){
    EXPECT_CALL(sut, has_email()).WillOnce(Return(true));
    EXPECT_CALL(sut, has_nickname()).WillOnce(Return(true));
    EXPECT_CALL(sut, has_password()).WillOnce(Return(true));

    EXPECT_TRUE(hasRequiredFields<IAdd>(sut) );
}

TEST_F( UserAddDataValidationsTests, invalidEmailFails ){
    EXPECT_CALL(sut, get_email())
            .WillOnce(ReturnRefOfCopy(String("invalid email")))
            .WillOnce(ReturnRefOfCopy(String("valid@email.com")));


    EXPECT_FALSE(isValid<IAdd>(sut));
    EXPECT_TRUE(isValid<IAdd>(sut));
}
