#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "config.h"

// PCA9685 servo driver object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Rolling average storage for EMG smoothing
int emgSamples[SMOOTHING_SAMPLES];
int sampleIndex = 0;
long sampleTotal = 0;

// Current hand state
bool handClosed = false;

void setup() {
#if DEBUG_SERIAL
  Serial.begin(SERIAL_BAUD);
  delay(1000);
  Serial.println("Starting ESP32 EMG Prosthetic Hand Prototype...");
#endif

  setupEMG();
  setupServoDriver();

#if DEBUG_SERIAL
  Serial.println("Setup complete.");
  Serial.println("Relax/flex your muscle and watch the EMG values.");
#endif
}

void loop() {
  int rawEMG = analogRead(EMG_PIN);
  int smoothedEMG = getSmoothedEMG(rawEMG);

  handClosed = smoothedEMG > FLEX_THRESHOLD;

  if (handClosed) {
    closeHand();
  } else {
    openHand();
  }

#if DEBUG_SERIAL
  printDebug(rawEMG, smoothedEMG, handClosed);
#endif

  delay(LOOP_DELAY_MS);
}

// Setup Functions

void setupEMG() {
  for (int i = 0; i < SMOOTHING_SAMPLES; i++) {
    emgSamples[i] = 0;
  }

#if DEBUG_SERIAL
  Serial.println("EMG sensor initialized.");
#endif
}

void setupServoDriver() {
#if USE_CUSTOM_I2C_PINS
  Wire.begin(SDA_PIN, SCL_PIN);
#else
  Wire.begin();
#endif

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);

  delay(500);

  openHand();

#if DEBUG_SERIAL
  Serial.println("PCA9685 servo driver initialized.");
#endif
}

// EMG Processing

int getSmoothedEMG(int newReading) {
  sampleTotal -= emgSamples[sampleIndex];
  emgSamples[sampleIndex] = newReading;
  sampleTotal += newReading;

  sampleIndex++;

  if (sampleIndex >= SMOOTHING_SAMPLES) {
    sampleIndex = 0;
  }

  return sampleTotal / SMOOTHING_SAMPLES;
}

// Hand Movement

void openHand() {
  setServoSafe(SERVO_INDEX_CHANNEL, SERVO_OPEN_PULSE);
  setServoSafe(SERVO_MIDDLE_CHANNEL, SERVO_OPEN_PULSE);
  setServoSafe(SERVO_RING_CHANNEL, SERVO_OPEN_PULSE);
  setServoSafe(SERVO_THUMB_CHANNEL, SERVO_OPEN_PULSE);
}

void closeHand() {
  setServoSafe(SERVO_INDEX_CHANNEL, SERVO_CLOSED_PULSE);
  setServoSafe(SERVO_MIDDLE_CHANNEL, SERVO_CLOSED_PULSE);
  setServoSafe(SERVO_RING_CHANNEL, SERVO_CLOSED_PULSE);
  setServoSafe(SERVO_THUMB_CHANNEL, SERVO_CLOSED_PULSE);
}

void setServoSafe(int channel, int pulse) {
  int safePulse = constrain(pulse, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
  pwm.setPWM(channel, 0, safePulse);
}


// Debug Output

void printDebug(int rawEMG, int smoothedEMG, bool closed) {
  Serial.print("Raw EMG: ");
  Serial.print(rawEMG);

  Serial.print(" | Smoothed EMG: ");
  Serial.print(smoothedEMG);

  Serial.print(" | Threshold: ");
  Serial.print(FLEX_THRESHOLD);

  Serial.print(" | Hand: ");
  Serial.println(closed ? "CLOSED" : "OPEN");
}