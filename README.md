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

Hệ thống được tổ chức theo kiến trúc phân lớp:

```text
+------------------------------------------------------+
|                  Application Layer                   |
|                                                      |
|   Diagnostic SWC   Vehicle Command   Engine Status   |
+--------------------------+---------------------------+
                           |
+--------------------------v---------------------------+
|                 Run-Time Environment                 |
|                         RTE                          |
+--------------------------+---------------------------+
                           |
+--------------------------v---------------------------+
|               Service / Middleware Layer             |
|                                                      |
|       DCM        Crypto Stack        NvM             |
|                                                      |
|                    PduR                              |
+--------------------------+---------------------------+
                           |
+--------------------------v---------------------------+
|              ECU Abstraction Layer                   |
|                                                      |
|             CanIf              LinIf                 |
|                                  |                   |
|                                LinTp                 |
+--------------------------+---------------------------+
                           |
+--------------------------v---------------------------+
|                       MCAL                           |
|                                                      |
|       CAN Driver    LIN Driver    GPIO Driver        |
+--------------------------+---------------------------+
                           |
+--------------------------v---------------------------+
|                 Custom RTOS Kernel                   |
|                                                      |
| Scheduler | Task Management | Context Switching      |
+--------------------------+---------------------------+
                           |
+--------------------------v---------------------------+
|                  STM32F103 MCU                       |
|                   ARM Cortex-M3                      |
+------------------------------------------------------+
```

---

## ⚙️ Các thành phần chính

### 1. Custom RTOS Kernel

Một RTOS Kernel nhỏ được xây dựng bằng C và ARM Assembly, dựa trên các khái niệm của OSEK/VDX.

Các chức năng chính:

* Priority-based Scheduling.
* Preemptive Scheduling.
* Quản lý trạng thái Task.
* Stack riêng cho từng Task.
* Context Switching thông qua PendSV.
* System Service thông qua SVC.
* Quản lý Stack Frame của Cortex-M3.
* Mutex và cơ chế đồng bộ tài nguyên cơ bản.

### Luồng Context Switching

```text
Task đang chạy
      |
      | Task có Priority cao hơn chuyển sang READY
      v
Scheduler
      |
      v
Trigger PendSV
      |
      v
Lưu Context của Task hiện tại
      |
      v
Cập nhật Task Control Block
      |
      v
Khôi phục Context của Task tiếp theo
      |
      v
Exception Return
      |
      v
Task tiếp theo bắt đầu chạy
```

### Kiểm chứng bằng Debugger

> Thêm hình debug tại đây.

```text
docs/images/os-context-switch.png
docs/images/task-state-debug.png
```

Nội dung nên thể hiện:

* Giá trị PSP/MSP trước và sau Context Switch.
* Stack Frame của Task.
* Sự thay đổi trạng thái Task.
* Luồng thực thi PendSV Handler.
* Quyết định của Scheduler khi có Task Priority cao hơn.

---

### 2. Communication Stack

Communication Stack được xây dựng theo kiến trúc phân lớp lấy cảm hứng từ AUTOSAR Classic.

Các module đang được triển khai:

* CAN Driver
* CanIf
* LIN Driver
* LinIf
* LinTp
* PduR

Mục tiêu chính là tách biệt phần xử lý giao tiếp cấp cao khỏi phần phụ thuộc trực tiếp vào phần cứng.

### Luồng truyền CAN

```text
Application SWC
      |
      v
     RTE
      |
      v
     COM
      |
      v
     PduR
      |
      v
    CanIf
      |
      v
  CAN Driver
      |
      v
 CAN Peripheral
      |
      v
    CAN Bus
```

Ví dụ, khi Application gửi dữ liệu:

1. SWC tạo yêu cầu truyền dữ liệu.
2. Dữ liệu được chuyển qua các interface của Communication Stack.
3. PduR định tuyến PDU đến Communication Interface phù hợp.
4. CanIf ánh xạ PDU sang cấu hình CAN tương ứng.
5. CAN Driver ghi frame vào CAN Peripheral.
6. Sau khi truyền hoàn tất, luồng Confirmation được trả ngược lên các tầng phía trên.

---

### Luồng LIN Transport Protocol

```text
Upper Layer
     |
     v
    PduR
     |
     v
    LinTp
     |
     v
    LinIf
     |
     v
  LIN Driver
     |
     v
 LIN Peripheral
```

