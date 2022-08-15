/*
Najiya(Black)
Mac Address Sender - 78:21:84:7E:1E:B0
                     - {0x78, 0x21, 0x84, 0x7E, 0x1E, 0xB0}

Karthi(Red)
Mac Address Receiver - 78:21:84:7E:0B:BC
                     - {0x78, 0x21, 0x84, 0x7E, 0x0B, 0xBC}
*/
#include <esp_now.h>
#include <WiFi.h>

const int ledPin = 2;
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a[32];
    int b;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("Int: ");
  Serial.println(myData.b);
  Serial.println();
  if (myData.b > 0)
    digitalWrite(ledPin, LOW);
  else
    digitalWrite(ledPin, HIGH);
  
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

}
