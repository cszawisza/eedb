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
SCA ActionRemove        = ActionId(6, "user::remove");

}

namespace category{

SCA ActionAdd           = ActionId(0, "category::add");
SCA ActionGet           = ActionId(2, "category::get");
SCA ActionModify        = ActionId(5, "category::modify");
SCA ActionRemove        = ActionId(10,"category::remove");

}

namespace item{

}

}
