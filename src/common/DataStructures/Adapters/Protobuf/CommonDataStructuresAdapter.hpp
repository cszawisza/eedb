#include "../../StructuresCommon.hpp"

namespace protobuf{
class Credentials;
}

class ProtobufAuthorizationDataAdapter : public IAuthorizationData{

    // IAuthorizationData interface
public:
    ProtobufAuthorizationDataAdapter();
    ProtobufAuthorizationDataAdapter(protobuf::Credentials *cred);
    ~ProtobufAuthorizationDataAdapter();
    void set_authorization(boost::variant<String, UID> auth);

    bool is_authorized_by_email() const;
    bool is_authorized_by_nickname() const;
    bool is_authorized_by_id() const;

    const String &get_email() const;
    const String &get_nickname() const;
    UID get_uid() const;

    void Clear() const;
    protobuf::Credentials *detachData();
private:
    protobuf::Credentials *m_data;
    bool m_takeOvnership = false;
};
