#ifndef USER_H
#define USER_H
#include <QString>

typedef enum UserRole{
    Admin,
    Normal,
} UserRole;

class User
{
public:
    User();

    UserRole getRole() const;
    void setRole(const UserRole &value);

    QString getName() const;
    void setName(const QString &value);

    QString getTelephone() const;
    void setTelephone(const QString &value);

    int getId() const;
    void setId(int value);

    QString getPasswd() const;
    void setPasswd(const QString &value);

private:
    UserRole role;
    QString  name;
    QString  passwd;
    QString  telephone;
    int      id;
};

#endif // USER_H
