#pragma once

#include <gmock/gmock.h>

#include "DataStructures/Interfaces/UserRequests.hpp"
#include "DataStructures/Interfaces/AclData.hpp"

//   ([\d\D]* )set_([\D]*)\(([\D]*)\); |    MOCK_METHOD1_T(set_\2, \1(\3 \2));
//   ([:a-zA-Z]*) \*([:a-zA-Z]*)\(\)\; |    MOCK_METHOD0_T(\2, \1*());

class UserAddMock : public requests::user::IAdd {
public:
    MOCK_CONST_METHOD0_T(get_id, UID());
    MOCK_METHOD1_T(set_id, void (UID uid));
    MOCK_CONST_METHOD0(has_id, bool());
    MOCK_METHOD0_T(clear_id, void());

    MOCK_METHOD0_T(nickname, String*());
    MOCK_CONST_METHOD0_T(get_nickname, const String &());
    MOCK_METHOD1_T(set_nickname, void (String nickname));
    MOCK_CONST_METHOD0_T(has_nickname, bool());
    MOCK_METHOD0_T(clear_nickname, void());

    MOCK_METHOD0_T(email, String*());
    MOCK_CONST_METHOD0_T(get_email, const String &());
    MOCK_METHOD1_T(set_email, void (String email));
    MOCK_CONST_METHOD0_T(has_email, bool());
    MOCK_METHOD0_T(clear_email, void());

    MOCK_METHOD0_T(password, String*());
    MOCK_CONST_METHOD0_T(get_password, const String &());
    MOCK_METHOD1_T(set_password, void (String password));
    MOCK_CONST_METHOD0_T(has_password, bool());
    MOCK_METHOD0_T(clear_password, void());

    MOCK_METHOD0_T(description, String*());
    MOCK_CONST_METHOD0_T(get_description, const String &());
    MOCK_METHOD1_T(set_description, void (String description));
    MOCK_CONST_METHOD0_T(has_description, bool());
    MOCK_METHOD0_T(clear_description, void());

    MOCK_METHOD0_T(avatar, Bytes*());
    MOCK_CONST_METHOD0_T(get_avatar, const Bytes &());
    MOCK_METHOD1_T(set_avatar, void (Bytes avatar));
    MOCK_CONST_METHOD0(has_avatar, bool());
    MOCK_METHOD0_T(clear_avatar, void());

    MOCK_METHOD0_T(acl, IAcl*());
    MOCK_CONST_METHOD0_T(get_acl, const IAcl& () );
    MOCK_METHOD1_T(assign_acl, void(IAcl*));
    MOCK_CONST_METHOD0_T(has_acl, bool());
    MOCK_METHOD0_T(clear_acl, void());

    MOCK_METHOD0_T(address, String*());
    MOCK_CONST_METHOD0_T(get_address, const String &());
    MOCK_METHOD1_T(set_address, void (String address));
    MOCK_CONST_METHOD0_T(has_address, bool());
    MOCK_METHOD0_T(clear_address, void());

    MOCK_METHOD0_T(phoneNumber, String*());
    MOCK_CONST_METHOD0_T(get_phoneNumber, const String &());
    MOCK_METHOD1_T(set_phoneNumber, void (String phoneNumber));
    MOCK_CONST_METHOD0_T(has_phoneNumber, bool());
    MOCK_METHOD0_T(clear_phoneNumber, void());
};
