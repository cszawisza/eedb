#pragma once

#include <gmock/gmock.h>

#include "DataStructures/Interfaces/UserRequests.hpp"

class UserAddMock : public requests::user::IGet {
public:
    MOCK_CONST_METHOD0_T(has_requestedUid, bool ());
    MOCK_METHOD1_T(request_uid, void (bool));

    MOCK_CONST_METHOD0_T(has_requestedAddress, bool ());
    MOCK_METHOD1_T(request_Address, void (bool));

    MOCK_CONST_METHOD0_T(has_requestedPhoneNumber, bool ());
    MOCK_METHOD1_T(request_PhoneNumber, void (bool));

    MOCK_CONST_METHOD0_T(has_requestedDescription, bool ());
    MOCK_METHOD1_T(request_Description, void (bool));

    MOCK_CONST_METHOD0_T(has_requestedAvatar, bool ());
    MOCK_METHOD1_T(request_Avatar, void (bool));

    MOCK_CONST_METHOD0_T(has_requestedAcl, bool ());
    MOCK_METHOD1_T(request_Acl, void (bool));

    MOCK_METHOD1_T(set_requestCriterion, void (ICriterion));
    MOCK_CONST_METHOD0_T(get_criteria, const ICriterion());
};
