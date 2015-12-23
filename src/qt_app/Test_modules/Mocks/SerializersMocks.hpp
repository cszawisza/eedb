#pragma once

#include <gmock/gmock.h>
#include "DataStructures/IRequestsSerializer.hpp"

#include "DataStructures/IRequestsDeserializer.hpp"
#include "DataStructures/IResponseDeserializer.hpp"

class IRequestSerializerMock : public IRequestsSerializer{
public:
    MOCK_CONST_METHOD1_T(serializeToByteArray, QByteArray (IClientRequest *req));
};

class IRequestDeserializerMock : public IRequestsDeserializer{
public:
    MOCK_CONST_METHOD1_T(parseFromByteArray, std::shared_ptr<IClientRequest> (const QByteArray &));
};

class IResponseDeserializerMock : public IResponsesDeserializer{
public:
    MOCK_CONST_METHOD1_T(parseFromByteArray, std::shared_ptr<IServerResponse> (const QByteArray &));
};
