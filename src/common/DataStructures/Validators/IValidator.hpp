#pragma once

template<typename T>
class IFieldValidator{
public:
    virtual bool isValid( const T &data ) const = 0;
};

template<typename T>
class IMessageValidator : public IFieldValidator<T> {
public:
    virtual bool hasRequiredFields(const T &data) const =0;
};
