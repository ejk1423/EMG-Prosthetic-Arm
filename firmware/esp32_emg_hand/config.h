#ifndef CONFIG_H
#define CONFIG_H

// =======================
// Pin Configuration
// =======================

// MyoWare EMG sensor signal pin.
// Use an analog-capable pin on your ESP32 / Arduino Nano ESP32.
#define EMG_PIN A0

// PCA9685 I2C pins.
// On many ESP32 boards these are usually SDA = 21, SCL = 22.
// On Arduino Nano ESP32, the default Wire pins usually work automatically.
#define USE_CUSTOM_I2C_PINS false
#define SDA_PIN 21
#define SCL_PIN 22

// =======================
// Servo Configuration
// =======================

// PCA9685 servo channels
#define SERVO_INDEX_CHANNEL   0
#define SERVO_MIDDLE_CHANNEL  1
#define SERVO_RING_CHANNEL    2
#define SERVO_THUMB_CHANNEL   3

// Servo pulse values for PCA9685.
// These may need tuning depending on your servos and hand design.
#define SERVO_OPEN_PULSE    150
#define SERVO_CLOSED_PULSE  430

// Safety limits. Do not go crazy with these values.
#define SERVO_MIN_PULSE     120
#define SERVO_MAX_PULSE     500

// Servo frequency for standard hobby servos
#define SERVO_FREQ 50

// =======================
// EMG Settings
// =======================

// Starting threshold. You MUST tune this using Serial Monitor.
#define FLEX_THRESHOLD 1700

// Number of samples used for smoothing.
// Higher = smoother but slower response.
#define SMOOTHING_SAMPLES 10

// Delay between loop updates in milliseconds
#define LOOP_DELAY_MS 20

// =======================
// Debug Settings
// =======================

#define DEBUG_SERIAL true
#define SERIAL_BAUD 115200

#endif