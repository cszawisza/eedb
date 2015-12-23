#include "../../StructuresCommon.hpp"

namespace pb{
class Credentials;
}

class ProtobufAuthorizationDataAdapter : public IAuthorizationData{

    // IAuthorizationData interface
public:
    ProtobufAuthorizationDataAdapter();
    ProtobufAuthorizationDataAdapter(pb::Credentials *cred);
    ~ProtobufAuthorizationDataAdapter();
    void set_authorization(boost::variant<String, UID> auth);

    bool is_authorized_by_email() const;
    bool is_authorized_by_nickname() const;
    bool is_authorized_by_id() const;

    const String &get_email() const;
    const String &get_nickname() const;
    UID get_uid() const;

    void Clear() const;
    pb::Credentials *detachData();
private:
    pb::Credentials *m_data;
    bool m_takeOvnership = false;
};
