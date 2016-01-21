#include "CategoryResponseAdapter.hpp"

#include "category.pb.h"

responses::category::Add::Add(protobuf::StdError *add):
    m_data(add),
    m_takeOvnership(false),
    m_isMutable(true)
{

}

responses::category::Add::Add(const protobuf::StdError &add):
    m_data(const_cast<protobuf::StdError*>(&add)),
    m_takeOvnership(false),
    m_isMutable(false)
{

}


responses::category::Add::~Add()
{
    if(m_takeOvnership)
        delete m_data;
}


void responses::category::Add::set_code(responses::category::IAdd::AddErrors e)
{
    m_data->set_error_code(e);
}

responses::category::Get::Get(protobuf::StdError *res):
    m_takeOvnership(false),
    m_data(res),
    m_isMutable(true)
{

}

responses::category::Get::Get(const protobuf::StdError &res):
    m_takeOvnership(false),
    m_data(const_cast<protobuf::StdError *>(&res)),
    m_isMutable(false)
{
}

responses::category::Get::~Get()
{
    if(m_takeOvnership)
        delete m_data;
}

void responses::category::Get::set_code(responses::category::IGet::GetErrors)
{
    ///TODO Implement
}

responses::category::IGet::GetErrors responses::category::Get::get_error_codes() const
{
    ///TODO Implement
}

responses::category::IAdd *responses::Category::add()
{
    Q_ASSERT(m_isMutable);
    m_add.reset(new responses::category::Add(m_data->mutable_add()));
    return m_add.get();
}

const responses::category::IAdd &responses::Category::get_add() const
{
    m_add.reset(new responses::category::Add(m_data->add()));
    return *m_add;
}

bool responses::Category::has_add() const
{
    return m_data->has_add();
}

responses::Category::Category(protobuf::CategoryRes *res):
    m_data(res),
    m_takeOvnership(false),
    m_isMutable(true)
{
}

responses::Category::Category(const protobuf::CategoryRes &res):
    m_data(const_cast<protobuf::CategoryRes*>(&res)),
    m_takeOvnership(false),
    m_isMutable(false)
{

}

responses::Category::~Category()
{
    if(m_takeOvnership)
        delete m_data;
}

boost::optional<ActionId> responses::Category::action_type() const
{
    ///TODO implement
    return boost::none;
}

void responses::Category::clear_action()
{
    Q_ASSERT(m_isMutable);
    m_data->Clear();
}

bool responses::Category::has_get() const
{
    return m_data->has_get();
}

responses::category::IGet *responses::Category::get()
{
    Q_ASSERT(m_isMutable);
    m_get.reset(new category::Get(m_data->mutable_get()));
    return m_get.get();
}

const responses::category::IGet &responses::Category::get_get() const
{
    m_get.reset(new category::Get(m_data->get()));
    return *m_get;
}

responses::category::IAdd::AddErrors responses::category::Add::get_error_codes() const
{
    return IAdd::AddErrors(m_data->error_code());
}
