#pragma once

#include "../../utils/NamedIdnetyfier.hpp"

#define SCA static constexpr auto

namespace actions{

SCA typeUser            = ActionTypeId(0, "user");
SCA typeCategory        = ActionTypeId(1, "category");

namespace user{

SCA ActionAdd           = ActionId(0, "user::add");
SCA ActionLogin         = ActionId(1, "user::login");
SCA ActionGet           = ActionId(2, "user::get");
SCA ActionLogout        = ActionId(3, "user::logout");
SCA ActionChangePassword= ActionId(4, "user::change_password");
SCA ActionModify        = ActionId(5, "user::modify");

}

namespace category{

}

namespace item{

}

}
