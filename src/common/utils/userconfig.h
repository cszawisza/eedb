 #pragma once

#include <QJsonObject>
#include <string>

namespace eedb {
namespace utils {

using namespace std;

///NOTE implement and test
class UserConfig
{
public:
    explicit UserConfig( string json );

    QString toString() const;
    string toStdString() const;

private:
    QByteArray getJson() const ;
    QJsonObject m_config;
};

}
}
