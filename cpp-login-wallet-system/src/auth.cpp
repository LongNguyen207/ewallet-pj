#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "../include/Auth.h"
#include <filesystem>

bool Auth::userExists(const std::string& username) {
    std::ifstream file("data/users/" + username + ".txt");
    return file.good();
}

std::string Auth::hashPassword(const std::string& password) {
    std::string hashed = password;
    for (char& c : hashed) {
        c = c + 1;
    }
    return hashed;
}

std::string Auth::generateOTP() {
    srand(static_cast<unsigned int>(time(nullptr)));
    std::string otp = "";
    for (int i = 0; i < 6; i++) {
        otp += std::to_string(rand() % 10);
    }
    return otp;
}

bool Auth::verifyOTP(const std::string& otp) {
    std::string inputOTP;
    std::cout << "Nhap OTP: ";
    std::cin >> inputOTP;
    return inputOTP == otp;
}

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

    // Tạo thư mục cần thiết nếu chưa có
std::filesystem::create_directories("data/users");
std::filesystem::create_directories("data/wallets");
std::filesystem::create_directories("data/history");

    saveUserData(username, hashPassword(password), newUser);

    std::ofstream wallet("data/wallets/" + username + ".txt");
    wallet << 1000;
    wallet.close();

    std::cout << "Dang ky thanh cong va tai khoan da kich hoat.\n";
    return true;
}

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
    } else {
        std::cout << "Mat khau sai!\n";
        return false;
    }
}

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

bool Auth::transferPoints(const std::string& fromUser) {
    std::string toUser;
    int amount;

    std::cout << "Nhap ten nguoi nhan: ";
    std::cin >> toUser;
    std::cout << "Nhap so diem muon chuyen: ";
    std::cin >> amount;

    if (!userExists(toUser)) {
        std::cout << "Nguoi nhan khong ton tai.\n";
        return false;
    }

    std::string fromPath = "data/wallets/" + fromUser + ".txt";
    std::string toPath = "data/wallets/" + toUser + ".txt";

    int fromBalance = 0, toBalance = 0;
    std::ifstream finFrom(fromPath);
    if (finFrom.is_open()) {
        finFrom >> fromBalance;
        finFrom.close();
    }

    if (fromBalance < amount) {
        std::cout << "So du khong du.\n";
        return false;
    }

    std::ifstream finTo(toPath);
    if (finTo.is_open()) {
        finTo >> toBalance;
        finTo.close();
    }

    fromBalance -= amount;
    toBalance += amount;

    std::ofstream foutFrom(fromPath);
    foutFrom << fromBalance;
    foutFrom.close();

    std::ofstream foutTo(toPath);
    foutTo << toBalance;
    foutTo.close();

    std::ofstream hFrom("data/history/" + fromUser + ".txt", std::ios::app);
    std::ofstream hTo("data/history/" + toUser + ".txt", std::ios::app);
    std::string timeStr = std::to_string(time(nullptr));

    hFrom << "Chuyen " << amount << " diem cho " << toUser << " vao luc " << timeStr << "\n";
    hTo << "Nhan " << amount << " diem tu " << fromUser << " vao luc " << timeStr << "\n";

    hFrom.close();
    hTo.close();

    std::cout << "Chuyen thanh cong.\n";
    return true;
}

void Auth::viewTransactionHistory(const std::string& username) {
    std::ifstream file("data/history/" + username + ".txt");
    if (!file.is_open()) {
        std::cout << "Khong co lich su giao dich.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << "\n";
    }
    file.close();
}
void Auth::viewBalance(const std::string& username) {
    std::ifstream walletFile("data/wallets/" + username + ".txt");
    if (!walletFile.is_open()) {
        std::cout << "Khong tim thay vi cua ban.\n";
        return;
    }

    int balance = 0;
    walletFile >> balance;
    walletFile.close();

    std::cout << "So du hien tai cua ban la: " << balance << " diem.\n";
}
