#include "gtest/gtest.h"
#include "utils/hash_passwd.h"

using namespace eedb::utils;

TEST(PasswordHash, set ){
    PasswordHash hash;

    hash.setPassword("my pass");
    hash.setSalt("SALT");

    EXPECT_EQ(hash.salt(), "SALT");
    EXPECT_EQ(hash.hash().length(), 128); // Hashed password
}

TEST(PasswordHash, calculate_hash){
    PasswordHash hash;
    hash.setPassword("my pass");

    EXPECT_EQ(hash.salt().size(), 128 ); // salt should be calculated if not existing
}

TEST(PasswordHash, check_passwd ){
    std::string password = "SECRET_PASSWORD";
    std::string hash, salt;
    {
        PasswordHash pass;
        pass.setPassword( password );

        hash = pass.hash();
        salt = pass.salt();
    }

    EXPECT_EQ(hash, PasswordHash::hashPassword(password, salt));
}
