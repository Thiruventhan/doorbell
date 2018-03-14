#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "pitches.h"
#include "themes.h"

#define buzzer 5
#define soundBut 0
#define humanBut 2
#define humanled 12

const char *ssid = "CK_bell0001";
const char *password = "password";

bool state=0;              // if true human detected
bool human = true;         // true if human inside
bool soundChage= false;    // if true music shuld be  changed
int music=0; // music track
String reply;

IPAddress         apIP(10, 10, 10, 1);
ESP8266WebServer server(80);


void handleRoot() {
  String data = server.arg("dataName"); // data from the client
  String success = "1";
  Serial.println(data);
  if((data=="hum") && (human)) {
      state=1;
}
 
  if (human){
   reply="_in";
  }
  else{
   reply="out";
  }
   String json = "{\"echo\":\"" + reply + "\","; // reply msg to client
  json += "\"success\":\"" + String(success) + "\"}";
    
  server.send(200, "application/json", json);
}

void setup() {
  pinMode(buzzer,OUTPUT);
  pinMode(humanBut,INPUT);
  pinMode(soundBut,INPUT);
   pinMode(humanled,OUTPUT);
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);


  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/0001", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
  attachInterrupt(0,humin ,FALLING);
  attachInterrupt(2,soundchange ,FALLING);
}

void loop() {
server.handleClient();
if(soundChage){
  playmusic();
}
if (state){
  for (int i=0;i<=10;i++){
    playmusic();
  }
}
}


