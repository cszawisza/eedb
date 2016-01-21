#include "gtest/gtest.h"
#include "TestCommon.hpp"

#include "database/idatabase.h"

///TODO do not use protobuf structures in tests
#include "DataStructures/Adapters/Protobuf/ClientRequestAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/ServerResponseAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/UserRequestAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/UserResponseAdapter.hpp"

#include "core/ProcessingUnits/UserPU.hpp"
#include <boost/algorithm/string.hpp>

using namespace test;

class userCreateTest : public ::testing::Test
{
public:
    userCreateTest():
        add( req.user()->add() )
    {
        db.start_transaction();
    }

    ~userCreateTest(){
        db.rollback_transaction(false);
    }

    responses::user::IAdd::AddErrors sendRequest( ){
        handler.setOutputData(std::make_shared<ServerResponse>());
        handler.process(db, &req);
        return handler.response()->user()->add()->get_error_code();
    }

    DB db;
    eedb::pu::UserPU handler;
    ClientRequest req;
    requests::user::IAdd *add;
};

TEST_F( userCreateTest, userNoNameAndEmail){
    add->set_password("passwd");

    auto res = sendRequest();
    EXPECT_EQ( responses::user::IAdd::Error_MissingRequiredFields, res );
}

TEST_F( userCreateTest, user_no_email){
    add->set_password("passwd");
    add->set_nickname("Test_user_asdf");

    auto res = sendRequest();
    EXPECT_EQ(responses::user::IAdd::Error_MissingRequiredFields, res);
}

TEST_F( userCreateTest, create_withBasicData ){
    add->set_password("passwd");
    add->set_nickname("Test_user_asdf");
    add->set_email("testuser@user.uu");
    auto res = sendRequest();
    EXPECT_EQ(responses::user::IAdd::Error_noError, res);
}

TEST_F( userCreateTest, user_name_to_long ){
    add->set_password("passwd");
    add->set_nickname( random_string(73) );
    add->set_email( random_string(10) + "@user.uu");
    auto res = sendRequest();
    EXPECT_EQ(responses::user::IAdd::Error_BadName, res);
}

TEST_F( userCreateTest, user_duplicated ){
    string name = "RANDOM_USER_NAME";
    string email= "random_user_name@email.com";

    add->set_password("passwd");
    add->set_nickname( name );
    add->set_email( email );
    auto res = sendRequest();
    EXPECT_EQ(responses::user::IAdd::Error_noError, res);

    add->set_nickname("different_name");
    res = sendRequest();
    EXPECT_EQ(responses::user::IAdd::Error_UserExists, res); // different name but the same email

    add->set_nickname( name );
    add->set_email( "blahhhh@asdfg.sa");
    res = sendRequest();
    EXPECT_EQ(responses::user::IAdd::Error_UserExists, res); // different email but the same name
}

TEST_F( userCreateTest, full_data ){
    add->set_password("passwd");
    add->set_nickname( random_string(10) );
    add->set_email( boost::algorithm::to_lower_copy(random_string(10)) + "@user.uu");
    add->set_address( random_string(100) );
    add->set_phoneNumber( random_string(10) );
    add->set_description( random_string(1000) );
    add->set_avatar( random_string(1000) );

    auto res = sendRequest();

    EXPECT_EQ(responses::user::IAdd::Error_noError, res);
}
