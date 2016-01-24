#include "LoginVerificator.hpp"
#include <Interfaces/UserResponses.hpp>
void LoginVerificator::loginResponseReceived(const responses::user::ILogin &msg) const
{
    using namespace responses::user;

    if( msg.is_successful()){
        emit loginSuccess();
    } else {
        emit loginError();
        auto err = msg.get_error_code();

        if(err == ILogin::Error_UserDontExists ){
            emit loginError( QString(tr("User don't exists in database", "blah")) );
        }
        else if( err == ILogin::Error_UserOnline ){
            emit loginError( QString(tr("User is online and should not try to login once more!", "blah2") ));
        }
        else if( err == ILogin::Error_WrongNameOrPass ){
            emit loginError( QString(tr("Wrong password")));
        }
        else
            emit loginError( QString(QStringLiteral("Unhandled error!")) );
    }
}
