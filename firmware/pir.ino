const int PIR_PIN = 5;

void setupPIR() {
  pinMode(PIR_PIN, INPUT);
}

bool isMotionDetected() {
  int pir_val = digitalRead(PIR_PIN);
  return pir_val == HIGH;
}