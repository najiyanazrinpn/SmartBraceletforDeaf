/*
Najiya(Black)
Mac Address Sender - 78:21:84:7E:1E:B0
                     - {0x78, 0x21, 0x84, 0x7E, 0x1E, 0xB0}

Karthi(Red)
Mac Address Receiver - 78:21:84:7E:0B:BC
                     - {0x78, 0x21, 0x84, 0x7E, 0x0B, 0xBC}
*/
#include <CircularBuffer.h>
#include <esp_now.h>
#include <WiFi.h>

int Mic_Pin = 34;

const uint8_t micSampleDelay = 50; //
uint8_t soundLowAlertLevel = 3000;          // Sound Threshold Levels are the triggers which define when to alert clients.

CircularBuffer<int, 50> micDeltaBuffer;   // Create circular buffer of ints, holding 50 values.  Used for smoothing input

uint16_t rawMicValue;
uint16_t micMinValue = 1024;
uint16_t micMaxValue = 0;
uint16_t micDeltaValue = 0;
uint16_t micDeltaAverage = 0;

uint8_t micDeltaSamplesToAvg = 10;        // Number of mic readings to average together - Can be changed via web interface.

uint8_t micReadingCurrent = 0;

uint32_t micTimeStart; //
uint32_t micTimeNow;//
uint32_t micTimeElapsed;

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x78, 0x21, 0x84, 0x7E, 0x1E, 0xB0};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  int b;
} struct_message;

struct_message myData;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  
  Serial.begin(9600);
  pinMode(Mic_Pin, INPUT);

  micTimeStart = millis();
  
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_send_cb(OnDataSent);
  
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
         
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  micTimeNow = millis();
  micTimeElapsed = micTimeNow - micTimeStart;

  if (micTimeElapsed >= micSampleDelay)
  {

    rawMicValue = analogRead(Mic_Pin);               // Read Mic Value after delay
    Serial.println(rawMicValue);
    micReadingCurrent++;                             // Increment Counter for each read

    micMinValue = min(micMinValue, rawMicValue);     // Change min value if new value is less
    micMaxValue = max(micMaxValue, rawMicValue);     // Change max value if new value is higher

    if (micReadingCurrent >= 4)
    {
      micDeltaValue = (micMaxValue - micMinValue);           // Calculate Delta (difference between softest & loudest sounds
      micDeltaBuffer.unshift(micDeltaValue);                 // Add Delta Value to buffer, which will push old values out
      for (int i = 0; i < micDeltaSamplesToAvg; i++)
      {       // Grab number of values from array based on micDeltaSamplesToAvg variable
        micDeltaAverage += micDeltaBuffer[i];                // Add just those values to the average
      }
      micDeltaAverage = (micDeltaAverage / micDeltaSamplesToAvg);   // Finally, compute the average

      if (micDeltaAverage > soundLowAlertLevel)
      {
        myData.b = 1;
      }
      else
      {
        myData.b = 0;
      }
  
      micMinValue = 1024;                // Reset Values
      micMaxValue = 0;                   //
      micDeltaAverage = 0;               //

      micReadingCurrent = 0;             // Reset Counter
    }
    micTimeStart = millis();             // Reset Timer
  }
  

  
    
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

}
