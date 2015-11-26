#pragma once

#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <boost/none.hpp>

#include <string>
#include <type_traits>

#include <QString>

namespace data{
class WireData{
public:
    virtual void Clear(){
    }
};

template<typename T>
bool isValid( const T &){ return false; }

template<typename Base, typename Derived>
class Adapter;

class Acl : public WireData {

};

using String = std::string;

struct Email{
    Email(){}
    Email( const char * c ){
        data = String(c);
    }
    Email( const String &s){
        data = s;
    }
    Email( const QString &qs ){
        data = qs.toStdString();
    }

    bool isValid() const {
        return true;
    }

    bool isNotValid() const {
        return !isValid();
    }
private:
    String data;
};

struct Name : public String{
    Name(){}
    explicit Name(const String &s){
        this->assign(s);
    }
};

using OptAcl = boost::optional<Acl>;
using OptName = boost::optional<Name>;
using OptEmail = boost::optional<Email>;
using OptString = boost::optional<std::string>;
using OptInt64 = boost::optional<int64_t>;
using Int64 = int64_t;

using OptUInt64 = boost::optional<uint64_t>;
using UInt64 = uint64_t;


using UID = uint64_t;
using OptUID = boost::optional<UID>;

using Bytes = std::vector<uint8_t>;
using OptBytes = boost::optional<Bytes>;
}
