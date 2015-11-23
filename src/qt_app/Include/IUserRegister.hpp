#pragma once

#include <QObject>

class IUserRegister : public QObject
{
    Q_OBJECT
public:
    virtual void registerUser() const = 0;
    virtual ~IUserRegister() {}
};
