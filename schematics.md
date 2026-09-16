# Schematics and Wiring Guidelines

## Circuit Overview
The system relies on an Arduino Uno microcontroller acting as the central hub. Peripherals are divided into input sensors (DHT11, Soil Moisture, Water Level, Bluetooth) and output actuators (Relays for Pump/Fan, Buzzer, LCD Display).

## Power Distribution & Safety Warnings
1. **Independent Power Supply:** Never power high-current inductive loads (such as the DC water pump and cooling fan) directly from the Arduino's 5V pin. Always use an external power source (e.g., 18650 battery pack or external adapter) with a **common ground (GND)** connected to the Arduino.
2. **Relay Logic:** The 2-channel relay module used in this project operates on **Active-LOW** logic. A LOW signal (`digitalWrite(PIN, LOW)`) activates the relay switch, while a HIGH signal turns it off.
3. **Decoupling:** Ensure stable connections for the I2C LCD to prevent signal degradation over longer jumper wires.
