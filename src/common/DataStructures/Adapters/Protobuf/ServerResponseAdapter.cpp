#include "ServerResponseAdapter.hpp"

#include "UserResponseAdapter.hpp"
#include "CategoryResponseAdapter.hpp"

#include "message_conteiner.pb.h"
#include "DefinedActions.hpp"

ServerResponse::ServerResponse():
    m_data(new protobuf::ServerResponse(protobuf::ServerResponse::default_instance()) ),
    m_takeOvnership(true),
    m_user(),
    m_category()
{
    m_buffer.reserve(1024*500); // reserve 500k of buffer data
}

ServerResponse::ServerResponse(protobuf::ServerResponse *req):
    m_data(req),
    m_takeOvnership(false),
    m_user(),
    m_category()
{
    m_buffer.reserve(1024*500); // reserve 500k of buffer data
}

ServerResponse::~ServerResponse()
{
    if(m_takeOvnership)
        delete m_data;
}

void ServerResponse::set_response_id(uint64_t id)
{
    m_data->set_response_id(id);
}

UID ServerResponse::response_id() const
{
    return m_data->response_id();
}

void ServerResponse::set_in_response_to(uint64_t id)
{
    m_data->set_in_response_to(id);
}

UID ServerResponse::in_response_to() const
{
    return m_data->in_response_to();
}

responses::IUser *ServerResponse::user()
{
    m_user.reset( new responses::User(m_data->mutable_userres()));
    return m_user.get();
}

const responses::IUser &ServerResponse::get_user() const
{
    m_user.reset( new responses::User(m_data->userres()));
    return *m_user;
}

bool ServerResponse::has_user() const
{
    return m_data->has_userres();
}

void ServerResponse::clear_user()
{
    m_data->clear_userres();
}

responses::ICategory *ServerResponse::category()
{
    m_category.reset( new responses::Category(m_data->mutable_categoryres()));
    return m_category.get();
}

const responses::ICategory &ServerResponse::get_category() const
{
    m_category.reset( new responses::Category(m_data->categoryres()));
    return *m_category;
}

bool ServerResponse::has_category() const
{
    return m_data->has_categoryres();
}

void ServerResponse::clear_category()
{
    m_data->clear_categoryres();
}

protobuf::ServerResponse *ServerResponse::rawPointer() const
{
    return m_data;
}

void ServerResponse::parse(const QByteArray &data)
{
    m_data->ParseFromArray(data.data(),data.size());
}

QByteArray ServerResponse::serialize() const
{
    int size = m_data->ByteSize();

    m_buffer.resize(size);
    m_data->SerializeToArray(m_buffer.data(), size);
    return m_buffer;
}

void ServerResponse::set_response_code(IServerResponse::ResponseFlags code)
{
    m_data->set_code(code);
}

IServerResponse::ResponseFlags ServerResponse::response_code() const
{
    int code = m_data->code();
    return ResponseFlags(code);
}


void ServerResponse::Clear()
{
    m_data->Clear();
}

boost::optional<ActionTypeId> ServerResponse::message_type() const
{
    switch (m_data->data_case()) {
    case protobuf::ServerResponse::kUserRes:
        return actions::typeUser;
    case protobuf::ServerResponse::kCategoryRes:
        return actions::typeCategory;
    default:
        break;
    }

    return boost::none;
}
