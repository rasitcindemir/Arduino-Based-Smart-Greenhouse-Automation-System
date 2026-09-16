/**
 * @file SmartGreenhouse.ino
 * @author Mechatronics Engineering Student
 * @brief Arduino-Based Smart Greenhouse Automation System
 * @version 1.1
 * @date 2026-09-16
 */

#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// --- Pin Definitions ---
constexpr uint8_t PIN_DHT = 2;
constexpr uint8_t PIN_SOIL_MOISTURE = A0;
constexpr uint8_t PIN_WATER_LEVEL = A1;
constexpr uint8_t PIN_PUMP_RELAY = 7;
constexpr uint8_t PIN_FAN_RELAY = 8;
constexpr uint8_t PIN_BUZZER = 9;
constexpr uint8_t PIN_BT_RX = 10;
constexpr uint8_t PIN_BT_TX = 11;

// --- Constants & Thresholds ---
constexpr uint8_t DHT_TYPE = DHT11;
constexpr uint8_t I2C_LCD_ADDRESS = 0x27;
constexpr unsigned long SENSOR_READ_INTERVAL = 5000; // 5 seconds
constexpr int SOIL_DRY_THRESHOLD = 700;
constexpr float TEMP_HIGH_THRESHOLD = 30.0;
constexpr int WATER_LOW_THRESHOLD = 200;

// --- Global Objects ---
DHT dht(PIN_DHT, DHT_TYPE);
LiquidCrystal_I2C lcd(I2C_LCD_ADDRESS, 16, 2);
SoftwareSerial btSerial(PIN_BT_RX, PIN_BT_TX);

// --- Timing Variables ---
unsigned long previousMillis = 0;

// --- Function Prototypes ---
void initializeHardware();
void handleSensors();
void handleBluetoothCommands();

void setup() {
    initializeHardware();
}

void loop() {
    unsigned long currentMillis = millis();

    // Non-blocking periodic sensor reading and control logic
    if (currentMillis - previousMillis >= SENSOR_READ_INTERVAL) {
        previousMillis = currentMillis;
        handleSensors();
    }

    // Handle incoming Bluetooth commands for manual override
    handleBluetoothCommands();
}

/**
 * @brief Initializes pins, communication protocols, and peripherals.
 */
void initializeHardware() {
    // Configure relay and actuator pins
    pinMode(PIN_PUMP_RELAY, OUTPUT);
    pinMode(PIN_FAN_RELAY, OUTPUT);
    pinMode(PIN_BUZZER, OUTPUT);
    
    // Set safe initial states (Relays OFF due to active-LOW logic, Buzzer OFF)
    digitalWrite(PIN_PUMP_RELAY, HIGH);
    digitalWrite(PIN_FAN_RELAY, HIGH);
    digitalWrite(PIN_BUZZER, LOW);

    // Initialize serial communications
    Serial.begin(9600);
    btSerial.begin(9600);
    dht.begin();
    
    // Initialize LCD display
    lcd.begin();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Smart Greenhouse");
    lcd.setCursor(0, 1);
    lcd.print("Initializing...");
    delay(2000);
    lcd.clear();
}

/**
 * @brief Reads data from sensors and manages automated outputs.
 */
void handleSensors() {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    int soilMoistureVal = analogRead(PIN_SOIL_MOISTURE);
    int waterLevelVal = analogRead(PIN_WATER_LEVEL);

    // Validate sensor readings
    if (isnan(humidity) || isnan(temperature)) {
        Serial.println(F("Error: Failed to read from DHT sensor!"));
        return;
    }

    // Update LCD Screen
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T:" + String(temperature, 1) + "C H:" + String(humidity, 0) + "%");
    lcd.setCursor(0, 1);
    lcd.print("Soil:" + String(soilMoistureVal));

    // Automated Pump Control (Active LOW logic)
    if (soilMoistureVal > SOIL_DRY_THRESHOLD) {
        digitalWrite(PIN_PUMP_RELAY, LOW); // Turn Pump ON
    } else {
        digitalWrite(PIN_PUMP_RELAY, HIGH); // Turn Pump OFF
    }

    // Automated Fan Control (Active LOW logic)
    if (temperature > TEMP_HIGH_THRESHOLD) {
        digitalWrite(PIN_FAN_RELAY, LOW); // Turn Fan ON
    } else {
        digitalWrite(PIN_FAN_RELAY, HIGH); // Turn Fan OFF
    }

    // Water Level Safety Check
    if (waterLevelVal < WATER_LOW_THRESHOLD) {
        digitalWrite(PIN_BUZZER, HIGH); // Sound Alarm
    } else {
        digitalWrite(PIN_BUZZER, LOW);  // Stop Alarm
    }
}

/**
 * @brief Processes incoming commands via Bluetooth module.
 */
void handleBluetoothCommands() {
    if (btSerial.available()) {
        char command = btSerial.read();
        switch (command) {
            case 'P': // Manual Pump ON
                digitalWrite(PIN_PUMP_RELAY, LOW);
                break;
            case 'p': // Manual Pump OFF
                digitalWrite(PIN_PUMP_RELAY, HIGH);
                break;
            case 'F': // Manual Fan ON
                digitalWrite(PIN_FAN_RELAY, LOW);
                break;
            case 'f': // Manual Fan OFF
                digitalWrite(PIN_FAN_RELAY, HIGH);
                break;
            default:
                break;
        }
    }
}