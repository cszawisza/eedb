#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QByteArray>
#include <boost/optional.hpp>
#include "message_conteiner.pb.h"
#include "user.pb.h"
#include <ProtobufConverters.hpp>

using namespace testing;

struct ProtobufConvertersTestSuite : public ::testing::Test
{
    ProtobufConvertersTestSuite();
};

ProtobufConvertersTestSuite::ProtobufConvertersTestSuite()
{
//    m_clientRequests.mutable_request()->Add();
//    m_clientRequests.mutable_request(0)->mutable_userreq()->mutable_add()->mutable_basic()->set_id(11);
//    m_clientRequests.request(0).set_requestid(basicId);
//    m_clientRequests.mutable_request()->AddAllocated(&m_clientRequest);
//    m_clientRequests.request(0).set_requestid(basicId);
//    p_clientRequest.set_requestid(1);
}

//TEST_F(ProtobufConvertersTestSuite, EmptyClientRequest)
//{
//    const pb::ClientRequests & l_emptyClientRequests{};
//    QByteArray l_emptyArray{};
//    EXPECT_EQ(l_emptyArray, convertProtobufClientRequestsToQByteArray(l_emptyClientRequests));
//}

//TEST_F(ProtobufConvertersTestSuite, EmptyServerResponse)
//{
//    QByteArray l_emptyArray{};
//    boost::optional<pb::ServerResponses> l_emptyServerResponses = pb::ServerResponses();
//    std::string l_emptyServerResponsesString;
//    l_emptyServerResponses->SerializeToString(&l_emptyServerResponsesString);

//    std::string l_emptyConvertedServerResponseString;
//    auto l_convertedResponse = convertQByteArrayToProtobufServerResponse(l_emptyArray);
//    l_convertedResponse->SerializeToString(&l_emptyConvertedServerResponseString);

//    EXPECT_TRUE(l_convertedResponse.is_initialized());
//    EXPECT_EQ(l_emptyServerResponsesString, l_emptyConvertedServerResponseString);
//}

//TEST_F(ProtobufConvertersTestSuite, ServerResponseParseError)
//{
//    boost::optional<pb::ServerResponses> l_emptyServerResponses{};
//    QByteArray l_emptyArray("12213");
//    EXPECT_FALSE(convertQByteArrayToProtobufServerResponse(l_emptyArray).is_initialized());
//}

//#include "ProtobufConvertersTestSuite.moc"
