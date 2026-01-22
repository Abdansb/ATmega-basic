# ATmega-Basic: AVR Learning & GPS Tracker Project

![Language](https://img.shields.io/badge/Language-Embedded%20C-blue)
![Platform](https://img.shields.io/badge/Platform-ATmega%20AVR-orange)
![IDE](https://img.shields.io/badge/IDE-Atmel%20Studio%207.0-red)

A collection of basic input-output programming examples for ATmega AVR microcontrollers, culminating in a **Final Project: A standalone GPS Tracker System**.

---

## 🛰️ Final Project: ATmega GPS Tracker

This project demonstrates a raw implementation of a GPS tracking system using an **ATmega16** microcontroller. It parses NMEA sentences from a GPS module via UART and displays the coordinates (Latitude/Longitude) on a 16x2 LCD.

### 📸 Project Gallery
| Hardware Setup | LCD Output |
| :---: | :---: |
| <img src="https://github.com/Abdansb/ATmega-basic/blob/main/Screenshot%202022-12-31%20092721.png?raw=true" width="360" /> | <img src="https://github.com/Abdansb/ATmega-basic/blob/main/IMG_20221222_084001.jpg?raw=true" width="360" /> |

### ⚡ Key Features
* **UART Communication:** Reads raw serial data from the GPS Module.
* **NMEA Parsing:** Extracts relevant coordinate data from standard GPS strings.
* **LCD Interfacing:** Displays real-time location data on a 16x2 Character LCD without using heavy Arduino libraries.
* **Low Level C:** Written in pure Embedded C for maximum efficiency.

### 📂 Source Code
👉 **[Click here to view the GPS Tracker Source Code](https://github.com/Abdansb/ATmega-basic/blob/main/Final%20Project/FinalProject10/FinalProject10/FinalProject10.c)**

---

## 🛠️ Hardware Requirements

To replicate the examples and the final project, you will need:

1.  **Microcontroller:** ATmega16 / ATmega32 (or compatible Minimum System Board).
2.  **Programmer:** USBasp (recommended) or Arduino as ISP.
3.  **GPS Module:** Ublox NEO-6M / NEO-7M (for Final Project).
4.  **Display:** LCD 16x2 (HD44780 Controller).
5.  **Basic Components:** LEDs, Push Buttons, Breadboard, Jumper Wires.

## 💻 Software & Tools

* **IDE:** [Atmel Studio 7.0](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio) (Microchip Studio).
* **Flasher:** Khazama AVR Programmer (or AVRDUDE).
* **Drivers:** [Zadig](https://zadig.akeo.ie/) (Required to install generic USB drivers for USBasp).

---

## 🚀 Getting Started

### 1. Setting up the Environment
Ensure your USBasp drivers are installed properly using Zadig.
1.  Plug in USBasp.
2.  Open Zadig.
3.  Select `libusbK` or `libusb-win32` driver.
4.  Click "Install Driver".

### 2. Flashing the Code
You can compile the code in Atmel Studio to generate a `.hex` file.
1.  Open **Khazama AVR Programmer**.
2.  Select your chip (e.g., ATmega16).
3.  Load the `.hex` file generated from the project.
4.  Click **Auto Program**.

> **Tip:** You can also use an Arduino board as a programmer by uploading the "ArduinoISP" sketch and connecting it via ICSP pins to the ATmega chip.

---

## 📚 Repository Structure
* `/Basic Examples` - Simple LED blink and Button handling codes.
* `/Final Project` - Full source code for the GPS Tracker.

## 🤝 Contributing
Feel free to open an issue or submit a pull request if you have suggestions to improve the NMEA parsing logic or hardware efficiency.

---
*Created by [Abdansb](https://github.com/Abdansb)*
