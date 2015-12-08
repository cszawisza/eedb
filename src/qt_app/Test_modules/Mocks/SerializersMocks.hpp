#pragma once

#include <gmock/gmock.h>
#include "DataStructures/IRequestsSerializer.hpp"

#include "DataStructures/IRequestsDeserializer.hpp"
#include "DataStructures/IResponseDeserializer.hpp"

class IRequestSerializerMock : public data::IRequestsSerializer{
public:
    MOCK_CONST_METHOD1_T(serializeToByteArray, QByteArray (data::IClientRequest *req));
};

class IRequestDeserializerMock : public data::IRequestsDeserializer{
public:
    MOCK_CONST_METHOD1_T(parseFromByteArray, std::shared_ptr<data::IClientRequest> (const QByteArray &));
};

class IResponseDeserializerMock : public data::IResponsesDeserializer{
public:
    MOCK_CONST_METHOD1_T(parseFromByteArray, std::shared_ptr<data::IServerResponse> (const QByteArray &));
};
