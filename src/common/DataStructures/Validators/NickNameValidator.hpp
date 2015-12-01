#pragma once

#include "IValidator.hpp"
#include "../StructuresCommon.hpp"

class QString;

namespace data{
class NickNameValidator : public IFieldValidator<String> {
public:
    NickNameValidator();
    virtual bool isValid(const String &data) const;
    bool isValid( const char* data) const;

    size_t maxNickNameLength() const;
    void setMaxNickNameLength(const size_t &maxNickNameLength);

    size_t minNickNameLength() const;
    void setMinNickNameLength(const size_t &minNickNameLength);
private:
    size_t m_maxNickNameLength;
    size_t m_minNickNameLength;
};
}
