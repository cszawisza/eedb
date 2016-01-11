#pragma once

#include "../../Interfaces/CategoryRequests.hpp"

class IAcl;

namespace protobuf{
class CategoryReq;
class CategoryReq_Add;
class CategoryReq_Get;
class CategoryReq_Get_Where;
}

namespace requests{
namespace category{
class Criteria : public ICriterion{
public:
    Criteria();
    Criteria( protobuf::CategoryReq_Get_Where *crit );
    Criteria( const protobuf::CategoryReq_Get_Where &crit );
    ~Criteria();

    void request_all(bool request = true) override;
    bool has_requested_all() const override;

private:
    bool m_takeOvnership;
    protobuf::CategoryReq_Get_Where *m_data;
    bool m_isMutable = true;
};

class Add : public IAdd{
    // IAdd interface
public:
    Add();
    Add( protobuf::CategoryReq_Add *add);
    Add( const protobuf::CategoryReq_Add &add );
    ~Add();

    String get_name() const;
    void set_name(String name);
    bool has_name() const;
    void clear_name();

    UID get_parentId() const;
    void set_parentId(UID id);
    bool has_parentId() const;
    void clear_parentId();

    String get_description() const;
    void set_description(String desc);
    bool has_description() const;
    void clear_description();

private:
    bool m_takeOvnership;
    protobuf::CategoryReq_Add *m_data;
    bool m_isMutable = true;
};

class Get : public IGet{
    // IGet interface
public:
    Get();
    Get( protobuf::CategoryReq_Get *get );
    Get( const protobuf::CategoryReq_Get &get);
    ~Get();

    bool has_requestedUid() const override;
    void request_uid(bool request = true) override;

    bool has_requestedParentUid() const override;
    void request_parentUid(bool request) override;

    bool has_requestedName() const override;
    void request_name(bool request = true) override;

//    ICriterion *criteria() override;
//    const ICriterion &get_criteria() const override;
//    void assign(ICriterion *) override;

private:
    bool m_takeOvnership;
    protobuf::CategoryReq_Get *m_data;
    bool m_isMutable = true;
};

}

class Category : public ICategory{
    // ICategory interface
public:
    Category();
    Category(protobuf::CategoryReq *req);
    Category(const protobuf::CategoryReq &req);
    ~Category();

    category::IAdd *add();
    const category::IAdd &get_add() const;
    bool has_add() const;
    void clear_add();

    category::IGet *get();
    const category::IGet &get_get() const;
    bool has_get() const;
    void clear_get();

private:
    bool m_takeovnership;
    protobuf::CategoryReq *m_data;
    bool m_isMutable = true;

    mutable std::shared_ptr<category::IAdd> m_add;
    mutable std::shared_ptr<category::IGet> m_get;
};

}
