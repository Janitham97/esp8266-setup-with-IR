
#include <ESP8266WiFi.h>

int sensor = 13; //pin for wifi module
int sensor1 = 12; //pin for wifi module

String  ClientRequest;
String d;
WiFiServer server(80);

void setup()
{
  ClientRequest = "";
   pinMode(sensor, INPUT);
Serial.begin(9600);
  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
   WiFi.begin("wifi name","password");  //replace with your wifi
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("Connected");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP().toString()));
  server.begin();

}


void loop()
{
    long state = digitalRead(sensor);
    long state1 = digitalRead(sensor1);
    if(state==LOW || state1==LOW){
      d="One Customers on seats";
      Serial.println("One Customers on seats");
      delay(3000);
    }else{
      d="customers not on seats";
      Serial.println("customers not on seats");
      delay(3000);
      }

 
      if(state==LOW && state1==LOW){
      d="Two Customers on seats";
      Serial.println("Two Customers on seats");
      delay(3000);
    }else{
      d="customers not on seats";
      Serial.println("customers not on seats");
      delay(3000);
      }
      
    WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    ClientRequest = (client.readStringUntil('\r'));
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println(d);
    client.println("</html>");
    //client.stop();
    delay(1);
    client.flush();

}