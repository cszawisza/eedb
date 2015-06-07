 #pragma once

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>


namespace eedb {
namespace utils {

using namespace std;

class UserConfig
{
    QString toString() const;
    string toStdString() const;

private:
QJsonObject m_config;
};

}
}
