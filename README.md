# Arduino-Based Smart Greenhouse Automation System

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform: Arduino](https://img.shields.io/badge/Platform-Arduino_Uno-blue.svg)](https://www.arduino.cc/)

A robust, microcontroller-based automation system designed to monitor and regulate environmental parameters in modern greenhouses. This system optimizes resource consumption (water and energy) while ensuring optimal plant growth conditions.

## 🌟 Key Features
* **Automated Irrigation:** Real-time soil moisture tracking triggers the water pump autonomously.
* **Climate Regulation:** Dynamic temperature and humidity monitoring via DHT11 activates cooling fans when thresholds are exceeded.
* **Safety Protocols:** Integrated liquid level sensors trigger audible buzzer alerts during water scarcity.
* **Wireless Override:** Seamless manual control via mobile devices using an HC-05 Bluetooth module.
* **Local Visualization:** Live data streaming displayed on an I2C 16x2 LCD interface.

---

## 🏗️ System Architecture & Pin Mapping

| Component | Arduino Pin | Description |
| :--- | :--- | :--- |
| **DHT11 (Temp/Humidity)** | D2 | Digital pin (DHT Library) |
| **Soil Moisture Sensor** | A0 | Analog input (0-1023 range) |
| **Water Level Sensor** | A1 | Analog input for tank monitoring |
| **Pump Relay** | D7 | Active-LOW relay for water pump |
| **Fan Relay** | D8 | Active-LOW relay for cooling fan |
| **Buzzer** | D9 | Audible alarm system |
| **Bluetooth Module (HC-05)** | D10 (RX), D11 (TX) | SoftwareSerial communication |
| **I2C LCD (16x2)** | A4 (SDA), A5 (SCL) | UI Display (Address: 0x27) |

---

## 📂 Documentation & Resources
Explore the detailed documentation in the `docs/` directory:
* [Bill of Materials (BOM)](docs/bill_of_materials.md) - Complete hardware breakdown and cost analysis.
* [Schematics & Wiring](docs/schematics.md) - Circuit diagrams and power configuration.
* [User Manual](docs/user_manual.md) - Bluetooth command reference and operating guide.
* [Troubleshooting & Calibration](docs/troubleshooting.md) - Sensor calibration and maintenance tips.

## 📜 License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.