LinTp được thiết kế theo State Machine để xử lý các Diagnostic Message có kích thước lớn hơn payload của một LIN Frame.

Ví dụ một chuỗi truyền:

```text
First Frame (FF)
       |
       v
Flow Control (FC)
       |
       v
Consecutive Frame (CF)
       |
       v
Consecutive Frame (CF)
       |
       v
Message Complete
       |
       v
Upper Layer Indication
```

### Kiểm chứng Communication Stack

> Thêm ảnh CAN/LIN Analyzer tại đây.

```text
docs/images/can-analyzer.png
docs/images/lin-first-frame.png
docs/images/lin-consecutive-frame.png
```

Với mỗi ảnh Analyzer, phần mô tả nên giải thích:

* CAN ID hoặc LIN PID.
* Loại Frame.
* Payload.
* Protocol State hiện tại.
* State Transition xảy ra sau khi nhận Frame.
* Callback nào được gọi trong Communication Stack.

---

### 3. Crypto Driver

Crypto Driver được thiết kế theo mô hình Job-based Processing, lấy cảm hứng từ kiến trúc Crypto Driver của AUTOSAR.

Các ý tưởng thiết kế chính:

* Job-based Processing Interface.
* Entry Point thông qua `Crypto_ProcessJob()`.
* Service Mapping bằng Lookup Table.
* Tách biệt Service Request khỏi Algorithm Implementation.
* Parameter Validation.
* DET-style Error Reporting.

### Luồng xử lý Crypto Job

```text
Application
     |
     v
Crypto Service Request
     |
     v
Crypto_ProcessJob()
     |
     v
Kiểm tra Parameter
     |
     v
Service Lookup Table
     |
     +----------+----------+
     |          |          |
     v          v          v
    AES        SHA       Service khác
     |          |             |
     +----------+-------------+
                |
                v
         Job Result / Status
```

### Kiểm chứng Crypto Driver

> Thêm ảnh Debug tại đây.

```text
docs/images/crypto-job-debug.png
docs/images/service-dispatcher.png
docs/images/aes-result.png
```

Ảnh Debug nên thể hiện:

* Nội dung Crypto Job.
* Service ID.
* Lookup Table Entry được lựa chọn.
* Algorithm Function được gọi.
* Input Buffer.
* Output Buffer.
* Job Result.

---

### 4. Diagnostic Communication Manager

DCM chịu trách nhiệm tiếp nhận Diagnostic Request và định tuyến yêu cầu đến Diagnostic Service Handler tương ứng.

Luồng xử lý:

```text
Diagnostic Tester
        |
        v
   CAN / LIN Bus
        |
        v
 Transport Protocol
        |
        v
       PduR
        |
        v
       DCM
        |
        v
 Service Dispatcher
        |
        v
 Diagnostic Service Handler
        |
        v
 Application / ECU Data
```

> Danh sách Diagnostic Service và kết quả kiểm thử sẽ được bổ sung tại đây.

Ví dụ cách trình bày một Test Case:

```text
Request:
02 10 03

Service:
Diagnostic Session Control

Response:
02 50 03
```

---

### 5. Non-Volatile Memory Management

Module NvM hiện đang trong quá trình phát triển.

Kiến trúc dự kiến:

```text
Application
     |
     v
    NvM
     |
     v
Memory Abstraction
     |
     v
Flash Driver
     |
     v
Internal Flash
```

Các chức năng dự kiến:

* Quản lý RAM Block.
* Lưu trữ Non-volatile Block.
* Kiểm tra tính toàn vẹn dữ liệu bằng CRC.
* Khôi phục Default Data.
* Tích hợp Crypto Stack để bảo vệ dữ liệu lưu trữ.

---

## 📁 Cấu trúc dự án

```text
/
├── docs/
│   ├── architecture/
│   ├── debug/
│   └── images/
│
├── src/
│   ├── Os/
│   │   ├── Kernel/
│   │   ├── Scheduler/
│   │   └── Port/
│   │
│   ├── Crypto/
│   │   ├── Driver/
│   │   └── Services/
│   │
│   ├── Com/
│   │   ├── PduR/
│   │   ├── CanIf/
│   │   ├── LinIf/
│   │   └── LinTp/
│   │
│   ├── Dcm/
│   │
│   ├── NvM/
│   │
│   └── Swc/
│
├── include/
│   ├── GeneralTypes/
│   └── Cfg/
│
├── Makefile
├── linker.ld
├── startup.s
└── main.c
```

