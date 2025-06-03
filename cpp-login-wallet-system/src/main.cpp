#include <iostream>
#include "../include/Auth.h"

int main() {
    std::string currentUser;
    bool loggedIn = false;

    while (true) {
        std::cout << "1. Dang ky\n"
                  << "2. Kich hoat tai khoan\n"
                  << "3. Dang nhap\n"
                  << "4. Doi mat khau\n"
                  << "5. Chuyen diem\n"
                  << "6. Xem lich su giao dich\n"
                  << "7. Xem so du\n"
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
                loggedIn = Auth::loginUser();
                if (loggedIn) {
                    std::cout << "Nhap lai username de xac nhan: ";
                    std::cin >> currentUser;
                }
                break;
            case 4:
                Auth::changePassword();
                break;
            case 5:
                if (loggedIn) {
                    Auth::transferPoints(currentUser);
                } else {
                    std::cout << "Vui long dang nhap truoc.\n";
                }
                break;
            case 6:
                if (loggedIn) {
                    Auth::viewTransactionHistory(currentUser);
                } else {
                    std::cout << "Vui long dang nhap truoc.\n";
                }
                break;
                case 7:
                if (loggedIn) {
                    Auth::viewBalance(currentUser);
                } else {
                    std::cout << "Vui long dang nhap truoc.\n";
                }
                break;

            case 0:
                std::cout << "Thoat chuong trinh.\n";
                return 0;
            default:
                std::cout << "Lua chon khong hop le, vui long thu lai.\n";
        }
    }
}
