#include "gtest/gtest.h"

#include "utils/unixPerms.hpp"

TEST( UnixPerms, noPerms ){
    EXPECT_EQ( 0, UnixPermissions(0).toInteger() );
}

TEST( UnixPerms, all ){
    EXPECT_EQ( 511, UnixPermissions(511).toInteger() );
}

TEST( UnixPerms, onlyOneOfEachGroup ){
    EXPECT_EQ( 421, UnixPermissions(421).toInteger() );
}

TEST( UnixPerms, onixToInt){
    /// twx rwx rwx
    EXPECT_EQ( 511, UnixPermissions({7,7,7}).toInteger() );
}

TEST( UnixPerms, unixToIntGroup ){
    /// r-- -wx r-x
    EXPECT_EQ( 285, UnixPermissions({4,3,5}).toInteger() );
}

TEST( UnixPerms, stringToInt ){
    EXPECT_EQ( 327, UnixPermissions("r-x---rwx"   ).toInteger() );
    EXPECT_EQ( 327, UnixPermissions("r-x --- rwx" ).toInteger() );
    EXPECT_EQ( 327, UnixPermissions("dr-x --- rwx").toInteger() );
    EXPECT_EQ( 327, UnixPermissions("-r-x---rwx"  ).toInteger() );
    EXPECT_EQ( 327, UnixPermissions("dr-x---rwx"  ).toInteger() );
}
