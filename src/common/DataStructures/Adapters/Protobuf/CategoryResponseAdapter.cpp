#include "CategoryResponseAdapter.hpp"

#include "category.pb.h"

responses::category::Add::Add()
{

}


responses::category::Add::Add(protobuf::CategoryRes *)
{

}


responses::category::Add::~Add()
{

}


void responses::category::Add::set_code(responses::category::IAdd::AddErrors)
{

}

responses::category::Get::Get()
{
    Q_ASSERT(false);
}

responses::category::Get::Get(protobuf::CategoryRes_Get *res):
    m_takeOvnership(false),
    m_data(res),
    m_isMutable(true)
{

}

responses::category::Get::Get(const protobuf::CategoryRes_Get &res):
    m_takeOvnership(false),
    m_data(const_cast<protobuf::CategoryRes_Get *>(&res)),
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
}

responses::category::IAdd *responses::Category::add()
{
}

const responses::category::IAdd &responses::Category::get_add() const
{
}

bool responses::Category::has_add() const
{
}


responses::Category::Category()
{

}

responses::Category::Category(protobuf::CategoryRes *res)
{

}

responses::Category::~Category()
{

}

boost::optional<responses::category::Action> responses::Category::stored_action() const
{
}

void responses::Category::clear_action()
{
//    m_data->h
}

bool responses::Category::has_get() const
{
    return m_data->has_get();
}

responses::category::IGet *responses::Category::get()
{
    m_get.reset(new category::Get(m_data->mutable_get()));
    return m_get.get();
}

const responses::category::IGet &responses::Category::get_get() const
{
    m_get.reset(new category::Get(m_data->get()));
    return *m_get;
}


responses::Category::Category(const protobuf::CategoryRes &res)
{

}
