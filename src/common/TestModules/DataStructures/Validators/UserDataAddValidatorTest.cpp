#include "../Mocks/UserAddMock.hpp"
#include "../Mocks/NickNameValidatorMock.hpp"
#include "../Mocks/EmailValidatorMock.hpp"

#include "DataStructures/Validators/UserDataValidator.hpp"

#include <memory>

using requests::user::IAdd;
using namespace testing;

class UserAddDataValidationsTests : public testing::Test{
public:
    UserAddDataValidationsTests():
        m_emailValidator(std::make_shared<EmailValidatorMock>()),
        m_nickValidator(std::make_shared<NickNameValidatorMock>() )
    {
        sut.setEmailValidator(m_emailValidator);
        sut.setNickNameValidator(m_nickValidator);
    }
protected:
    UserAddMock dataMock;
    requests::UserAddValidator sut;
    std::shared_ptr<EmailValidatorMock> m_emailValidator;
    std::shared_ptr<NickNameValidatorMock> m_nickValidator;
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
    EXPECT_CALL( dataMock, get_email()).WillOnce(ReturnRefOfCopy(String()) );
    EXPECT_CALL( dataMock, get_nickname()).WillOnce(ReturnRefOfCopy(String()));

    EXPECT_CALL(*m_emailValidator, isValid( _ )).WillOnce(Return(true));
    EXPECT_CALL(*m_nickValidator, isValid( _ )).WillOnce(Return(true));

    EXPECT_TRUE(sut.isValid( dataMock ));
}
