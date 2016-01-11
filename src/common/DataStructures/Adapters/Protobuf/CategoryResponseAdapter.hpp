#pragma once

#include "../../Interfaces/CategoryResponses.hpp"

namespace protobuf{
    class CategoryRes;
    class CategoryRes_Get;
    class CategoryRes_Add;

    class ServerResponse;
}

namespace responses{
namespace category{

class Add: public IAdd{
public:
    Add();
    Add(protobuf::CategoryRes *);
    ~Add();

    void set_code(AddErrors);
private:
    protobuf::CategoryRes *m_data;
    bool m_takeOvnership = false;
};


class Get: public IGet {
    // IGet interface
public:
    Get();
    Get(protobuf::CategoryRes_Get *res);
    Get(const protobuf::CategoryRes_Get &res);

    ~Get();

    void set_code(GetErrors);

private:
    bool m_takeOvnership;
    protobuf::CategoryRes_Get *m_data;
    bool m_isMutable = true;
};

}

class Category: public responses::ICategory{
    // IUser interface
public:
    Category();
    Category(protobuf::CategoryRes *res);
    Category(const protobuf::CategoryRes &res);

    ~Category();

    boost::optional<category::Action> stored_action() const override;
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
    bool m_takeOvnership = false;

    mutable std::shared_ptr<category::IAdd> m_add;
    mutable std::shared_ptr<category::IGet> m_get;
};
}
