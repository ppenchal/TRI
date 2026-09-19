# TRI-LAYER-SECURE-ENTRY-SYSTEM_ARM

---

# **RFID + Password + OTP Based Access System (LPC2148 / LPC214x)**

This project implements a **three-level secure access system** using:

✅ **RFID Authentication**
✅ **Password Verification (Keypad)**
✅ **OTP Verification (GSM Module via UART0)**

The system is built on the LPC2148 ARM7 microcontroller and integrates a 4×4 keypad, LCD, RFID reader (UART1), GSM module (UART0), and I2C EEPROM for secure storage of RFID and password data. Upon successful authentication, the LED on P0.25 is activated.

---

## 📁 **Project Structure**

```
Repository Root/
│
├── src/
│   ├── 01_main.c
│   ├── 02_system.c
│   ├── 03_lcd.c
│   ├── 04_kpm.c
│   ├── 05_i2c.c
│   ├── 06_uart1.c
│   ├── 07_delay.c
│
├── include/
│   ├── 01_defines.h
│   ├── 02_types.h
│   ├── 03_delay.h
│   ├── 04_lcd_defines.h
│   ├── 05_lcd.h
│   ├── 06_kpm_defines.h
│   ├── 07_kpm.h
│   ├── 08_i2c.h
│   ├── 09_uart1.h
│   ├── 10_system.h
|
├── images/        # Block diagrams, Proteus images, photos, etc.
│   ├── block_diagram.png
│   └── proteus_img.png
|
└── README.md
```

---

# ⭐ **Features**

### ✔ **1. RFID Authentication**

Reads tag via **UART1**, compares with stored data in EEPROM.

### ✔ **2. Password Authentication**

User enters 8-digit password using **4×4 Keypad**.

### ✔ **3. OTP-Based Verification**

OTP is generated and sent to registered mobile number using **GSM Module (UART0)**.
User must enter correct OTP within **20 seconds timeout**.

### ✔ **4. LCD Display**

Shows all messages such as:

* `Show RFID Tag`
* `Enter Password`
* `Sending OTP`
* `ACCESS GRANTED` etc.

### ✔ **5. EEPROM Storage (I2C)**

Stores:

* RFID tag at address `0x00`
* Password at address `0x20`

### ✔ **6. LED Control**

**P0.25** is configured as output for Access Granted indication.

---

# 🧰 **Hardware Used**

| Component                      | Purpose             |
| ------------------------------ | ------------------- |
| **LPC2148 ARM7 MCU**           | Core controller     |
| **Serial RFID Reader** | Tagged access       |
| **GSM Module**        | OTP SMS sending     |
| **4×4 Matrix Keypad**          | Password/OTP entry  |
| **I2C EEPROM 24C02/24C04**     | Store RFID/Password |
| **16×2 LCD**                   | User interface      |
| **LED (P0.25)**                | Access indicator    |

---

# 🔌 **Pin Connections**

### **LCD**

* D0–D7 → P0.10 – P0.17
* RS = P0.18
* RW = P0.19
* EN = P0.20

### **Keypad**

Mapped using `kpm_defines.h`

### **I2C EEPROM**

* SDA → P0.2
* SCL → P0.3

### **RFID Reader**

* RX, TX → UART1 → P0.8, P0.9

### **GSM Module**

* RX, TX → UART0 → P0.0, P0.1

### **LED**

* LED → P0.25

---

# 🧪 **Authentication Flow**

```
RFID -> Correct? 
      -> Password -> Correct?
                    -> OTP Sent -> Enter OTP 
                                  -> Match? 
                                        -> ACCESS GRANTED (LED ON)
                                        -> Else: ACCESS DENIED
```

---

# 🛠 **How to Build and Flash**

1. Open project in **Keil uVision**.
2. Add all `.c` files inside **src/**
3. Add all `.h` files inside **include/**
4. Set device to **LPC2148**
5. Compile and generate HEX
6. Flash using:

   * Flash Magic
---

# 📌 **Important Notes**
* LED on for 2 seconds on access.
* Default stored values:

  * RFID: `"12345678"`
  * Password: `"12341234"`

---

---
## 🏅 **Author**

**Raj-GitCode**  <br>
📌 *TRI-LAYER-SECURE-ENTRY-SYSTEM*

