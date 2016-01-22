#include "iprocessor.h"

#include "database/idatabase.h"
#include "auth/acl.hpp"

#include <QObject>
#include <QSharedPointer>
#include <QDebug>

std::atomic<quint64> IMessageProcessingUnit::m_response_id;


IMessageProcessingUnit::IMessageProcessingUnit():
m_response( nullptr )
{
}

void IMessageProcessingUnit::setOutputData(std::shared_ptr<IServerResponse> frame){
    m_response = frame;
}

void IMessageProcessingUnit::setUserData(std::shared_ptr<UserData> userData){
    m_userData.swap(userData);
}

void IMessageProcessingUnit::clear(){
    m_userData.reset();
}

std::shared_ptr<UserData> IMessageProcessingUnit::user(){
    if(!m_userData)
        m_userData = std::make_shared<UserData>();
    return m_userData;
}

void IMessageProcessingUnit::process(IClientRequest *req){
    prepareNewResponse();
    m_response->set_response_code( IServerResponse::Error_UnknownMessage );
}

void IMessageProcessingUnit::process(DB &db, IClientRequest *req){
    process(req);
}

IServerResponse *IMessageProcessingUnit::response() {
    return m_response.get();
}

void IMessageProcessingUnit::prepareNewResponse()
{
    m_response->set_response_code( 0 );
    m_response->set_response_id( m_response_id++ );
}

void IMessageProcessingUnit::sendServerError( IServerResponse::ResponseFlags e){
    response()->set_response_code( e );
}

