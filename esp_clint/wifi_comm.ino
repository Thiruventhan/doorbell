// function to post data to the server
void PostData(){
 String response;
 String batty=String(analogRead(A0));
 Serial.println(batty);
  post = "dataName=" + data+batty;
HTTPClient http;

http.begin("http://10.10.10.1/0001"); // IP is servers IP

http.addHeader("Content-Type", "application/x-www-form-urlencoded");
int httpCode = http.POST(post); // sending post string to server
Serial.println(httpCode); // will get httpcode eg : 200 if connection works fine
if(httpCode == HTTP_CODE_OK)
{
   Serial.print("HTTP response code ");
   Serial.println(httpCode);
   response = http.getString(); // Reply from the server
   Serial.println(response.substring(8,13));
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
   response = http.getString(); // Reply from the server
   Serial.println(response.substring(8,13));
  }
  else{
     Serial.println("Error in HTTP request 2");
     Serial.println("Failed post");
     digitalWrite(cont_led,LOW);
  }
}
if (response.substring(8,13)="out"){
  human_state=1;
}
http.end();
  }

