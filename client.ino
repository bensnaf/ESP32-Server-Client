#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

const char* ssid = "ESP32-Soft-accessPoint";
const char* password = "P@ssw0rd";
const char* DataSet = "";
//INPUT
int Btn1 = 5;
int Btn2 = 18;
int Btn3 = 19;
int DataBtn1,DataBtn2,DataBtn3;
//OUTPUT
int DataOP1 = 27;
int DataOP2 = 26;
int DataOP3 = 25;
int DataOP4 = 33;
int DataOP5 = 32;
int DataOP6 = 36;
int DataOP7 = 34;

AsyncWebServer server(80);

unsigned long last_time = 0;
const long Delay = 10000;

void ButtonAction()
{
  DataBtn1 = digitalRead(Btn1);
  DataBtn2 = digitalRead(Btn2); 
  DataBtn3 = digitalRead(Btn3);  

  if (Btn1 == 1)
  {
    analogWrite(DataOP1, 1);
    analogWrite(DataOP2, 10);
    analogWrite(DataOP3, 11);
    analogWrite(DataOP4, 100);
    analogWrite(DataOP5, 101);
    analogWrite(DataOP6, 110);
    analogWrite(DataOP7, 111);
    DataSet = "Button 1: Data sent to analog";
  }else if (Btn2 == 1)
  {
    analogWrite(DataOP1, 1);
    analogWrite(DataOP2, 10);
    analogWrite(DataOP3, 11);
    analogWrite(DataOP4, 100);
    analogWrite(DataOP5, 101);
    analogWrite(DataOP6, 110);
    analogWrite(DataOP7, 111);
    DataSet = "Button 2: Data sent to analog";
  }else if (Btn3 == 1)
  {
    analogWrite(DataOP1, 1);
    analogWrite(DataOP2, 10);
    analogWrite(DataOP3, 11);
    analogWrite(DataOP4, 100);
    analogWrite(DataOP5, 101);
    analogWrite(DataOP6, 110);
    analogWrite(DataOP7, 111);
    DataSet = "Button 3: Data sent to analog";
  }
  SetupData();
}

String SetupData()
{
  Serial.print(DataSet);
  return String(DataSet);
}

void setup(){
  Serial.begin(115200);
  
  pinMode (Btn1, INPUT);
  pinMode (Btn2, INPUT);
  pinMode (Btn3, INPUT);
  pinMode (DataOP1, OUTPUT);
  pinMode (DataOP2, OUTPUT);
  pinMode (DataOP3, OUTPUT);
  pinMode (DataOP4, OUTPUT);
  pinMode (DataOP5, OUTPUT);
  pinMode (DataOP6, OUTPUT);
  pinMode (DataOP7, OUTPUT);
  
  Serial.println();
  Serial.println("Setting soft access point mode");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/setupdata", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", SetupData().c_str());
  });
  
  
  server.begin();
}
 
void loop(){
  unsigned long current_time = millis();
  if(current_time - last_time >= Delay) 
  {
    ButtonAction();
    last_time = current_time;
  }
}
