#pragma once

#include "../../utils/Optional.hpp"
#include "../StructuresCommon.hpp"

enum MessageType{
    User,
    Category,
    Inventory
};

static constexpr auto userType = CategoryTypeId(0, "client::requests::user");
static constexpr auto categoryType = CategoryTypeId(1, "client::requests::category" );

//enum CategoryActions{
//    Add,
//    Get,
//    Modify,
//    Delete
//};
