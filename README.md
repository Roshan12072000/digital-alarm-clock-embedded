# ⏰ Digital Alarm Clock – Embedded C Project

## 📌 Project Overview

The Digital Alarm Clock is an embedded system application developed using a PIC microcontroller to display real-time clock information and generate alarm alerts based on user-configured time settings.

The system continuously tracks current time and allows users to configure an alarm. When the preset alarm time matches the system time, an LED indication is triggered as an alert.

This project demonstrates real-time embedded firmware development, timer usage, and peripheral interfacing.

---

## ⚙️ System Working Principle

The microcontroller maintains real-time clock operation using timer peripherals and software time counters.

Users can configure:

* Current system time
* Alarm trigger time

When system time equals alarm time, the controller activates an LED output to indicate the alarm event.

---

## 🖥️ System Screens / Output

### 1️⃣ Default Clock Display

Displays continuous real-time clock information.

```
Time : 10 : 45 : 32
Alarm : OFF
```

---

### 2️⃣ Time Setting Mode

Allows the user to configure system time.

```
Set Time :
HH : MM : SS
```

Navigation is done using push buttons or keypad inputs.

---

### 3️⃣ Alarm Setting Screen

Users can set alarm trigger time.

```
Set Alarm :
06 : 30 : 00
```

---

### 4️⃣ Alarm Trigger Indication

When system time matches alarm time:

```
*** ALARM ACTIVE ***
LED : ON
```

The LED remains ON for a predefined duration or until user acknowledgment.

This demonstrates event-based GPIO control in embedded systems.

---

## 🚀 Features

* Real-time clock display
* Time setting functionality
* Alarm configuration
* LED-based alarm indication
* LCD display interface
* Button / keypad navigation
* Timer-based time tracking

---

## 🛠️ Hardware Components Used

* PIC Microcontroller (PIC18F4580 / similar)
* 16×2 CLCD Display
* Push Buttons / Keypad
* LED Alarm Indicator
* Crystal Oscillator
* Power Supply Circuit

---

## 💻 Software Tools

* Embedded C
* MPLAB IDE
* XC8 Compiler
* Makefile Build System

---

## 📂 Project Structure

```
Digital_Alarm_Clock/
│
├── main.c
├── clock.c
├── alarm.c
├── clcd.c
├── clcd.h
├── Makefile
├── README.md
```

---

## ▶️ Build Instructions

### Compile

```
make
```

### Clean Build Files

```
make clean
```

The HEX file generated can be programmed into the microcontroller.

---

## 🎯 Applications

* Household alarm systems
* Office reminder systems
* Industrial timers
* Event notification devices
* Embedded scheduling systems

---

## 📚 Learning Outcomes

* Timer programming
* Real-time clock implementation
* Alarm scheduling logic
* GPIO output control
* Embedded user interface design

---

## 👨‍💻 Author

**Roshan Jameer**
GitHub: https://github.com/Roshan12072000

---

## 📜 Note

This project was developed for educational purposes to understand real-time embedded clock systems and alarm event handling using microcontrollers.
