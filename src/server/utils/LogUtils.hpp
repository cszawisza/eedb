#include <sqlpp11/postgresql/pgexception.h>
#include "spdlog/spdlog.h"

#include <QAbstractSocket>

inline std::ostream& operator<<(std::ostream& os, const QString& c) {
        return os << c.toStdString();
}

inline std::ostream& operator<<(std::ostream& os, const QAbstractSocket::SocketState& c) {

    switch (c) {
    case QAbstractSocket::UnconnectedState:
        os << "QAbstractSocket::UnconnectedState";
        break;
    case QAbstractSocket::HostLookupState:
        os << "QAbstractSocket::HostLookupState";
        break;
    case QAbstractSocket::ConnectingState:
        os << "QAbstractSocket::ConnectingState";
        break;
    case QAbstractSocket::ConnectedState:
        os << "QAbstractSocket::ConnectedState";
        break;
    case QAbstractSocket::BoundState:
        os << "QAbstractSocket::BoundState";
        break;
    case QAbstractSocket::ListeningState:
        os << "QAbstractSocket::ListeningState";
        break;
    case QAbstractSocket::ClosingState:
        os << "QAbstractSocket::ClosingState";
        break;
    }
    return os;
}

#define LOG_DB_EXCEPTION(e)\
if(e.code().pgClass().isError())\
    LOG_DB_ERROR(e);\
else{\
    LOG_DB_WARNING(e); \
}


#define LOG_DB_ERROR(e) LogDbError(e, __PRETTY_FUNCTION__ )
inline void LogDbError(const sqlpp::postgresql::pg_exception &e, const char* function){
    spdlog::get("Server")->error("{}: {}", function, e.what() );
}

#define LOG_DB_WARNING(e) LogDbWarning(e, __PRETTY_FUNCTION__ )
inline void LogDbWarning(const sqlpp::postgresql::pg_exception &e, const char* function){
    spdlog::get("Server")->warn("{}: {}", function, e.what() );
}

inline std::shared_ptr<spdlog::logger> getServerLoger(){
    return spdlog::get("Server");
}
