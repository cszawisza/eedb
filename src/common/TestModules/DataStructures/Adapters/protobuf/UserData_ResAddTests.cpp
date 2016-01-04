#include <gmock/gmock.h>

#include <DataStructures/Adapters/Protobuf/UserResponseAdapter.hpp>
#include <DataStructures/Adapters/Protobuf/UserRequestAdapter.hpp>

#include <DataStructures/Adapters/Protobuf/ClientRequestAdapter.hpp>
#include <DataStructures/Adapters/Protobuf/ServerResponseAdapter.hpp>

//class UserDataAddResTests : public testing::Test{
//protected:
//    responses::user::Add sut;

//    responses::user::Add roundtrip(){
//        ServerResponse sr;

//        sr.user()->assign(&sut);

//        auto serializedResponse = sr.serialize();

////        return parser.parseServerResponse(serializer.serializeServerResponse(&sr));
//        return sut;
//    }
//};

//TEST_F(UserDataAddResTests, setSucces ){
//    using namespace responses::user;
//    sut.set_successful();
//    EXPECT_TRUE( sut.is_successful() );
//    EXPECT_FALSE(sut.is_not_successful());

//    sut.set_successful(false);
//    EXPECT_FALSE(sut.is_successful() );
//    EXPECT_TRUE(sut.is_not_successful());
//}

//TEST_F(UserDataAddResTests, setNoErrorIsASuccess ){
//    using namespace responses::user;
//    sut.set_successful(false);
//    sut.set_error( Add::Error_noError );

//    EXPECT_TRUE( sut.is_successful() );
//}

////TEST_F(UserDataAddResTests, setError ){
////    using namespace responses::user;
////    sut.set_successful(false);
////    sut.set_error( Add::Error_noError );

////    EXPECT_TRUE( roundtrip().is_successful() );
////}

