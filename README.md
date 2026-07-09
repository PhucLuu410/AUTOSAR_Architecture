# Automotive Embedded Software Stack

Hệ thống phần mềm nhúng ô tô được xây dựng theo kiến trúc phân lớp, lấy cảm hứng từ AUTOSAR Classic Platform và OSEK/VDX, triển khai trên STM32F103 (ARM Cortex-M3).

Mục tiêu của dự án là nghiên cứu và thực hành kiến trúc phần mềm ô tô thông qua việc tự xây dựng các thành phần từ mức thấp như Startup, Linker Script, Driver và RTOS Kernel đến Communication Stack, Diagnostic Services và Crypto Services.

> **Lưu ý:** Đây là dự án nghiên cứu và học tập lấy cảm hứng từ kiến trúc AUTOSAR Classic Platform và OSEK/VDX. Dự án không tuyên bố tuân thủ đầy đủ tiêu chuẩn AUTOSAR, OSEK hoặc ISO 26262.

---

## 📖 Tổng quan dự án

Các ECU hiện đại sử dụng kiến trúc phần mềm phân lớp nhằm tách biệt Application Logic, Communication Services, System Services và Hardware Driver.

Dự án này tập trung vào việc tự triển khai và nghiên cứu luồng hoạt động giữa các tầng của một hệ thống phần mềm nhúng ô tô.

Các mục tiêu chính:

* Hiểu kiến trúc phần mềm phân lớp trong Automotive Embedded Systems.
* Xây dựng Driver giao tiếp trực tiếp với phần cứng.
* Thiết kế interface giữa các software module.
* Xây dựng RTOS Kernel dựa trên các khái niệm của OSEK/VDX.
* Nghiên cứu luồng truyền dữ liệu giữa các tầng của Communication Stack.
* Xây dựng kiến trúc xử lý Diagnostic Service.
* Xây dựng Crypto Driver theo mô hình Job-based Processing.
* Thực hành debug và kiểm chứng hệ thống trên phần cứng thực tế.

---

## 🏗 Kiến trúc hệ thống

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

```text
/
├── README.md/                  # Sơ đồ kiến trúc & Tài liệu thiết kế.
├── App/                    
│   ├── Swc_Diag/               # Gửi request Diag, Nhận respond dựa theo chuẩn ISO-TP.
│   ├── Swc_EngineStatus/       # cập nhập định kì RPM, TEMP, Alive Counter cho eVCU.
│   ├── Swc_VehicleCommand/     # Parse gói tin định kì từ eVCU gửi trên mạng Can.
├── Rte/                        # Lớp trừu tượng Bsw cho các Swc.
├── Bsw/                            
│   ├── Mcal/                   
│       ├── ComDriver/          # Chứa cấu trúc Can Driver của Stm32f103.
│       ├── CryptoDriver/       # Chứa cấu trúc Crypto Software Driver của Stm32f103.
│       ├── IoDriver/           # Chứa cấu trúc Io Driver của Stm32f103 hỗ trợ Io, Adc.
│       ├── McuDriver/          # Chứa cấu trúc Mcu Driver của Stm32f103 cấu hình Clock.
│   ├── EcuAbstraction/     
│       ├── ComHwAb/            # Tầng trừu tượng hóa giao tiếp của Can Driver.
│       ├── IoHwAb/             # Tầng trừu tượng hóa giao tiếp của Can Driver.
│   ├── Service/
│       ├── ComService/         # Cung cấp dịch vụ Com, Uds, Iso-Tp, PduR.
│       ├── SystemService/      # Cung cấp mini Os OSEK-Like, và các service như Det, Dem.
├── System/ 
│   ├── Debug/                  # Trình debug stm32 file .svd.
│   ├── Driver/ 
│       ├── CMSIS/              # SDK CMSIS của hãng cung cấp.
│       ├── Common/             # Thư viện chung của Autosar.
│   ├── Startup/                # Startup Code
│   ├── Linker/                 # Linker Script
├──
├── Makefile/                   # Chương trình makefile theo trình GCC.
└── main.c/                     # Chương trình chính.

```

