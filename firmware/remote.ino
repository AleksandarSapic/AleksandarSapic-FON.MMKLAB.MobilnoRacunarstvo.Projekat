#include <IRremote.h>

const int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setupIRRemote() {
  IrReceiver.begin(RECV_PIN, false);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void checkIRRemote() {
  if (IrReceiver.decode()) {
    IrReceiver.resume();
    if (!(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)) {
      handleIRInput(IrReceiver.decodedIRData.command);
    }
  }
}

void handleIRInput(uint16_t value) {
  String digit = "";
  switch (value) {
    case 69: digit = "1"; break;
    case 70: digit = "2"; break;
    case 71: digit = "3"; break;
    case 68: digit = "4"; break;
    case 64: digit = "5"; break;
    case 67: digit = "6"; break;
    case 7: digit = "7"; break;
    case 21: digit = "8"; break;
    case 9: digit = "9"; break;
    case 25: digit = "0"; break;
    case 28: 
      if (inputPassword == correctPassword) {
        Serial.println("Correct password entered.");
        resetSystem();
      } else {
        Serial.println("Incorrect password.");
      }
      return;
    case 8:  
      if (inputPassword.length() > 0) {
        inputPassword.remove(inputPassword.length() - 1);
      }
      return;
  }
  inputPassword += digit;
  Serial.println("Current password: " + inputPassword);
}
