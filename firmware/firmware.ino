String inputPassword = "";
String correctPassword = "1234";

unsigned long entryTime;
bool counting = false;

void setup() {
  Serial.begin(9600);
  setupPIR();
  setupIRRemote();
  wifi_connect("ssid", "password");
}

void loop() {
  if (isMotionDetected() && !counting) {
    // PIR senzor je detektovao pokret, započni odbrojavanje
    startCounter();
  }

  if (counting) {
    // Provera unosa šifre
    checkIRRemote();
    // Provera tajmera
    checkTimer();
  }
}

void startCounter() {
  counting = true;
  entryTime = millis();
  inputPassword = "";
  Serial.println("Movement detected. Enter password:");
}

void checkTimer(){
  if (millis() - entryTime > 15000) {
    // Isteklo je vreme, provera šifre
    if (inputPassword != correctPassword) {
      sendAlert();
    }
    resetSystem();
  }
}

void resetSystem() {
  counting = false;
  inputPassword = "";
  Serial.println("System reset.");
}
