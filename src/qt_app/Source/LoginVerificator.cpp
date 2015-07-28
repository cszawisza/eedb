#include "LoginVerificator.hpp"

LoginVerificator::LoginVerificator(QWebSocket & p_qWebSocket)
    : m_qWebSocket(p_qWebSocket)
{ }

bool LoginVerificator::wasLoginSucces() const
{
    return true;
}
