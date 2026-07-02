const int EMG_PIN = A0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("MyoWare EMG read test started.");
  Serial.println("Relax and flex your muscle to compare values.");
}

void loop() {
  int emgValue = analogRead(EMG_PIN);

  Serial.println(emgValue);

  delay(20);
}