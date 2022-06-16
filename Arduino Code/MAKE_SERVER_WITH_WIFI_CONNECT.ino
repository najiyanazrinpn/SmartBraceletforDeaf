#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "V2022";
const char* password = "Najiya123";

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
    String buttons = "<input type=\"checkbox\" onchange=\"func(this)\">Male</input>";
    return buttons;
  }
  return String();
}

void setup() {
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

  server.begin();
}

void loop() {
  
}

/*
 * 
 * #include <WiFi.h>

const char* ssid = "Gray_hat:)";
const char* password = "1010101010";

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());
}

void loop() {
}
 */
