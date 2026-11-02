# Bài 01 - Quản lý bãi đỗ xe

## Biên dịch và chạy
```
g++ -std=c++11 -o main main.cpp
./main
```

## Ghi chú
- Mã xe (vehicleID) và mã bãi (parkID) không được trùng.
- Loại xe nhập không phân biệt hoa/thường.
- Điều kiện hợp lệ: giờ vào + số giờ đỗ <= 24 (xe ra trong cùng ngày).
- Xóa bãi thì các xe trong bãi cũng bị xóa.
- Đơn giá lấy theo đề (6/4/2) nên phí in ra là số theo đơn giá đó.
