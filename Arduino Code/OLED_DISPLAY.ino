#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  
  //Display Text
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Welcome!");
  display.display(); 
}

void loop() {
  //Display Text
//  display.setTextSize(1);
//  display.setTextColor(WHITE);
//  display.setCursor(0, 10);
//  display.println("Welcome!");
//  display.display(); 
//  delay(4000);
}
