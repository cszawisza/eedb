#include <gmock/gmock.h>

#include "DataStructures/Interfaces/UserData.hpp"
#include "DataStructures/Interfaces/AclData.hpp"

//   ([\d\D]* )set_([\D]*)\(([\D]*)\); |    MOCK_METHOD1_T(set_\2, \1(\3 \2));
//   ([:a-zA-Z]*) \*([:a-zA-Z]*)\(\)\; |    MOCK_METHOD0_T(\2, \1*());

class UserAddMock : public data::requests::user::IAdd {
public:
    MOCK_CONST_METHOD0_T(get_id, data::UID());
    MOCK_METHOD1_T(set_id, void (data::UID uid));
    MOCK_CONST_METHOD0(has_id, bool());
    MOCK_METHOD0_T(clear_id, void());

    MOCK_METHOD0_T(nickname, data::String*());
    MOCK_CONST_METHOD0_T(get_nickname, data::String &());
    MOCK_METHOD1_T(set_nickname, void (data::String nickname));
    MOCK_CONST_METHOD0_T(has_nickname, bool());
    MOCK_METHOD0_T(clear_nickname, void());

    MOCK_METHOD0_T(email, data::String*());
    MOCK_CONST_METHOD0_T(get_email, data::String &());
    MOCK_METHOD1_T(set_email, void (data::String email));
    MOCK_CONST_METHOD0_T(has_email, bool());
    MOCK_METHOD0_T(clear_email, void());

    MOCK_METHOD0_T(password, data::String*());
    MOCK_CONST_METHOD0_T(get_password, data::String &());
    MOCK_METHOD1_T(set_password, void (data::String password));
    MOCK_CONST_METHOD0_T(has_password, bool());
    MOCK_METHOD0_T(clear_password, void());

    MOCK_METHOD0_T(description, data::String*());
    MOCK_CONST_METHOD0_T(get_description, data::String &());
    MOCK_METHOD1_T(set_description, void (data::String description));
    MOCK_CONST_METHOD0_T(has_description, bool());
    MOCK_METHOD0_T(clear_description, void());

    MOCK_METHOD0_T(avatar, data::Bytes*());
    MOCK_CONST_METHOD0_T(get_avatar, data::Bytes &());
    MOCK_METHOD1_T(set_avatar, void (data::Bytes avatar));
    MOCK_CONST_METHOD0(has_avatar, bool());
    MOCK_METHOD0_T(clear_avatar, void());

    MOCK_METHOD0_T(acl, std::shared_ptr<data::IAcl>());
    MOCK_METHOD1_T(assign_acl, void(std::shared_ptr<data::IAcl>));
    MOCK_CONST_METHOD0_T(has_acl, bool());
    MOCK_METHOD0_T(clear_acl, void());

    MOCK_METHOD0_T(address, data::String*());
    MOCK_CONST_METHOD0_T(get_address, data::String &());
    MOCK_METHOD1_T(set_address, void (data::String address));
    MOCK_CONST_METHOD0_T(has_address, bool());
    MOCK_METHOD0_T(clear_address, void());

    MOCK_METHOD0_T(phoneNumber, data::String*());
    MOCK_CONST_METHOD0_T(get_phoneNumber, data::String &());
    MOCK_METHOD1_T(set_phoneNumber, void (data::String phoneNumber));
    MOCK_CONST_METHOD0_T(has_phoneNumber, bool());
    MOCK_METHOD0_T(clear_phoneNumber, void());
};
