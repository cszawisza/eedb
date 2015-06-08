#include "gtest/gtest.h"
#include "utils/userconfig.h"
#include "messages/pb_cpp/user.pb.h"

#include <QJsonDocument>
#include <QJsonObject>

using namespace eedb::utils;

TEST( UserConfig, ctor ){
    UserConfig uc("");

    EXPECT_EQ(uc.toStdString(), "{}");
    EXPECT_EQ(uc.toString(), "{}");
}

TEST( UserConfig, simple_conf ){
    UserConfig uc("{ \n\
                    \t \"last_group_id\":10 \n\
                   }");
    EXPECT_EQ(uc.toStdString(), "{\"last_group_id\":10}");
    EXPECT_EQ(uc.toString(), "{\"last_group_id\":10}");
}

TEST( UserConfig, createByMessage ){
    user::UserConfig conf;

    conf.set_last_group_id( 10 );
//    conf.set_last_item_id( 11 );
//    conf.set_last_parameter_id( 12 );
//    conf.set_last_storage_id( 13 );

    UserConfig uc( conf );

//    EXPECT_EQ(uc.toString(), "{\"last_group_id\":10}");
}
