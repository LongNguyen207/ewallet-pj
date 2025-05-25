#include <iostream>
#include "auth.h"

int main() {
    while (true) {
        std::cout << "1. Dang ky\n2. Dang nhap\n0. Thoat\nLua chon: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(); // loại bỏ ký tự newline

        if (choice == 1) {
            Auth::registerUser();
        } else if (choice == 2) {
            Auth::loginUser();
        } else if (choice == 0) {
            std::cout << "Thoat chuong trinh.\n";
            break;
        } else {
            std::cout << "Lua chon khong hop le, vui long thu lai.\n";
        }
    }

    return 0;
}
