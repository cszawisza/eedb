#pragma once

#include <gmock/gmock.h>
#include "DataStructures/Validators/NickNameValidator.hpp"

class NickNameValidatorMock : public NickNameValidator {
public:
    MOCK_CONST_METHOD1_T(isValid, bool (const String &name));
};
