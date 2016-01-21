#pragma once

#include "../../Interfaces/CategoryResponses.hpp"

namespace protobuf{
    class StdError;
    class CategoryRes;

    class ServerResponse;
}

namespace responses{
namespace category{

class Add: public IAdd{
public:
    Add( protobuf::StdError *add);
    Add(const protobuf::StdError &add);
    ~Add();

    void set_code(AddErrors) override;
    AddErrors get_error_codes() const override;
private:
    protobuf::StdError *m_data;
    bool m_takeOvnership = false;
    bool m_isMutable;
};


class Get: public IGet {
    // IGet interface
public:
    Get(protobuf::StdError *res);
    Get(const protobuf::StdError &res);

    ~Get();

    void set_code(GetErrors);
    GetErrors get_error_codes() const override;
private:
    bool m_takeOvnership;
    protobuf::StdError *m_data;
    bool m_isMutable = true;
};

}

class Category: public responses::ICategory{
    // IUser interface
public:
    Category(protobuf::CategoryRes *res);
    Category(const protobuf::CategoryRes &res);

    ~Category();

    boost::optional<ActionId> action_type() const override;
    void clear_action() override;

    bool has_add() const override;
    category::IAdd *add() override;
    const category::IAdd &get_add() const override;

    bool has_get() const override;
    category::IGet *get() override;
    const category::IGet &get_get() const override;

    protobuf::CategoryRes *detachData();
private:
    protobuf::CategoryRes *m_data;
    bool m_takeOvnership;
    bool m_isMutable;

    mutable std::shared_ptr<category::IAdd> m_add;
    mutable std::shared_ptr<category::IGet> m_get;
};
}
