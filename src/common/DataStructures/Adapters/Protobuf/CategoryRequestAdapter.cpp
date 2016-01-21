#include "CategoryRequestAdapter.hpp"

#include "category.pb.h"


requests::Category::Category():
    m_takeovnership(true),
    m_data(new protobuf::CategoryReq(protobuf::CategoryReq::default_instance())),
    m_add(),
    m_get()
{

}

requests::Category::Category(protobuf::CategoryReq *req):
    m_takeovnership(false),
    m_data(req),
    m_add(),
    m_get()
{

}

requests::Category::Category(const protobuf::CategoryReq &req):
    m_takeovnership(false),
    m_data(const_cast<protobuf::CategoryReq *>(&req)),
    m_isMutable(false),
    m_add(),
    m_get()
{

}

requests::Category::~Category()
{
    if(m_takeovnership)
        delete m_data;
}

requests::category::IAdd *requests::Category::add()
{
    Q_ASSERT(m_isMutable);
    if(!m_add)
        m_add = std::make_shared<category::Add>( m_data->mutable_add() );
    m_add->operator = ( category::Add(m_data->mutable_add()));
    return m_add.get();
}

const requests::category::IAdd &requests::Category::get_add() const
{
    if(!m_add)
        m_add = std::make_shared<category::Add>( m_data->add() );
    m_add->operator = ( category::Add(m_data->add()));
    return *m_add;
}

bool requests::Category::has_add() const
{
    return m_data->has_add();
}

void requests::Category::clear_add()
{
    Q_ASSERT(m_isMutable);
    m_data->clear_add();
    m_add.reset();
}

requests::category::IGet *requests::Category::get()
{
    Q_ASSERT(m_isMutable);
    if(!m_get)
        m_get = std::make_shared<category::Get>( m_data->mutable_get() );
    m_get->operator = ( category::Get(m_data->mutable_get()));
    return m_get.get();
}

const requests::category::IGet &requests::Category::get_get() const
{
    if(!m_get)
        m_get = std::make_shared<category::Get>( m_data->get() );
    m_get->operator = ( category::Get(m_data->get()));
    return *m_get;
}

bool requests::Category::has_get() const
{
    return m_data->has_get();
}

void requests::Category::clear_get()
{
    Q_ASSERT(m_isMutable);
    m_data->clear_get();
    m_get.reset();
}

requests::category::Get::Get():
    m_takeOvnership(false),
    m_data( new protobuf::CategoryReq_Get( protobuf::CategoryReq_Get::default_instance() ))
{

}

requests::category::Get::Get(protobuf::CategoryReq_Get *get):
    m_takeOvnership(false),
    m_data(get)
{

}

requests::category::Get::Get(const protobuf::CategoryReq_Get &get):
    m_takeOvnership(false),
    m_data( const_cast<protobuf::CategoryReq_Get *>(&get) ),
    m_isMutable(true)
{

}

requests::category::Get::~Get()
{
    if(m_takeOvnership)
        delete m_data;
}

bool requests::category::Get::has_requestedUid() const
{
    return m_data->has_get_ids() && m_data->get_ids();
}

void requests::category::Get::request_uid(bool request)
{
    Q_ASSERT(m_isMutable);
    m_data->set_get_ids(request);
}

bool requests::category::Get::has_requestedParentUid() const
{
    return m_data->has_get_parent_id() && m_data->get_parent_id();
}

void requests::category::Get::request_parentUid(bool request)
{
    Q_ASSERT(m_isMutable);
    m_data->set_get_parent_id(request);
}

bool requests::category::Get::has_requestedName() const
{
    return m_data->has_get_name() && m_data->get_name();
}

void requests::category::Get::request_name(bool request)
{
    Q_ASSERT(m_isMutable);
    m_data->set_get_name(request);
}

requests::category::Criteria::Criteria():
    m_takeOvnership(true),
    m_data( new protobuf::CategoryReq_Get_Where(protobuf::CategoryReq_Get_Where::default_instance())),
    m_isMutable(true)
{
}

requests::category::Criteria::Criteria(protobuf::CategoryReq_Get_Where *crit):
    m_takeOvnership(true),
    m_data( crit ),
    m_isMutable(true)
{
}

requests::category::Criteria::Criteria(const protobuf::CategoryReq_Get_Where &crit):
    m_takeOvnership(true),
    m_data( const_cast<protobuf::CategoryReq_Get_Where *>(&crit) ),
    m_isMutable(false)
{
}

requests::category::Criteria::~Criteria()
{
    if(m_takeOvnership)
        delete m_data;
}

void requests::category::Criteria::request_all(bool request)
{
    Q_ASSERT(m_isMutable);
    m_data->set_all_groups(request);
}

bool requests::category::Criteria::has_requested_all() const
{
    return m_data->has_all_groups();
}


boost::optional<ActionId> requests::Category::action_type() const
{
    ///TODO implement
    return boost::none;
}


requests::category::Add::Add(protobuf::CategoryReq_Add *add):
    m_data(add),
    m_takeOvnership(false),
    m_isMutable(true)
{

}

requests::category::Add::Add(const protobuf::CategoryReq_Add &add):
    m_data(const_cast<protobuf::CategoryReq_Add *>(&add)),
    m_takeOvnership(false),
    m_isMutable(false)
{

}

requests::category::Add::~Add()
{
    if(m_takeOvnership)
        delete m_data;
}

String requests::category::Add::get_name() const
{
    return m_data->name();
}

void requests::category::Add::set_name(String name)
{
    Q_ASSERT(m_isMutable);
    m_data->set_name(name);
}

bool requests::category::Add::has_name() const
{
    return m_data->has_name();
}

void requests::category::Add::clear_name()
{
    Q_ASSERT(m_isMutable);
    m_data->clear_name();
}

UID requests::category::Add::get_parentId() const
{
    return m_data->parent_id();
}

void requests::category::Add::set_parentId(UID id)
{
    Q_ASSERT(m_isMutable);
    m_data->set_parent_id(id);
}

bool requests::category::Add::has_parentId() const
{
    return m_data->has_parent_id();
}

void requests::category::Add::clear_parentId()
{
    Q_ASSERT(m_isMutable);
    m_data->clear_parent_id();
}

String requests::category::Add::get_description() const
{
    return m_data->description();
}

void requests::category::Add::set_description(String desc)
{
    Q_ASSERT(m_isMutable);
    m_data->set_description(std::move(desc));
}

bool requests::category::Add::has_description() const
{
    return m_data->has_description();
}

void requests::category::Add::clear_description()
{
    Q_ASSERT(m_isMutable);
    m_data->clear_description();
}
