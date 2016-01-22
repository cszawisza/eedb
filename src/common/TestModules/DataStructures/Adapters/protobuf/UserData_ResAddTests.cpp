#include <gmock/gmock.h>

#include <DataStructures/Adapters/Protobuf/UserResponseAdapter.hpp>
#include <DataStructures/Adapters/Protobuf/UserRequestAdapter.hpp>

#include <DataStructures/Adapters/Protobuf/ClientRequestAdapter.hpp>
#include <DataStructures/Adapters/Protobuf/ServerResponseAdapter.hpp>

class UserDataAddResTests : public testing::Test{
public:
    UserDataAddResTests():
        sut(sr.user()->add())
    {}
protected:
    ServerResponse sr;
    ServerResponse res;
    responses::user::IAdd *sut;

    void reset(){
        sut = sr.user()->add();
    }

    void roundtrip(){
        res.parse( sr.serialize() );
        sut = res.user()->add();
    }
};

TEST_F(UserDataAddResTests, setSucces ){
    sut->set_successful();
    roundtrip();

    EXPECT_TRUE ( sut->is_successful() );
    EXPECT_FALSE( sut->is_not_successful() );
    reset();

    sut->set_successful(false);
    roundtrip();
    EXPECT_FALSE( sut->is_successful() );
    EXPECT_TRUE ( sut->is_not_successful() );
}

TEST_F(UserDataAddResTests, setNoErrorIsASuccess ){
    sut->set_successful( false );
    sut->set_error( responses::user::IAdd::Error_noError );
    roundtrip();
    EXPECT_TRUE( sut->is_successful() );
}

TEST_F(UserDataAddResTests, setError ){
    sut->set_successful(false);
    sut->set_error( responses::user::IAdd::Error_noError );
    roundtrip();
    EXPECT_TRUE( sut->is_successful() );
}

