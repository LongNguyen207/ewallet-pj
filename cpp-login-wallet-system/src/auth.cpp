#include "../include/Auth.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

// Kiểm tra tồn tại user
bool Auth::userExists(const std::string& username) {
    std::ifstream file("data/users/" + username + ".txt");
    return file.good();
}

// Băm mật khẩu đơn giản
std::string Auth::hashPassword(const std::string& password) {
    std::string hashed = password;
    for (char& c : hashed) {
        c = c + 1;
    }
    return hashed;
}

// Sinh OTP 6 chữ số
std::string Auth::generateOTP() {
    srand(static_cast<unsigned int>(time(nullptr)));
    std::string otp = "";
    for (int i = 0; i < 6; i++) {
        otp += std::to_string(rand() % 10);
    }
    return otp;
}

// Xác thực OTP
bool Auth::verifyOTP(const std::string& otp) {
    std::string inputOTP;
    std::cout << "Nhap OTP: ";
    std::cin >> inputOTP;
    return inputOTP == otp;
}

// Lưu dữ liệu user vào file
void Auth::saveUserData(const std::string& username, const std::string& hashedPassword, const UserInfo& info) {
    std::ofstream file("data/users/" + username + ".txt");
    if (file.is_open()) {
        file << hashedPassword << "\n";
        file << info.fullName << "\n";
        file << info.email << "\n";
        file << static_cast<int>(info.role) << "\n";
        file << (info.isActive ? 1 : 0) << "\n";
        file.close();
    }
}

// Đọc dữ liệu user từ file
bool Auth::loadUserData(const std::string& username, std::string& hashedPassword, UserInfo& info) {
    std::ifstream file("data/users/" + username + ".txt");
    if (!file.is_open()) return false;

    int roleInt;
    int activeInt;

    std::getline(file, hashedPassword);
    std::getline(file, info.fullName);
    std::getline(file, info.email);
    file >> roleInt;
    file >> activeInt;

    info.role = static_cast<Role>(roleInt);
    info.isActive = (activeInt == 1);

    info.username = username;

    return true;
}

// Đăng ký user mới (isActive = false)
bool Auth::registerUser() {
    std::string username, password, fullName, email;

    std::cout << "Nhap username: ";
    std::cin >> username;

    if (userExists(username)) {
        std::cout << "Tai khoan da ton tai!\n";
        return false;
    }

    std::cout << "Nhap mat khau: ";
    std::cin >> password;

    std::cout << "Nhap ho va ten: ";
    std::cin.ignore();
    std::getline(std::cin, fullName);

    std::cout << "Nhap email: ";
    std::getline(std::cin, email);

    UserInfo newUser;
    newUser.username = username;
    newUser.fullName = fullName;
    newUser.email = email;
    newUser.role = Role::User;
    newUser.isActive = false;

    std::string otp = generateOTP();
    std::cout << "Ma OTP kich hoat la: " << otp << std::endl;
    if (!verifyOTP(otp)) {
        std::cout << "OTP khong dung, dang ky that bai.\n";
        return false;
    }

    newUser.isActive = true;

    saveUserData(username, hashPassword(password), newUser);

    std::cout << "Dang ky thanh cong va tai khoan da kich hoat.\n";
    return true;
}

// Kích hoạt tài khoản (trường hợp chưa kích hoạt)
bool Auth::activateAccount() {
    std::string username;
    std::cout << "Nhap username: ";
    std::cin >> username;

    if (!userExists(username)) {
        std::cout << "Tai khoan khong ton tai!\n";
        return false;
    }

    std::string hashedPassword;
    UserInfo info;
    if (!loadUserData(username, hashedPassword, info)) {
        std::cout << "Loi doc du lieu user.\n";
        return false;
    }

    if (info.isActive) {
        std::cout << "Tai khoan da kich hoat truoc do.\n";
        return true;
    }

    std::string otp = generateOTP();
    std::cout << "Ma OTP kich hoat la: " << otp << std::endl;
    if (!verifyOTP(otp)) {
        std::cout << "OTP khong dung, kich hoat that bai.\n";
        return false;
    }

    info.isActive = true;
    saveUserData(username, hashedPassword, info);
    std::cout << "Kich hoat tai khoan thanh cong.\n";
    return true;
}

// Đăng nhập
bool Auth::loginUser() {
    std::string username, password;

    std::cout << "Nhap username: ";
    std::cin >> username;

    if (!userExists(username)) {
        std::cout << "Tai khoan khong ton tai!\n";
        return false;
    }

    std::string storedHashedPassword;
    UserInfo info;
    if (!loadUserData(username, storedHashedPassword, info)) {
        std::cout << "Loi doc du lieu user.\n";
        return false;
    }

    if (!info.isActive) {
        std::cout << "Tai khoan chua kich hoat, vui long kich hoat truoc.\n";
        return false;
    }

    std::cout << "Nhap mat khau: ";
    std::cin >> password;

    if (hashPassword(password) == storedHashedPassword) {
        std::cout << "Dang nhap thanh cong!\n";
        return true;
    }
    else {
        std::cout << "Mat khau sai!\n";
        return false;
    }
}

// Đổi mật khẩu (cần OTP)
bool Auth::changePassword() {
    std::string username;
    std::cout << "Nhap username: ";
    std::cin >> username;

    if (!userExists(username)) {
        std::cout << "Tai khoan khong ton tai!\n";
        return false;
    }

    std::string storedHashedPassword;
    UserInfo info;
    if (!loadUserData(username, storedHashedPassword, info)) {
        std::cout << "Loi doc du lieu user.\n";
        return false;
    }

    std::string otp = generateOTP();
    std::cout << "Ma OTP doi mat khau la: " << otp << std::endl;
    if (!verifyOTP(otp)) {
        std::cout << "OTP khong dung, doi mat khau that bai.\n";
        return false;
    }

    std::string newPassword;
    std::cout << "Nhap mat khau moi: ";
    std::cin >> newPassword;

    saveUserData(username, hashPassword(newPassword), info);

    std::cout << "Doi mat khau thanh cong.\n";
    return true;
}
