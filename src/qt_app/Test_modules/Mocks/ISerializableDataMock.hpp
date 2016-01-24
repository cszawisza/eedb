#pragma once

#include <gmock/gmock.h>
#include <DataStructures/StructuresCommon.hpp>

class SerializableDataMock : public ISerializableData{
public:
  MOCK_METHOD1_T(parse, void (const QByteArray &data));
  MOCK_CONST_METHOD0_T(serialize, QByteArray ());
};