> Cấu trúc trên cần được cập nhật lại theo đúng cấu trúc thực tế của repository.

---

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

### Mục tiêu kiểm thử

Mô tả chức năng hoặc hành vi cần kiểm chứng.

### Input

```text
Frame nhận được hoặc Function Call
```

### Luồng xử lý mong đợi

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

> Thêm ảnh tại đây.

### Phân tích

Giải thích:

1. Dữ liệu đi vào hệ thống từ đâu.
2. Module nào tiếp nhận dữ liệu.
3. State Transition nào xảy ra.
4. Callback nào được gọi.
5. Kết quả thực tế có phù hợp với thiết kế hay không.

---

## 🛠 Công cụ và môi trường phát triển

| Thành phần             | Công nghệ                |
| ---------------------- | ------------------------ |
| MCU                    | STM32F103                |
| CPU Architecture       | ARM Cortex-M3            |
| Ngôn ngữ               | C / ARM Assembly         |
| Compiler               | ARM GCC                  |
| Build System           | Makefile                 |
| Debugger               | GDB                      |
| Communication          | CAN / LIN                |
| Architecture Reference | AUTOSAR Classic concepts |
| OS Design Reference    | OSEK/VDX concepts        |

---

## 💡 Điểm kỹ thuật nổi bật

### Low-Level Implementation

RTOS Kernel và các thành phần Low-level được triển khai thủ công bằng C và ARM Assembly nhằm nghiên cứu:

* Cortex-M Exception Handling.
* Stack Frame Structure.
* PSP và MSP.
* PendSV Context Switching.
* SVC System Services.
* Startup Sequence.
* Vector Table.
* Linker Script.
* Memory Layout của MCU.

### Modular Architecture

Hệ thống được phân tách thành các tầng:

```text
Application Logic
        |
        v
Module Interface
        |
        v
Service Logic
        |
        v
Hardware Abstraction
        |
        v
Hardware Driver
```

Thiết kế này giúp giảm sự phụ thuộc trực tiếp giữa Application Logic và Hardware Driver.

### Defensive Programming

Dự án áp dụng một số kỹ thuật Defensive Programming:

* Pointer Validation.
* Parameter Validation.
* Kiểm tra trạng thái khởi tạo Module.
* Service ID Validation.
* Error Code Reporting.
* DET-style Development Error Tracing.

---

## 🚀 Hướng phát triển

* [x] Custom OS Kernel cơ bản
* [x] Task Scheduling
* [x] Cortex-M3 Context Switching
* [x] CAN Communication cơ bản
* [x] LIN Communication cơ bản
* [x] PduR Routing Concept
* [x] Crypto Job Processing Architecture
* [ ] Hoàn thiện LinTp State Machine
* [ ] Hoàn thiện tích hợp DCM Service
* [ ] Hoàn thiện NvM Manager
* [ ] Tích hợp CRC để kiểm tra tính toàn vẹn dữ liệu
* [ ] Tích hợp Crypto Service với Persistent Storage
* [ ] Xây dựng Module-level Test Case
* [ ] Phân tích Timing và Memory Usage

---

## 📚 Kiến thức nghiên cứu trong dự án

Thông qua dự án này, các chủ đề kỹ thuật được nghiên cứu và thực hành bao gồm:

* Automotive Embedded Software Architecture.
* AUTOSAR Classic Platform concepts.
* OSEK/VDX OS concepts.
* ARM Cortex-M3 Architecture.
* Real-time Scheduling.
* Context Switching.
* CAN Communication.
* LIN Communication.
* Transport Protocol.
* Diagnostic Communication.
* Cryptographic Service Architecture.
* Embedded Debugging.

---

## ⚠️ Phạm vi dự án

Dự án được phát triển với mục đích học tập, nghiên cứu và xây dựng portfolio cá nhân.

Kiến trúc và API được tham khảo từ các tiêu chuẩn và khái niệm trong Automotive Software, tuy nhiên dự án không tuyên bố tuân thủ hoàn toàn AUTOSAR, đạt chứng nhận OSEK hoặc đáp ứng đầy đủ quy trình ISO 26262.

---

## 👤 Tác giả

**Luu Hoang Phuc**

Email: [luuphuc20012001@gmail.com](mailto:luuphuc20012001@gmail.com)
