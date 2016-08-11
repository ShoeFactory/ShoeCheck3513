#include "user.h"

User::User()
{
    role = User::Normal;
}
int User::getRole() const
{
    return role;
}

void User::setRole(const int &value)
{
    role = (UserRole)value;
}
QString User::getName() const
{
    return name;
}

void User::setName(const QString &value)
{
    name = value;
}
QString User::getTelephone() const
{
    return telephone;
}

void User::setTelephone(const QString &value)
{
    telephone = value;
}
int User::getId() const
{
    return id;
}

void User::setId(int value)
{
    id = value;
}
QString User::getPasswd() const
{
    return passwd;
}

void User::setPasswd(const QString &value)
{
    passwd = value;
}






