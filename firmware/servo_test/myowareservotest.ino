#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

const int EMG_PIN = A0;
const int SERVO_CHANNEL = 0;

// start conservatively
const int OPEN_PULSE = 200;
const int CLOSED_PULSE = 400;

//adjustable
int threshold = 3000;

// prevent rapid switching near the threshold
const int hysteresis = 100;

bool handClosed = false;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  Wire.begin(A4, A5);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);

  pwm.setPWM(SERVO_CHANNEL, 0, OPEN_PULSE);

  delay(1000);
  Serial.println("MyoWare servo control started");
}

void loop() {
  int emg = analogRead(EMG_PIN);

  Serial.print("EMG: ");
  Serial.print(emg);
  Serial.print("  State: ");
  Serial.println(handClosed ? "CLOSED" : "OPEN");

  if (!handClosed && emg > threshold + hysteresis) {
    handClosed = true;
    pwm.setPWM(SERVO_CHANNEL, 0, CLOSED_PULSE);
  }

  if (handClosed && emg < threshold - hysteresis) {
    handClosed = false;
    pwm.setPWM(SERVO_CHANNEL, 0, OPEN_PULSE);
  }

  delay(20);
}