 #pragma once

#include <QJsonObject>
#include <string>

#include "user.pb.h"

namespace eedb {
namespace utils {

using namespace std;

class UserConfig
{
public:
    explicit UserConfig( string json );
    UserConfig(const pb::UserConfig &conf);

    QString toString() const;
    string toStdString() const;

private:
    QByteArray getJson() const ;
    QJsonObject m_config; ///TODO replace with protbuf message
    pb::UserConfig m_conf;
};

}
}
