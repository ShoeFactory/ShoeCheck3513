#include "userauth.h"

UserAuth *UserAuth::userAuth = NULL;

UserAuth *UserAuth::getUserInstance()
{
    if(userAuth == NULL)
        userAuth = new UserAuth;
    return userAuth;
}

UserAuth::UserAuth(QObject *parent) : QObject(parent)
{

}
User UserAuth::getCurrentUser() const
{
    return currentUser;
}

void UserAuth::setCurrentUser(const User &value)
{
    currentUser = value;
}

