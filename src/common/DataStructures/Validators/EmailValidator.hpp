#pragma once
#include "IValidator.hpp"
#include "../StructuresCommon.hpp"

namespace data{
class EmailValidator : public IFieldValidator<data::String> {
    // IValidator interface
public:
    virtual bool isValid( const data::String &data ) const override;

    template<typename T>
    bool isValid(const T &data) const{ return isValid(data.get_email()); }

    bool isValid( const QString &email ) const { return isValid( email.toStdString() ); }
    bool isValid( const char* email ) const { return isValid( data::String( email ) ); }
private:
//    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) const {
//        std::stringstream ss(s);
//        std::string item;
//        while (std::getline(ss, item, delim)) {
//            elems.push_back(item);
//        }
//        return elems;
//    }

//    std::vector<std::string> split(const std::string &s, char delim) const {
//        std::vector<std::string> elems;
//        split(s, delim, elems);
//        return elems;
//    }
};
}
