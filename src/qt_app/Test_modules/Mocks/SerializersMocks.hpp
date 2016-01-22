#pragma once

#include <gmock/gmock.h>


#include "Interfaces/ClientRequest.hpp"
#include "Interfaces/ServerResponse.hpp"


class IRequestSerializerMock : public IClientRequest{
public:
    MOCK_CONST_METHOD1_T(serializeClientRequest, QByteArray (IClientRequest *));
    MOCK_CONST_METHOD2_T(serializeClientRequest, void (IClientRequest *, QByteArray&));

    MOCK_CONST_METHOD1_T(parseServerResponse, IServerResponse* (const QByteArray &));
    MOCK_CONST_METHOD2_T(parseServerResponse, void (const QByteArray &, IServerResponse*));
};

class IResponseSerializerMock : public IServerResponse{
public:
    MOCK_CONST_METHOD1_T(serializeServerResponse, QByteArray (IServerResponse *));
    MOCK_CONST_METHOD2_T(serializeServerResponse, void (IServerResponse *, QByteArray&));

    MOCK_CONST_METHOD1_T(parseClientRequest, IClientRequest* (const QByteArray &));
    MOCK_CONST_METHOD2_T(parseClientRequest, void (const QByteArray &, IClientRequest*));
};
