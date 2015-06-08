#include "userconfig.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QString>
#include <QByteArray>
#include <string>
#include <QDebug>

eedb::utils::UserConfig::UserConfig(std::string json)
{
    m_config = QJsonDocument::fromJson(QByteArray::fromRawData(json.data(), json.size())).object();
}

eedb::utils::UserConfig::UserConfig(const user::UserConfig &conf)
{
    m_conf.CopyFrom(conf);
}

QString eedb::utils::UserConfig::toString() const
{
    return QString(getJson());
}

std::string eedb::utils::UserConfig::toStdString() const
{
    return getJson().toStdString();
}

QByteArray eedb::utils::UserConfig::getJson() const
{
    return QJsonDocument(m_config).toJson(QJsonDocument::JsonFormat::Compact);
}
