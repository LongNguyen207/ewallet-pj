#ifndef AUTH_H
#define AUTH_H

#include <string>
#include "user.h"

class Auth {
public:
    static bool registerUser();
    static bool loginUser();
    static bool activateAccount();
    static bool changePassword();
    //
    static bool transferPoints(const std::string& fromUser);
    static void viewTransactionHistory(const std::string& username);
    static void viewBalance(const std::string& username);


private:
    static bool userExists(const std::string& username);
    static std::string hashPassword(const std::string& password);
    static std::string generateOTP();
    static bool verifyOTP(const std::string& otp);

    static void saveUserData(const std::string& username, const std::string& hashedPassword, const UserInfo& info);
    static bool loadUserData(const std::string& username, std::string& hashedPassword, UserInfo& info);
};

#endif // AUTH_H
