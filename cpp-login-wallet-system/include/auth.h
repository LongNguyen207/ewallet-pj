#ifndef AUTH_H
#define AUTH_H

#include <string>

class Auth {
public:
    static bool registerUser();
    static bool loginUser();
};

// Hàm kiểm tra sự tồn tại của tài khoản
bool userExists(const std::string& username);

// Hàm băm mật khẩu đơn giản
std::string hashPassword(const std::string& password);

#endif
