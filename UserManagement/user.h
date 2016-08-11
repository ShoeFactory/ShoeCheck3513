#ifndef USER_H
#define USER_H
#include <QString>



class User
{
public:
    enum UserRole{
        Admin=1,
        Normal=2,
    };

    User();

    int getRole() const;
    void setRole(const int &value);

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
