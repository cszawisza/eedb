#pragma once

#include <QObject>
#include "Interfaces/UserResponses.hpp"
class QString;


class ILoginVerificator : public QObject
{
    Q_OBJECT
public:
    virtual ~ILoginVerificator() = default;

public slots:
    virtual void loginResponseReceived( const responses::user::ILogin &msg) const = 0;

signals:
    void loginSuccess() const;
    void loginError() const;
    void loginError( QString ) const;
};
