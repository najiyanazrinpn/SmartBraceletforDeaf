#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "V2022";
const char* password = "Najiya123";

const int vibPin = 2;

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
    String buttons = "<h2>OK</h2>";
    return buttons;
  }
  return String();
}

void vib_on(){
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
}

void setup() {
  pinMode (vibPin, OUTPUT);
  
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
