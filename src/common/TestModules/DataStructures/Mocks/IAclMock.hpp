#pragma once

#include <gmock/gmock.h>

#include "DataStructures/Interfaces/AclData.hpp"

class IAclMock : public IAcl {
public:
    MOCK_CONST_METHOD0_T(get_id, UID ());
    MOCK_METHOD1_T(set_id, void(UID));
    MOCK_CONST_METHOD0_T(has_id, bool());
    MOCK_METHOD0_T(clear_id,void());

    MOCK_CONST_METHOD0_T(get_owner, UID ());
    MOCK_METHOD1_T(set_owner, void(UID));
    MOCK_CONST_METHOD0_T(has_owner, bool());
    MOCK_METHOD0_T(clear_owner,void());

    MOCK_CONST_METHOD0_T(get_groups, UID ());
    MOCK_METHOD1_T(set_groups, void(UID));
    MOCK_CONST_METHOD0_T(has_groups, bool());
    MOCK_METHOD0_T(clear_groups,void());

    MOCK_CONST_METHOD0_T(get_unixperms, UnixPermissions ());
    MOCK_METHOD1_T(set_unixperms, void(UnixPermissions));
    MOCK_CONST_METHOD0_T(has_unixperms, bool());
    MOCK_METHOD0_T(clear_unixperms,void());

    MOCK_CONST_METHOD0_T(get_status, Status ());
    MOCK_METHOD1_T(set_status, void(Status));
    MOCK_CONST_METHOD0_T(has_status, bool());
    MOCK_METHOD0_T(clear_status,void());
};
