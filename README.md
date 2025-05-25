# Hệ Thống Quản Lý Ví Điện Tử (Electronic Wallet System)

## Giới thiệu dự án
Dự án này là một hệ thống quản lý ví điện tử đơn giản, được phát triển bằng C++ để phục vụ việc đăng ký tài khoản, chuyển điểm giữa các ví, và quản lý thông tin người dùng. Mục tiêu là xây dựng một hệ thống an toàn, robust, và thân thiện với người dùng, phù hợp với yêu cầu của một bài tập nhóm sinh viên.

### Mục tiêu chính:
- Quản lý người dùng với tài khoản duy nhất (`username` không sửa được).
- Mỗi ví có mã định danh riêng (`walletID`), sinh tự động, duy nhất.
- Giao dịch an toàn với OTP và log trạng thái (`PENDING`, `COMMITTED`, `FAILED`).
- Quyền admin: Xem tất cả giao dịch, chỉnh thông tin user (trừ `username`).

---

## Thành viên tham gia dự án
| Tên thành viên       | Công việc được giao                          |
|----------------------|----------------------------------------------|
| Nguyễn Phi Long   | Phân tích yêu cầu, đề xuất tính năng, kiểm tra lỗi |
| Trần Thị B (mình)    | Lập trình chính, tối ưu mã nguồn, viết tài liệu |
| (Thêm nếu có)        | (Mô tả công việc)                            |

---

## Phân tích và đặc tả chức năng

### Yêu cầu chức năng
1. **Quản lý người dùng**:
   - Đăng ký user thường và admin (admin tạo bởi admin).
   - Kích hoạt tài khoản bằng OTP (hết hạn 24 giờ).
   - Đổi mật khẩu qua OTP, admin có mật khẩu tự sinh lần đầu.
   - Không cho phép sửa `username`.

2. **Quản lý ví**:
   - Mỗi ví có `walletID` duy nhất, sinh tự động, ẩn với user thường.
   - Hiển thị `walletID` trong log giao dịch và admin view.

3. **Giao dịch**:
   - Chuyển điểm giữa các ví (OTP xác nhận).
   - Log giao dịch: trạng thái, thời gian, `walletID`.
   - User xem lịch sử cá nhân, admin xem tất cả.

4. **Quyền admin**:
   - Xem danh sách user, chỉnh `fullName` (OTP), xem toàn bộ giao dịch.

5. **Xử lý trùng lặp**:
   - Đảm bảo `username` và `walletID` không trùng.
   - Phát hiện trùng khi khởi động, admin chọn giữ user nào, thông báo user.

6. **An toàn và robust**:
   - Backup và rollback khi crash.
   - Log lỗi trùng lặp (`duplicate_issues.txt`).

### Phân tích
- **Input**: Thông tin user (`username`, `password`, v.v.), điểm chuyển, OTP.
- **Output**: Thông báo đăng ký, giao dịch, lịch sử, log file.
- **Xử lý**: Kiểm tra tính duy nhất, sinh `walletID`, xác thực OTP, ghi file.

---

## Cách tải và dịch chương trình

### Yêu cầu hệ thống
- Hệ điều hành: Windows/Linux/MacOS (có trình biên dịch C++).
- Trình biên dịch: g++ (hoặc bất kỳ compiler C++11 trở lên).
- Không cần thư viện ngoài, chỉ dùng STL C++.

### Tải chương trình
1. Clone từ GitHub (giả sử bọn mình dùng Git):
   ```bash
   git clone https://github.com/username/electronic-wallet-system.git
   cd electronic-wallet-system





