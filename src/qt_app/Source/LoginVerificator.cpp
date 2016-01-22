#include "LoginVerificator.hpp"


LoginVerificator::LoginVerificator()
{
}

bool LoginVerificator::tryLogin(const std::string & p_password, const std::string & p_login) const
{
//    protobuf::ClientRequests l_clientRequests{};
//    protobuf::ClientRequest * l_clientRequest = l_clientRequests.add_request();

//    protobuf::UserReq::Credentials * l_credentials{};
//    l_credentials->set_nickname(p_login);

//    protobuf::UserReq::Login * l_login{};
//    l_login->set_allocated_cred(l_credentials);
//    l_login->set_password(p_password);

//    protobuf::UserReq * l_userReq{};
//    l_userReq->set_allocated_login(l_login);
//    l_clientRequest->set_allocated_userreq(l_userReq);
    return true;
}
