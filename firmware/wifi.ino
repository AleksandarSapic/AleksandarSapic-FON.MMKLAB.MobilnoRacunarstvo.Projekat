#define SERVER_URL "http://127.0.0.1:3000/api/data"
#define CONTENT_TYPE "Content-Type", "application/json"

void wifi_connect(char* ssid, char* password) {
  int attemptsNo = 0;
  Serial.println("\n----> Connecting to WIFI");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED && attemptsNo < 200) {
    attemptsNo++;
    delay(50);
    Serial.print(".");
    delay(50);
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n|+| ----> Connected to the WiFi network!");
    Serial.print("|+| ----> Local ESP8266 IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("|-| ----> Cannot connect to WiFi!");
  }
}

void sendAlert() {
  String url = SERVER_URL;
  String message = "Intruder detected. Incorrect password entered.";
  String body = "{\"time\":\"";
  body = body + String(millis());
  body = body + "\", \"message\":";
  body = body + message;
  body = body + "}";

  Serial.println("|+| ----> Sending HTTP POST request:");
  Serial.println(url);
  Serial.println(body);
  
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(url);
    http.addHeader(CONTENT_TYPE);
    int httpResponseCode = 0;
    httpResponseCode = http.POST(body);
    String response = "";
    if (httpResponseCode > 0) {
      response = http.getString();
      Serial.print("|+| ----> HTTP RESPONSE CODE: ");
      Serial.println(httpResponseCode);
      Serial.print("|+| ----> RESPONSE FROM SERVER: ");
      Serial.println(response);
    } else {
      Serial.println(F("|-| ----> Error sending HTTP request!"));
      Serial.print("|-| ----> RESPONSE CODE: ");
      Serial.println(httpResponseCode);
    }
  }
}

