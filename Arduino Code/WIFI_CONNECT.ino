#include <WiFi.h>

const char* ssid = "V2022";
const char* password = "Najiya123";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:


}
