#include <gmock/gmock.h>

#include <DataStructures/Adapters/Protobuf/ClientRequestAdapter.hpp>
#include <DataStructures/Adapters/Protobuf/UserRequestAdapter.hpp>

using namespace requests::user;

class UserDataGetTests : public testing::Test{
public:
    UserDataGetTests(): sut(new Get() ){}
    ~UserDataGetTests(){ delete sut;}
protected:
    Get *sut;

    void make_roundtrip(){
        ClientRequest client_req;
        client_req.user()->assign(sut);
        auto ba = client_req.serialize();

        ClientRequest parsed;
        parsed.parse(ba);

        sut = new Get( dynamic_cast<Get*>(parsed.user()->get())->detachData());
    }

    void all_false()
    {
        EXPECT_FALSE(sut->has_requestedAcl());
        EXPECT_FALSE(sut->has_requestedAddress());
        EXPECT_FALSE(sut->has_requestedAvatar());
        EXPECT_FALSE(sut->has_requestedDescription());
        EXPECT_FALSE(sut->has_requestedPhoneNumber());
        EXPECT_FALSE(sut->has_requestedUid());
    }

    void all_true(){
        make_roundtrip();
        EXPECT_TRUE(sut->has_requestedAcl());
        EXPECT_TRUE(sut->has_requestedAddress());
        EXPECT_TRUE(sut->has_requestedAvatar());
        EXPECT_TRUE(sut->has_requestedDescription());
        EXPECT_TRUE(sut->has_requestedPhoneNumber());
        EXPECT_TRUE(sut->has_requestedUid());
    }
};


TEST_F(UserDataGetTests, ctor){
    all_false();
}

TEST_F(UserDataGetTests, setFalseDontChangeData ){
    sut->request_acl(false);
    sut->request_address(false);
    sut->request_avatar(false);
    sut->request_description(false);
    sut->request_phoneNumber(false);
    sut->request_uid(false);

    all_false();
}

TEST_F(UserDataGetTests, setTrue ){
    sut->request_acl();
    sut->request_address();
    sut->request_avatar();
    sut->request_description();
    sut->request_phoneNumber();
    sut->request_uid();

    all_true();
}

TEST_F(UserDataGetTests, clearBySetFalse ){
    sut->request_acl();
    sut->request_address();
    sut->request_avatar();
    sut->request_description();
    sut->request_phoneNumber();
    sut->request_uid();
    all_true();

    sut->request_acl(false);
    sut->request_address(false);
    sut->request_avatar(false);
    sut->request_description(false);
    sut->request_phoneNumber(false);
    sut->request_uid(false);
    all_false();
}


TEST_F(UserDataGetTests, getCriteria ){
    sut->criteria()->require_data_own(true);

    make_roundtrip();
    EXPECT_TRUE(sut->get_criteria().has_requested_own_data());
}
