# C++ project: Chương trình quản lý máy bay, chuyến bay của một hãng hàng không
## Chương trình gồm có các object:
- **Máy bay**: gồm các thông tin như số hiệu máy bay, loại máy bay, số dãy, số hàng. Mỗi máy bay có một số hiệu duy nhất. Nếu số dãy là 5 thì máy bay có các dãy A, B, C, D, E. Nếu số dòng là 20 thì máy bay có các hàng ghế đánh số từ 1 -> 20. Kết hợp dãy và hàng ta có được số vé. Theo như ví dụ trên thì có 100 vé từ A1,A2,...A19,A20,...E19,E20.
- **Chuyến bay**: gồm mã chuyến bay, ngày giờ khởi hành, sân bay đến, trạng thái, số hiệu MB, danh sách vé. Mỗi chuyến bay có 1 mã duy nhất. Trạng thái chuyến bay có 0(hủy chuyến), 1(còn vé), 2(hết vé), 3(hoàn tất).
- **Danh sách vé**: cho biết thông tin vé trên chuyến bay và số CCCD của khách hàng đã đặt vé đó. Danh sách chuyến bay luôn có sẫn thứ tự theo mã chuyến bay.
- **Hành khách**: gồm có CCCD, Họ, tên và phái.
## Chương trình có các chức năng sau:
- **Cập nhật danh sách máy bay(thêm, xóa, sửa)**.(Duy)
- **Cập nhật chuyến bay:** lập chuyến bay mới, hiệu chỉnh ngày giở khởi hành, hủy chuyến.(Nam)
- **Đặt vé:** cho phép đặt vé trên một chuyến bay. Mỗi vé đều phải ghi nhận CCCD của khách hàng. Nếu hành khách chưa có thông tin thì yêu cầu nhập thông tin khách hàng trước. Nếu đã có thì hiển thị thông tin ra cho khách hàng kiểm tra. Trên một chuyến bay, mỗi hành khách chỉ được mua một vé.(Anh)
- **Hủy vé:** Hủy vé đã đặt của hành khách.(Anh)
- In danh sách hành khách thuộc một chuyến bay dựa vào mã chuyến bay.(Anh)
- In danh sách các chuyến bay khởi hành trong ngày đd/mm/yyyy đến sân bay XXX mà còn vé.(Duy)
- Thống kê số lượt thực hiện chuyến bay của từng máy bay.(Nam)
Thư viện đi kèm: mylib(Thư viện này để xử lý phần giao diện cho chương trình)
