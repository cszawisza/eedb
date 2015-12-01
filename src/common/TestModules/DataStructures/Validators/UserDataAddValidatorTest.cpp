#include "../Mocks/UserAddMock.hpp"
#include "../Mocks/EmailValidatorMock.hpp"

#include "DataStructures/Validators/UserDataValidator.hpp"

#include <memory>

using namespace data;
using data::requests::user::IAdd;
using namespace testing;

class UserAddDataValidationsTests : public testing::Test{

protected:
    UserAddMock dataMock;
    UserAddValidator sut;
};

TEST_F( UserAddDataValidationsTests, requiredFieldsFail){
    EXPECT_CALL(dataMock, has_email()).WillOnce(Return(false));

    EXPECT_FALSE(sut.hasRequiredFields(dataMock));
}

TEST_F( UserAddDataValidationsTests, allRequiredAvalible ){
    EXPECT_CALL(dataMock, has_email()).WillOnce(Return(true));
    EXPECT_CALL(dataMock, has_nickname()).WillOnce(Return(true));
    EXPECT_CALL(dataMock, has_password()).WillOnce(Return(true));

    EXPECT_TRUE(sut.hasRequiredFields(dataMock));
}

TEST_F( UserAddDataValidationsTests, invalidEmailFails ){
    auto validator = std::make_shared<EmailValidatorMock>();
    sut.setEmailValidator( validator );

    EXPECT_CALL( dataMock, get_email());
    EXPECT_CALL(*validator, isValid( _ )).WillOnce(Return(true));

    sut.isValid( dataMock );
}
