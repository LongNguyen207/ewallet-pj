#ifndef USER_H
#define USER_H

#include <string>

enum class Role {
    User,
    Admin
};

struct UserInfo {
    std::string fullName;
    std::string email;
    Role role;
};

#endif // USER_H
