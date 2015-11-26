#pragma once

#include <QString>
#include <QUrl>
#include <string>

class Url{
public:

    operator QUrl() const {
        QUrl url;
        url.setHost(QString::fromStdString(host()));
        url.setPort(port());
        url.setScheme("ws");
        return url;
    }

    std::string host() const;
    void setHost(const std::string &host);
    void setHost(const QString &host);
    uint16_t port() const;
    void setPort(const uint16_t &port);
private:
    std::string m_host;
    uint16_t m_port;
};

inline std::string Url::host() const
{
    return m_host;
}

inline void Url::setHost(const std::string &host)
{
    m_host = host;
}

inline void Url::setHost(const QString &host)
{
    m_host=host.toStdString();
}
inline uint16_t Url::port() const
{
    return m_port;
}

inline void Url::setPort(const uint16_t &port)
{
    m_port = port;
}

