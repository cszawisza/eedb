#include <gmock/gmock.h>
#include "DataStructures/Validators/EmailValidator.hpp"

class EmailValidatorMock : public data::EmailValidator {
public:
    MOCK_CONST_METHOD1_T(isValid, bool (const data::String &email));
};