## 🛠 Công cụ & Môi trường

## 🔬 Kiểm thử và xác minh

Hệ thống được kiểm tra thông qua nhiều phương pháp:

* Debug bằng GDB.
* Kiểm tra MCU Register.
* Quan sát Task Stack.
* Theo dõi luồng thực thi bằng Breakpoint.
* Phân tích CAN Frame.
* Phân tích LIN Frame.
* Logic Analyzer.
* Quan sát State Machine trong Runtime.

Mỗi Test Case quan trọng nên được trình bày theo cấu trúc sau:

## 💡 Điểm nổi bật

Mô tả chức năng hoặc hành vi cần kiểm chứng.

### Input

```text
Frame nhận được hoặc Function Call
```

## 🚀 Hướng phát triển

```text
Module A
   |
   v
Module B
   |
   v
Module C
```

### Kết quả Analyzer / Debugger

1. **Gửi định kì gói tin vào eVCU**

![alt text](image.png)

![alt text](image-1.png)

Gửi dữ liệu liên tục từ Os_Task_10ms.
Luồng đi Swc->Rte->Com->PduR->CanIf->Can->Hardware.
TxConfirmation Được gọi để check luồng Tx.

2. **Parse định kì gói tin từ eVCU vào Com-Ecu**

![alt text](image-2.png)

Nhận dữ liệu từ Can qua Filter 0x180 chu kì 10ms.
Parse gói tin đẩy lên các Swc để lấy dữ liệu.
Luồng nhận Can->CanIf->PduR->Com->Rte->Swc.

3. **Gửi Request Diag dựa theo Iso-Tp từ Diag-Ecu vào eVCU**

3.1. Gửi yêu cầu mở phiên

Request:

![alt text](Media/image-24.png)

Respond:

![alt text](Media/image-25.png)

3.2. Gửi yêu cầu chẩn đoạn tốc độ động cơ

Data:

![alt text](Media/image-4.png)

Analyzer:

Request:

![alt text](Media/image-6.png)

Respond:

![alt text](Media/image-7.png)


3.3. Gửi yêu cầu chẩn đoán Nhiệt độ động cơ

Data:

![alt text](Media/image-8.png)

Analyzer:

Request:

![alt text](Media/image-9.png)

Respond:

![alt text](Media/image-10.png)


3.4. Gửi yêu cầu chẩn đoán Vin

Data:

![alt text](Media/image-11.png)


Analyzer:

Request:

![alt text](Media/image-12.png)

Respond:

![alt text](Media/image-13.png)

Gửi Cf và chờ bơm frame còn lại:

![alt text](Media/image-14.png)

Frame còn lại được bơm liên tục sau khi CanTp check xong buffer Uds và báo về eVCU:

![alt text](Media/image-15.png)

![alt text](Media/image-16.png)

3.5. Gửi yêu cầu chẩn đoán DTC

Data:

![alt text](Media/image-17.png)

Analyzer:

Request:

![alt text](Media/image-18.png)

Respond:

![alt text](Media/image-19.png)

Gửi Cf và chờ bơm frame còn lại:

![alt text](Media/image-20.png)

Frame còn lại được bơm liên tục sau khi CanTp check xong buffer Uds và báo về eVCU:

![alt text](Media/image-21.png)

![alt text](Media/image-22.png)

![alt text](Media/image-23.png)

Gửi Request yêu cầu mở phiên 0x10 0x03.
Nhận Respond phiên đã mở 0x50 0x03 0x00 0x32 0x01 0xf4.
Gửi Request dịch vụ cần chẩn đoán.
Nhận Respond và check buffer từ Dcm nếu đủ để nhận thì gửi FC để duy trì luồng nhận.
Luồng đi Ecu_Diag: Swc->Rte->Dcm->PduR->CanTp->CanIf->Can->Hardware.

## 👤 Author

> **Luu Hoang Phuc**
> 📧 **Email:** `luuphuc20012001@gmail.com`
