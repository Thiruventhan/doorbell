#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#define ssid      "CK_bell"     // WiFi SSID
#define password  "password"
#define cont_led  12
#define hum_det_led  14
#define hum_pre_led  13
#define pir 2

String data;
String post ;
bool state=0;

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

   data = "myData";
   post = "dataName=" + data ;
  
  attachInterrupt(2,hum ,FALLING);
}


void loop() {
//Sending data to server
 if (state==1){
  digitalWrite(hum_det_led,HIGH);
  PostData();  
  Serial.println();  
  state=0;
  digitalWrite(hum_det_led,LOW);
 }
}

void hum(){
  Serial.println("detected");
  state=1;
}

//Function to handle HTTP request
void PostData(){
 
HTTPClient http;
http.begin("http://10.10.10.1/0001"); // IP is servers IP

http.addHeader("Content-Type", "application/x-www-form-urlencoded");
int httpCode = http.POST(post); // sending post string to server
Serial.println(httpCode); // will get httpcode eg : 200 if connection works fine
if(httpCode == HTTP_CODE_OK)
{
   Serial.print("HTTP response code ");
   Serial.println(httpCode);
   String response = http.getString(); // Reply from the server
   Serial.println(response);
}
else
{
   Serial.println("Error in HTTP request 1");
   int httpCode = http.POST(post); // sending post string to server
  Serial.println(httpCode); // will get httpcode eg : 200 if connection works fine
  if(httpCode == HTTP_CODE_OK)
  {
   Serial.print("HTTP response code ");
   Serial.println(httpCode);
   String response = http.getString(); // Reply from the server
   Serial.println(response);
  }
  else{
     Serial.println("Error in HTTP request 2");
     Serial.println("Failed post");
     while(WiFi.status() != WL_CONNECTED) {
        digitalWrite(cont_led,HIGH);
        Serial.print(".");
        delay(500);
    }
    digitalWrite(cont_led,LOW);
  }
}

http.end();
  }



