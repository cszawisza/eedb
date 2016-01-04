#include "CategoryRequestAdapter.hpp"

#include "category.pb.h"

requests::category::Add::Add()
{
}


requests::category::IAdd *requests::Category::add()
{
}

const requests::category::IAdd &requests::Category::get_add() const
{
}

void requests::Category::assign(requests::category::IAdd *)
{
}

bool requests::Category::has_add() const
{
}

void requests::Category::clear_add()
{
}

String requests::category::Add::get_name() const
{
    return m_data->name();
}

void requests::category::Add::set_name(String name)
{
    m_data->set_name(name);
}

bool requests::category::Add::has_name() const
{
    return m_data->has_name();
}

void requests::category::Add::clear_name()
{
    m_data->clear_name();
}

UID requests::category::Add::get_parentId() const
{
}

void requests::category::Add::set_parentId(UID id)
{
}

bool requests::category::Add::has_parentId() const
{
}

void requests::category::Add::clear_parentId()
{
}

String requests::category::Add::get_description() const
{
}

void requests::category::Add::set_description(String desc)
{
}

bool requests::category::Add::has_description() const
{
}

void requests::category::Add::clear_description()
{
}
