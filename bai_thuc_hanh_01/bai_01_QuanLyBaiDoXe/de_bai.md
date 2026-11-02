# Đề bài: Hệ thống quản lý bãi đỗ xe - Giai đoạn 1

Xây dựng ứng dụng console C++ (C++11) theo OOP gồm 3 lớp: `Vehicle`, `ParkingLot`, `SystemInterface`.

- Thuộc tính private, truy cập qua getter/setter/constructor.
- Không dùng mảng, vector, con trỏ.
- Tối đa 3 bãi (S/M/L chứa 1/2/3 xe), quản lý bằng biến đơn và cờ bool.
- Phí đỗ: Car 6, Motorcycle 4, Bicycle 2 mỗi giờ; 2 giờ đầu +30% (giờ cao điểm 6-9, 15-18) hoặc -5% (giờ thấp điểm); từ giờ thứ 3 giảm 10%.
- Menu 9 chức năng (tạo/xóa bãi, thêm/lấy xe, hiển thị, lọc theo loại, báo cáo phí trung bình).
