# Automotive Software Stack (AUTOSAR-inspired)

## 📖 Tổng quan dự án
Dự án phát triển hệ thống phần mềm nhúng (Embedded Software Stack) tuân thủ kiến trúc phân lớp (Layered Architecture) lấy cảm hứng từ chuẩn **AUTOSAR (Classic Platform)**. Dự án được phát triển trên nền tảng phần cứng **STM32 (Cortex-M3)**, tập trung vào việc tự xây dựng các thành phần cốt lõi từ mức thấp nhất (Bare-metal) nhằm hiểu sâu sắc về kiến trúc hệ thống ô tô thời gian thực.

## 🏗 Kiến trúc hệ thống
Hệ thống được thiết kế theo mô hình 4 tầng tiêu chuẩn:

* **Application Layer (SWC):** Chứa các Software Components (Diagnostic, Vehicle Command, Engine Status).
* **RTE (Run-Time Environment):** Lớp trừu tượng hóa giao tiếp, kết nối các SWCs với các dịch vụ bên dưới.
* **Service/Middleware Layer:** * 
    * **COM:** Cung cấp dịch vụ chẩn đoán lỗi (UDS).
    * **CSM:** Cung cấp dịch vụ mã hóa/băm (AES, SHA) với cơ chế Job Management.
    * **System:** Quản lí lỗi Det, Dem.
* **ECU Abstraction & MCAL:** Các Driver điều khiển phần cứng (CAN, LIN, IO) 
* **Custom OS Kernel** Đã hoàn thành phần nhân và hoạt động thử. Đang phát triển hướng OSEK VDX

## ⚙️ Các thành phần cốt lõi
1.  **Custom RTOS Kernel (OSEK-like):**
    * Lập lịch ưu tiên (Preemptive Scheduler).
    * Cơ chế Context Switching (PendSV/SVC) trên Cortex-M3.
2.  **Crypto Driver:**
    * Cấu trúc Job-based (ProcessJob) chuẩn AUTOSAR.
    * Cơ chế Dispatcher sử dụng Service Mapping (Lookup Table).
    * Tích hợp DET (Development Error Tracer) để đảm bảo tính an toàn.
3.  **Communication Stack:**
    * Mô phỏng PduR (PDU Router) cho giao tiếp CAN và LIN và DCM.
4.  **Io Stack:**
    * Phát triển Io, Adc.
5.  **Swc:**
    * Hiện cung cấp dịch vụ cho 3 SWC mô phỏng theo 1 dự án nhỏ (có thể checkout các branch ECU_COM và ECU_DIAG để thêm thông tin chi tiết dự án) là Diag(UDS), Gửi dữ liệu định kì cập nhập Ecu và Parse gói tin từ các EVCU truyền về.

## 📁 Cấu trúc thư mục
```text
/
├── README.md/                  # Sơ đồ kiến trúc & Tài liệu thiết kế
├── App/                    
│   ├── Swc_Diag/               # 
│   ├── Swc_EngineStatus/       # 
│   ├── Swc_VehicleCommand/     # 
├── Rte/                        # 
├── Bsw/                            
│   ├── Mcal/                   
│       ├── ComDriver/          # 
│       ├── CryptoDriver/       # 
│       ├── IoDriver/           # 
│       ├── McuDriver/          # 
│   ├── EcuAbstraction/     
│       ├── ComHwAb/            # 
│       ├── IoHwAb/             # 
│   ├── Service/
│       ├── ComService/         # 
│       ├── SystemService/      # 
├── System/ 
│   ├── Debug/                  # 
│   ├── Driver/
│       ├── CMSIS/              # 
│       ├── Common/             # 
│   ├── Startup/                # 
│   ├── Linker/                 # 
├──
├── Makefile/                   # 
└── main.c/                     # 

```

## 🛠 Công cụ & Môi trường

Hardware: STM32F103 (Cortex-M3)

Compiler: ARM-GCC (GNU Arm Embedded Toolchain)

Development Philosophy: AUTOSAR Architecture & OSEK VDX

Communication: CAN, LIN Protocols

## 💡 Điểm nổi bật

Zero-dependency: Tự xây dựng Kernel từ mức Assembly/C, không phụ thuộc vào thư viện RTOS bên ngoài.

Modular Design: Kiến trúc có tính mở rộng cao, dễ dàng thay thế hoặc thêm mới dịch vụ (service) mà không ảnh hưởng đến core logic.

Defensive Programming: Tuân thủ chặt chẽ việc kiểm soát con trỏ, lỗi hệ thống thông qua Det_ReportError.

## 🚀 Hướng phát triển

[ ] Hoàn thiện NvM (Non-volatile Memory Manager).

[ ] Tích hợp mã hóa vào lưu trữ dữ liệu nhạy cảm.

[ ] Tối ưu hóa hiệu năng theo chuẩn ISO 26262.



## 👤 Author

> **Luu Hoang Phuc**
> 📧 **Email:** `luuphuc20012001@gmail.com`
