/*
Finding the Mac Address of the sender node - Najiya(Black)
Mac Address Sender - 78:21:84:7E:1E:B0
                     - {0x78, 0x21, 0x84, 0x7E, 0x1E, 0xB0}
Find the MAC Address of the receiver node - Karthi(Red)
Mac Address Receiver - 78:21:84:7E:0B:BC
                     - {0x78, 0x21, 0x84, 0x7E, 0x0B, 0xBC}
*/

#include <WiFi.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress());
}

void loop() {
  // put your main code here, to run repeatedly:

}
