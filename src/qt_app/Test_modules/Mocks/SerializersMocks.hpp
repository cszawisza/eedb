#pragma once

#include <gmock/gmock.h>
#include "DataStructures/IResponseSerializer.hpp"
#include "DataStructures/IRequestSerializer.hpp"


class IRequestSerializerMock : public IRequestsSerializer{
public:
    MOCK_CONST_METHOD1_T(serializeToByteArray, QByteArray (IClientRequest *));
    MOCK_CONST_METHOD2_T(serializeToByteArray, void (IClientRequest *, QByteArray&));

    MOCK_CONST_METHOD1_T(parseFromByteArray, IServerResponse* (const QByteArray &));
    MOCK_CONST_METHOD2_T(parseFromByteArray, void (const QByteArray &, IServerResponse*));
};

class IResponseSerializerMock : public IResponseSerializer{
public:
    MOCK_CONST_METHOD1_T(serializeToByteArray, QByteArray (IServerResponse *));
    MOCK_CONST_METHOD2_T(serializeToByteArray, void (IServerResponse *, QByteArray&));

    MOCK_CONST_METHOD1_T(parseFromByteArray, IClientRequest* (const QByteArray &));
    MOCK_CONST_METHOD2_T(parseFromByteArray, void (const QByteArray &, IClientRequest*));
};
