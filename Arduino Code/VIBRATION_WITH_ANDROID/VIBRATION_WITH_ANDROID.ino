#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* ssid = "V2022";
const char* password = "Najiya123";

const int vibPin = 2;

String data = "";
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<html>
<body>
<h3>hello world!</h3>
%BUTTONPLACEHOLDER%
</body>
</html>
)rawliteral";



String processor(const String& var){
  if(var == "BUTTONPLACEHOLDER"){
    String buttons = "OK";
    return buttons;
  }
  return String();
}

void vib_on(){
  Serial.begin(115200);
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  //Display Text
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println(data);
  display.display(); 

    Serial.println(data);
  
  digitalWrite(vibPin, HIGH);
  delay(500);
  digitalWrite(vibPin, LOW);
  delay(500);
  digitalWrite(vibPin, HIGH);
  delay(500);
}
void vib_off(){
  digitalWrite(vibPin, LOW);
  
  delay(500);
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("");
  display.display(); 
}

void setup() {
  pinMode (vibPin, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("welcome");
  display.display();

  
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  

  server.on("/on_vib", HTTP_GET, [](AsyncWebServerRequest *request){
    
    if (request->hasParam("data"))
    {
      data = request->getParam("data")->value();
    }
    Serial.println("Got vibration request ON  ");    
    vib_on();
  });

  server.on("/off_vib", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Got vibration request OFF  ");
    vib_off();
  });

  server.begin();
}

void loop() {
  
}
