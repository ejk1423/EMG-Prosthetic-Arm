#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

const int SERVO_CHANNEL = 0;

const int SERVO_OPEN = 150;
const int SERVO_CLOSED = 430;

void setup() {
  Serial.begin(115200);

  Wire.begin();

  pwm.begin();
  pwm.setPWMFreq(50);

  delay(500);

  Serial.println("Servo test started.");
}

void loop() {
  Serial.println("Opening servo...");
  pwm.setPWM(SERVO_CHANNEL, 0, SERVO_OPEN);
  delay(1000);

  Serial.println("Closing servo...");
  pwm.setPWM(SERVO_CHANNEL, 0, SERVO_CLOSED);
  delay(1000);
}