#include "auth.h"
#include <iostream>
#include <fstream>
#include <string>

bool userExists(const std::string& username) {
    std::ifstream file("data/users/" + username + ".txt");
    return file.good();
}

std::string hashPassword(const std::string& password) {
    std::string hashed = password;
    for (char& c : hashed) {
        c = c + 1; // băm đơn giản: tăng mỗi ký tự 1 đơn vị
    }
    return hashed;
}

bool Auth::registerUser() {
    std::string username, password;
    std::cout << "Nhap ten dang nhap: ";
    std::cin >> username;

    if (userExists(username)) {
        std::cout << "Tai khoan da ton tai!\n";
        return false;
    }

    std::cout << "Nhap mat khau: ";
    std::cin >> password;

    std::string filepath = "data/users/" + username + ".txt";
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cout << "Khong the tao file tai khoan!\n";
        return false;
    }

    file << hashPassword(password) << std::endl;
    file.close();
    std::cout << "Dang ky thanh cong!\n";
    return true;
}

bool Auth::loginUser() {
    std::string username, password;
    std::cout << "Nhap ten dang nhap: ";
    std::cin >> username;

    if (!userExists(username)) {
        std::cout << "Tai khoan khong ton tai!\n";
        return false;
    }

    std::cout << "Nhap mat khau: ";
    std::cin >> password;

    std::string filepath = "data/users/" + username + ".txt";
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cout << "Khong the mo file tai khoan!\n";
        return false;
    }

    std::string storedHashedPassword;
    std::getline(file, storedHashedPassword);

    if (hashPassword(password) == storedHashedPassword) {
        std::cout << "Dang nhap thanh cong!\n";
        return true;
    } else {
        std::cout << "Mat khau sai!\n";
        return false;
    }
}
