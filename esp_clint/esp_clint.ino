#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#define ssid      "CK_bell0001"     // WiFi SSID
#define password  "password"
#define cont_led  12
#define hum_det_led  14
#define hum_pre_led  13
#define pir 2
#define batt

String data;
String post ;
bool state=0;
bool human_state=0;

void setup() {
    pinMode(cont_led,OUTPUT);
    pinMode(hum_det_led,OUTPUT);
    pinMode(hum_pre_led,OUTPUT);
    pinMode(pir,INPUT);

    
    
    Serial.begin(115200);
    delay(10);
    digitalWrite(cont_led,HIGH);
    WiFi.begin(ssid,password);
    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    digitalWrite(cont_led,LOW);
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

   data = "hum";
   post = "dataName=" + data ;
  
  attachInterrupt(2,hum ,FALLING);
}


void loop() {
//Sending data to server
while(WiFi.status() != WL_CONNECTED) {
        digitalWrite(cont_led,HIGH);
        Serial.print(".");
        delay(500);
}
digitalWrite(cont_led,LOW);
 if (state==1){
  digitalWrite(hum_det_led,HIGH);
  PostData();  
  Serial.println();  
  state=0;
  delay(100);
  digitalWrite(hum_det_led,LOW);
 }
 if(human_state){
  for(int i=0;i<=20;i++){
    digitalWrite(hum_pre_led,HIGH);
    delay(500);
    digitalWrite(hum_pre_led,LOW);
    delay(500); 
  }
  human_state=0;
 }
}


void hum(){
  Serial.println("detected");
  state=1;
}











