#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const char* ssid = "ESP32-Soft-accessPoint";
const char* password = "P@ssw0rd";

const char* setupdata_server = "http://192.168.4.1/setupdata";

String SetupData;


unsigned long last_time = 0;
const long Delay = 10000; 

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  unsigned long current_time = millis();
  if(current_time - last_time >= Delay) {
    if(WiFi.status()== WL_CONNECTED ){ 
      SetupData = HTTP_Request(setupdata_server);
      Serial.println("Status: OK");
      if (SetupData != "")
      {
        Serial.println("ResultData = " + SetupData);
      }
      last_time = current_time;
    }
    else {
      Serial.println("WiFi got disconnected!");
      Serial.println("Reconnecting to WiFi...");
      WiFi.disconnect();
      WiFi.reconnect();
    }
  }
}

String HTTP_Request(const char* server_name) {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, server_name);
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();

  return payload;
}
