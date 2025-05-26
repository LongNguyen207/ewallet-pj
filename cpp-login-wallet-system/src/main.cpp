#include <iostream>
#include "../include/Auth.h"

int main() {
    while (true) {
        std::cout << "1. Dang ky\n"
                  << "2. Kich hoat tai khoan\n"
                  << "3. Dang nhap\n"
                  << "4. Doi mat khau\n"
                  << "0. Thoat\n"
                  << "Lua chon: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                Auth::registerUser();
                break;
            case 2:
                Auth::activateAccount();
                break;
            case 3:
                Auth::loginUser();
                break;
            case 4:
                Auth::changePassword();
                break;
            case 0:
                std::cout << "Thoat chuong trinh.\n";
                return 0;
            default:
                std::cout << "Lua chon khong hop le, vui long thu lai.\n";
        }
    }
}
